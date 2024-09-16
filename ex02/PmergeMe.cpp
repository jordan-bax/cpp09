
#include "../mycolor.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <iomanip>
#include <algorithm>

#include "PmergeMe.hpp"
#include <chrono>
#include "../mycolor.hpp"

// Recursive function to generate nth Jacobsthal number
int jacobsthal(int n){
	// first base case
	if (n == 0)
		return 0;

	// second base case
	if (n == 1)
		return 1;

	// recurse!
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

// Built a sequence of valid jacobsthal numbers, given an array length
std::vector<int> build_jacob_insertion_sequence (std::vector<int> array){
	// Store some variables, set some up for returning
	unsigned int array_len = array.size();
	std::vector<int> end_sequence;
	int jacob_index = 3; // The first one that matters

	// Loop through and create the sequence
	while (static_cast<unsigned>(jacobsthal(jacob_index)) < array_len -1)
	{
		end_sequence.push_back(jacobsthal(jacob_index));
		jacob_index += 1;
	}

	// Return it for user
	return end_sequence;
}

// Create Sequence
std::vector<int> create_s(std::vector<std::vector<int>> sorted_split_array,int straggler,bool print_comparision_estimation)
{
	// Placeholders for the key sequences
	std::vector<int> S;
	std::vector<int> pend;

	// Comparison Counter
	int comparisions_made = 0;

	// Split the pairs into the main sequences.
	for (unsigned int i = 0; sorted_split_array.size() > i; i++)
	{
		// Add the larger elements into 'main'
		S.push_back((sorted_split_array[i])[1]);
		// add smaller elements into 'pend'
		pend.push_back((sorted_split_array[i])[0]);
	}

	// Insert the first element in S -- we know it's the smallest, since it
	// was already sorted smaller in the first pairing
	S.insert(S.begin(), pend[0]);

	// Now, we need to build an insertion sequence, taking advantage of the
	// Jacobsthal number set

	// Store some placeholders
	unsigned int iterator = 0; // We already added one
	int jacobindex = 3; // Start at three, since we already inserted 1 and we can skip the beginning of this sequence
	std::vector<int> indexSequence; 
	indexSequence.push_back(1); // Index sequence for reporting purposes (and sanity)
	std::string last = "default"; // Not the most elegant solution, but store a string so we know when if the last sequence entry was a Jacobsthal number
	int item;
	// build the valid jacobsthal sequence, then we can fill in the rest
	std::vector<int> jacob_insertion_sequence = build_jacob_insertion_sequence(pend);

	// iterate through the rest of 'pend'
	while (iterator <= pend.size())
	{
		// if we have a valid jacobsthal index, let's use it!
		if (jacob_insertion_sequence.size() != 0 && last != "jacob")
		{

			indexSequence.push_back(jacob_insertion_sequence[0]);
			item = pend[jacob_insertion_sequence[0] - 1];
			// Now pop it off
			jacob_insertion_sequence.erase(jacob_insertion_sequence.begin());
			last = "jacob";
		}
		else
		{
			// Else, let's fill it with what's remaining most efficently
			// First, make sure the jacob number wasn't already used
			if (std::find(indexSequence.begin(),indexSequence.end(), iterator) != indexSequence.end())
				iterator += 1;
			item = pend[iterator - 1];
			indexSequence.push_back(iterator);
			last = "not-jacob";
		}
		// we now have the most optimal item to insert (with the least comparisons!).
		// lets use bisect to get the insertion point
		// insertion_point = bisect.bisect(S, item, 0, len(S))

		// then insert it into S!
		S.insert(std::lower_bound(S.begin(),S.end(),item),item);
//		S.insert(insertion_point, item)

		// Increment our iterators
		iterator += 1;
		jacobindex += 1;

		// Update comparisions counter
		comparisions_made += 2;

	}
	// If an odd numbered array was given, we took off the straggler in the beginning
	// We now binary search insert the entire array for this one, following the algo.
	if (straggler != -1)
	{
		S.insert(std::lower_bound(S.begin(),S.end(),straggler),straggler);
		comparisions_made += 2;
	}

		// insertion_point = bisect.bisect(S, straggler, 0, len(S))
		// S.insert(insertion_point, straggler)

	if (print_comparision_estimation)
		std::cout << "Approximate Comparisions Made: " << comparisions_made << std::endl;

	return S;
}

// Split into pairs
std::vector<std::vector<int>> create_pairs(std::vector<int> container)
{
	unsigned int size = container.size();
	// Create local stores for use
	std::vector<std::vector<int>>	pairs_container(size / 2); // it needs to be a array or vector to make sure the contents are orderd after each other in memory

	// split container in pairs where the lager is after the smaller number
	// then make a pointer sub_container consisting of the addres of the larger number of each pair
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if (container[i] > container[i + 1])
		{
			pairs_container[i / 2].push_back(container[i + 1]);
			pairs_container[i / 2].push_back(container[i]);
			// sub_container.push_back(&pairs_container[i / 2][1]);
		}
		else
		{
			pairs_container[i / 2].push_back(container[i]);
			pairs_container[i / 2].push_back(container[i + 1]);
			// pairs_container[i / 2][0] = (container[i]);
			// pairs_container[i / 2][1] = (container[i + 1]);
			// sub_container.push_back(&pairs_container[i / 2][1]);
		}
	}

	//count += 1

	return pairs_container;
}
// Sort all the pairs
// def sort_each_pair (split_array)
// {
// 	for pair in split_array:
// 	// compare values in each pair and sort
// 	if len(pair) != 1 and (pair[0] > pair[1]):
// 		temp = pair[0]
// 		pair[0] = pair[1]
// 		pair[1] = temp;

// 	return split_array
// }

// build utility functions for recursive insertion sort by highest value in pair
std::vector<std::vector<int>> insert(std::vector<int>	element, std::vector<std::vector<int>> &A, size_t n)
{
	// jb_displayContaner(element,"ll");
	// std::cout <<n<< "test\n";
	if (n < 0)
		A[0] = element;
	else if (element[1] >= (A[n])[1])
	{
		if (n == A.size()-1)
			A.push_back(element);
		else
			A[n+1] = element;
	}
	else
	{
		if (n == A.size()-1)
			A.push_back(A[n]);
		else
		{
			A[n+1] = A[n];
			if (n > 0)
				insert(element, A, n-1);
			else
				A[0] = element;
		}
	}
	return A;
}

// entry function to recusrively sort pairs by their higher value
std::vector<std::vector<int>> insertion_sort_pairs(std::vector<std::vector<int>> &split_array, unsigned int size)
{
	if (size < 1)
		return split_array;
	else
	{
		insertion_sort_pairs(split_array, size - 1);
		insert(split_array[size], split_array, size - 1);
	}
	return split_array;
}
// Recursively sort the larger set of elements into sorted set
void sort_by_larger_value(std::vector<std::vector<int>> & sorted_split_array)
{
	// Grab the length
	// length = len(sorted_split_array)
	// recursively sort the pairs by largest element
	insertion_sort_pairs(sorted_split_array, (sorted_split_array.size() -1));
	jb_displayContanerToContainer(sorted_split_array, "test; ", false);
}

std::vector<int> merge_insertion_sort (std::vector<int> A){
	int	straggler;
	std::vector<int> S;
	// Print out Given Array, for clarity
   

	// Determine if it's odd numbered... if so, take off a straggler
	if ( A.size() % 2 != 0)
	{
		straggler = A.back();
		A.pop_back();
	}
	else
		straggler = -1;

	// Then Split Array into Pairs
	std::vector<std::vector<int>>	split_array = create_pairs(A);

	// Sort each pair of elements
	std::vector<std::vector<int>>	sorted_split_array = split_array;//sort_each_pair(split_array)

	jb_displayContaner(A, "starting: ");
	// Recursively sort the pairs by their largest element
	sort_by_larger_value(sorted_split_array);

	// // Create main and pend sequences and merge insertion sort
	S = create_s(sorted_split_array, straggler, true);

	// // Print it to the user
	// print("Sorted Array:");
	// print(S);

	// Return it to the user
	return S;
}

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
	// start time by getting the current system time
	start = std::chrono::high_resolution_clock::now();
	jb_argumentToContaner(container2, argc, argv);
	container2 = ford_johnson<std::deque>(container2);
	// end time by getting the current system time
	end = std::chrono::high_resolution_clock::now();
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
	return 0;
}