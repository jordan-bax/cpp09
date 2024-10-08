#include <algorithm>
#include "PmergeMe.hpp"
#include <chrono>
#include "../mycolor.hpp"


// looks if all of src contains only charecter in set;
bool	ft_stringSet(char const *src, char const *set)
{
	int		n;
	int		index;

	index = 0;
	n = 0;
	while (src[index])
	{
		while (set[n] != src[index])
		{
			if (!set[n])
				return (false);
			n++;
		}
		n = 0;
		index++;
	}
	return (true);
}

int main(int argc, char const *argv[])
{
	std::vector<int> container1;
	std::string s_container1;
	std::deque<int> container2;
	std::string s_container2;

	// Error checks
	if (argc < 3)
	{
		std::cout << FG_RED << "Error, can't sort with les than 2 numbers" << FG_DEFAULT << std::endl;
		return 1;
	}
	for (int i = 1; i < argc; i++)
	{
		if (!ft_stringSet(argv[i], "0123456789"))
		{
			std::cout << FG_RED << "Error, can't sort with negitive or non numbers" << FG_DEFAULT << std::endl;
			return 1;
		}
	}
	g_comperisons = 0;
	// place the argument in container and execute the ford jonson
	jb_argumentToContaner(container1, argc, argv);
	jb_displayContaner(container1, "Before: ");
	// start time by getting the current system time
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	container1 = ford_johnson<std::vector, int,int>(container1);
	// end time by getting the current system time
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	jb_displayContaner(container1, "After: ");
	// calculate the time spend by milliseconds inside a double type
	std::chrono::duration<double, std::milli> ms_double = end - start;
	g_comperisons = 0;
	jb_argumentToContaner(container2, argc, argv);
	// jb_displayContaner(container2, "Before: ");
	// start time by getting the current system time
	start = std::chrono::high_resolution_clock::now();
	container2 = ford_johnson<std::deque, int,int>(container2);
	// end time by getting the current system time
	end = std::chrono::high_resolution_clock::now();
	// jb_displayContaner(container2, "After: ");
	if ( ms_double <= end - start)
	{
		s_container1 = FG_GREEN;
		s_container2 = FG_LRED;
	}
	else
	{
		s_container1 = FG_LRED;
		s_container2 = FG_GREEN;
	}
	std::cout << s_container1<<"Time to process a range of "<<container1.size()
		<<" elements with std::vector : "<< ms_double.count() << "ms\n" FG_DEFAULT;
	// calculate the time spend by milliseconds inside a double type
	ms_double = end - start;
	std::cout << s_container2<<"Time to process a range of "<<container2.size()
		<<" elements with std::deque : "<< ms_double.count() << "ms\n" FG_DEFAULT;
	// jb_displayContaner(container1, "After: ");
	// std::vector<int> container3;
	// jb_argumentToContaner(container3, argc, argv);
	// // jb_displayContaner(container3, "Before: ");
	// std::sort(container3.begin(),container3.end());
	// jb_displayContaner(container3, "Before: ");
	std::cout << "comparesons made -> "<< g_comperisons<< std::endl;
	return 0;
}
