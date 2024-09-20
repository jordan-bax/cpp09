#include "../mycolor.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <iomanip>
#include <algorithm>

#include "PmergeMe2.hpp"
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
	std::vector<std::pair<int,int>> container2;
	container2.push_back(std::pair<int , int> (5,6));
	container2[0].first;
	container2[0].second;
	container2[0];
	std::string s_container1;
	std::pair<int,int> s();
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

	// start time by getting the current system time
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	// place the argument in container and execute the ford jonson
	jb_argumentToContaner(container1, argc, argv);
	jb_displayContaner(container1, "Before: ");
	container1 = merge_insertion_sort(container1);
	jb_displayContaner(container1, "After: ");
	// end time by getting the current system time
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	// calculate the time spend by milliseconds inside a double type
	std::chrono::duration<double, std::milli> ms_double = end - start;
	std::cout << s_container1<<"Time to process a range of "<<container1.size()
		<<" elements with std::vector : "<< ms_double.count() << "ms\n" FG_DEFAULT;
	return 0;
}