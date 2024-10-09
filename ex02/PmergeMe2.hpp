#pragma once
#include "../mycolor.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <iomanip>

// template section

// one global to keep count of the comperisons
int g_comperisons;

// copy the argument to a container that has a push_back function
template<typename T>
void	jb_argumentToContaner(T & int_container, int argc, char const **argv)
{
	for (int i = 1; i < argc; i++)
	{
		int_container.push_back(std::stoi(argv[i]));
	}
}

// displays in standard out the contents of a container with pointers plus a message before
template<typename T>
void	jb_displayContanerpointer(T & int_container, std::string message, bool display_pairs)
{
	size_t		size = int_container.size();

	if (size > 30)
		size = 30;
	std::cout << std::setw(15) << std::left << message;
	for (size_t i = 0; i < size; i++)
	{
		if (display_pairs)
			std::cout << *(int_container[i] - 1) << " ";
		std::cout << *int_container[i] << " ";
	}
	if (size < int_container.size())
		std::cout << "[...]";
	std::cout << std::endl;
}
template<typename T>
void	jb_displayContanerToContainer(T & int_container, std::string message, bool display_pairs)
{
	size_t		size = int_container.size();

	if (size > 30)
		size = 30;
	std::cout << std::setw(15) << std::left << message;
	for (size_t i = 0; i < size; i++)
	{
		if (display_pairs)
			std::cout << (int_container[i][0]) << " ";
		std::cout << int_container[i][1] << " ";
	}
	if (size < int_container.size())
		std::cout << "[...]";
	std::cout << std::endl;
}
// displays in standard out the contents of a container plus a message before
template<typename T>
void	jb_displayContaner(T & int_container, std::string message)
{
	size_t		size = int_container.size();

	if (size > 30)
		size = 30;
	std::cout << std::setw(15) << std::left << message;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << int_container[i] << ", ";
	}
	if (size < int_container.size())
		std::cout << "[...]";
	std::cout << std::endl;
}
// overload in case its not a container
int find_number(int pairs)
{
	// std::type_info;

	return pairs;

}
// returns the first and largest number of the pair container
template<typename T>
int find_number(T pairs)
{
	// if (std::is_same<std::pair<int,int>, T>::value)
	// {
	// 	int i = pairs[0];
	// 	return i;
	// }
	// else if (!std::is_same<int, T>::value)
	// 	return	find_number(pairs[0]);
	return find_number(pairs[0]);
}
// displays the pair container in std::out if bool = true displays the connected pair before the larger one
template<typename T>
void	jb_display_pairs(T & int_container, std::string message, bool display_pairs)
{
	size_t		size = int_container.size();

	if (size > 30)
		size = 30;
	std::cout << std::setw(15) << std::left << message;
	for (size_t i = 0; i < size; i++)
	{
		if (display_pairs)
			std::cout << find_number(int_container[i][int_container[i].size() / 2]) << "-";
		std::cout << find_number( int_container[i]) << " ";
	}
	if (size < int_container.size())
		std::cout << "[...]";
	std::cout << std::endl;
}

// Recursive function to generate nth Jacobsthal number
unsigned int jacobsthal(unsigned int n){
	// first base case
	if (n == 0)
		return 0;

	// second base case
	if (n == 1)
		return 1;

	// recurse!
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}
// megre two containers and returns a new conatianer consisting of the two after each other 
template<typename T>
T merge_container(T first, T second)
{
	T container(first);
	for (typename T::iterator it = second.begin(); it != second.end(); it++)
		container.push_back(*it);
	return container;
}
// overload in case its not a container
int split_container_front(int pairs)
{
	return pairs;
}
// overload in case its not a container
int split_container_back(int pairs)
{
	return pairs;
}
// splits a container and returns a new container of the front half
template<typename T>
T split_container_front(T pairs)
{
	T container;
	for (typename T::iterator it = pairs.begin(); it != pairs.begin() + pairs.size() / 2; it++)
		container.push_back(*it);
	return container;
}
// splits a container and returns a new container of the back half
template<typename T>
T split_container_back(T pairs)
{
	T container;
	for (typename T::iterator it = pairs.begin() + pairs.size() / 2; it != pairs.end(); it++)
		container.push_back(*it);
	return container;
}
// arg1 > arg2
// the only function to compair the content of the containers and thus easy counting of comperisons 
template< typename L,typename ELEM>
bool compare_higher_than(L element1, ELEM element2){
	g_comperisons++;
	if (find_number(element1) > find_number(element2))
		return true;
	return false;
}
template< typename L>
void insertion_sort2(L &final_container, int element , unsigned int start, unsigned int size)
{
	if (start >= size)
	{
		final_container.insert((final_container.begin()+start),element);
		return;
	}
	unsigned int middel = (size - start) / 2 + start;
	// std::cout <<"start; "<< start <<"middel; " <<middel <<" size; "<<size << " elem; "<< find_number(element)<< "\n";
	if ( compare_higher_than(element, final_container[middel]) )
		insertion_sort2(final_container, element, middel +1, size);
	else
		insertion_sort2(final_container, element, start, middel );
}
template<typename T, typename L>
void insertion_sort1(T &split_array, L &final_container, int stragler , unsigned int last_jacob,unsigned int jacob_insertion_sequence,bool &is_stargler)
{
	for (unsigned int i = 0 ;jacob_insertion_sequence > last_jacob + i; i++)
	{
		if (last_jacob + i < split_array.size())
			final_container.push_back(split_container_front(split_array[last_jacob + i])[0]);
	}
	unsigned int size = final_container.size() - 1;
	for (unsigned int i = 1 ;jacob_insertion_sequence - i >= last_jacob; i++)
	{
		if (is_stargler && jacob_insertion_sequence > split_array.size())
		{
			insertion_sort2(final_container, stragler, 0, final_container.size());
			is_stargler = false;
			size++;
		}
		if (jacob_insertion_sequence - i < split_array.size())
		{
			insertion_sort2(final_container, split_container_back(split_array[jacob_insertion_sequence - i])[0], 0, size);
		}
	}
}
// the overload function it does the same as te other except it won't go as deep in the array to prevent a seq
template<typename T, typename L>
void insertion_sort(T &split_array, L &final_container, int stragler , bool is_stragler)
{
	unsigned int jacob_insertion_sequence = 0;  // the next index to start inserting 
	unsigned int jacob_last = 1; // have already done the first one 
	unsigned int jacob_index = 3; // The first one that matters

	while (jacob_last < split_array.size() || is_stragler)
	{
		jacob_insertion_sequence = jacobsthal(jacob_index);
		insertion_sort1(split_array,final_container, stragler,jacob_last, jacob_insertion_sequence, is_stragler);
		jacob_index++;
		jacob_last = jacob_insertion_sequence;
	}
}

template< typename L,typename ELEM>
void insertion_sort2(L &final_container, ELEM element , unsigned int start, unsigned int size)
{
	if (start >= size)
	{
		final_container.insert((final_container.begin()+start),element);
		return;
	}
	unsigned int middel = (size - start) / 2 + start;
	// std::cout <<"start; "<< start <<"middel; " <<middel <<" size; "<<size << " elem; "<< find_number(element)<< "\n";
	if ( compare_higher_than(element, final_container[middel]) )
		insertion_sort2(final_container, element, middel +1, size);
	else
		insertion_sort2(final_container, element, start, middel );
}
template<typename T, typename L,typename ELEM>
void insertion_sort1(T &split_array, L &final_container, ELEM stragler , unsigned int last_jacob,unsigned int jacob_insertion_sequence,bool &is_stargler)
{
	for (unsigned int i = 0 ;jacob_insertion_sequence > last_jacob + i; i++)
	{
		if (last_jacob + i < split_array.size())
			final_container.push_back(split_container_front(split_array[last_jacob + i]));
	}
	unsigned int size = final_container.size() - 1;
	for (unsigned int i = 1 ;jacob_insertion_sequence - i >= last_jacob; i++)
	{
		if (is_stargler && jacob_insertion_sequence > split_array.size())
		{
			insertion_sort2(final_container, stragler, 0, final_container.size());
			is_stargler = false;
			size++;
		}
		if (jacob_insertion_sequence - i < split_array.size())
		{
			insertion_sort2(final_container, split_container_back(split_array[jacob_insertion_sequence - i]), 0, size);
		}
	}
}
// has 3 fases 1 makes the jacob numbers for the correct order of insertion
// 2 uses the jacob number and finds the sequence to insert
// 3 uses binary search to insert the number in the correct place
template<typename T, typename L,typename ELEM>
void insertion_sort(T &split_array, L &final_container, ELEM stragler , bool is_stragler)
{
	unsigned int jacob_insertion_sequence = 0;  // the next index to start inserting 
	unsigned int jacob_last = 1; // have already done the first one 
	unsigned int jacob_index = 3; // The first one that matters

	while (jacob_last < split_array.size() || is_stragler)
	{
		jacob_insertion_sequence = jacobsthal(jacob_index);
		insertion_sort1(split_array,final_container, stragler,jacob_last, jacob_insertion_sequence, is_stragler);
		jacob_index++;
		jacob_last = jacob_insertion_sequence;
	}
}

template<typename T>
T ford_johnson1(T &container)
{
	size_t		size = container.size();
	T			sub_container;
	
	// split container in pairs where the lager is before the smaller numbers groep
	// then make a sub_container consisting of numbers begining with de larger of the par followed by the previus pairs than
	// merging with the lower of the pair folowed by its previous pairs
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if ( compare_higher_than(container[i], container[i + 1]) )
		{
			sub_container.push_back(merge_container(container[i], container[i + 1]));
		}
		else
		{
			sub_container.push_back(merge_container(container[i+1], container[i]));
		}
	}
	// the first recursion need differant types and this template is already diffined
	if (sub_container.size() > 1)
		sub_container = ford_johnson1(sub_container);
	// jb_display_pairs(sub_container, "test; ", false);

	T final_container;

	// save a comperison by manualy inerting the first pair
	final_container.push_back(split_container_back(sub_container[0]));
	final_container.push_back(split_container_front(sub_container[0]));
	// give straglers or not
	if (size % 2 != 0)
		insertion_sort(sub_container,final_container,container.back(),true);
	else
		insertion_sort(sub_container,final_container,container.back(),false);
	return final_container;
}

// sorts a int container with the ford_johnson algaritme.
// the template strips the container argument type so we still need to define them, including the default allocator type.
// and I used container features that limit the containers pool to vectors and deques.
template<template<typename ELM,typename ALLOC> class T, typename TYPE, typename PAIR_TYPE>
T<TYPE,std::allocator<TYPE>> ford_johnson(T<TYPE,std::allocator<TYPE>> &container)
{
	size_t				size = container.size();
	T<T<TYPE,std::allocator<TYPE>>,std::allocator<T<TYPE,std::allocator<TYPE>>>>	sub_container;
	
	// split container in pairs where the lager is before the smaller numbers groep
	// then make a sub_container consisting of numbers begining with de larger of the par followed by the previus pairs than
	// merging with the lower of the pair folowed by its previous pairs
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if ( compare_higher_than(container[i], container[i + 1]) )
		{
			T<TYPE,std::allocator<TYPE>> pair(1, container[i]);
			pair.push_back(container[i + 1]);
			sub_container.push_back(pair);
		}
		else
		{
			T<TYPE,std::allocator<TYPE>> pair(1, container[i + 1]);
			pair.push_back(container[i]);
			sub_container.push_back(pair);
		}
	}
	// the first recursion need differant types and this template is already diffined
	if (sub_container.size() > 1)
		sub_container = ford_johnson1(sub_container);
	// jb_display_pairs(sub_container, "test; ", true);

	T<TYPE,std::allocator<TYPE>> final_container;
	// save a comperison by manualy inerting the first pair
	final_container.push_back(split_container_back(sub_container[0])[0]);
	final_container.push_back(split_container_front(sub_container[0])[0]);
	// give straglers or not
	if (size % 2 != 0)
		insertion_sort(sub_container,final_container,container.back(),true);
	else
		insertion_sort(sub_container,final_container,container.back(),false);
	// std::cout << std::setw(15) << std::left << g_comperisons  - com<< "\n";
	return final_container;
}
