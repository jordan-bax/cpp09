#include "PmergeMe.hpp"
#include <chrono>


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
	// container1.
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
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
	jb_argumentToContaner(container1, argc, argv);
	jb_displayContaner(container1, "Before: ");
	ford_johnson(container1);
	jb_displayContaner(container1, "After: ");
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double = end - start;
	std::cout << ms_double.count() << "ms\n";
	return 0;
}
 
//     // Call the function, here sort()
//     sort(values.begin(), values.end());
 
//     // Get ending timepoint
//     auto stop = high_resolution_clock::now();
 
//     // Get duration. Substart timepoints to 
//     // get duration. To cast it to proper unit
//     // use duration cast method
//     auto duration = duration_cast<microseconds>(stop - start);
 
//     cout << "Time taken by function: "
//          << duration.count() << " microseconds" << endl;