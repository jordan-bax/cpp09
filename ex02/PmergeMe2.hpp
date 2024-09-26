#pragma once
#include "../mycolor.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <iomanip>

// template section
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
int find_number(int pairs)
{
	// std::type_info;

	return pairs;

}
template<typename T>
int find_number(T pairs)
{
	// if (std::is_same<std::pair<int,int>, T>::value)
	// {
	// 	int i = pairs.first;
	// 	return i;
	// }
	// else if (!std::is_same<int, T>::value)
	// 	return	find_number(pairs.first);
	return find_number(pairs.first);
}
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
			std::cout << find_number(int_container[i].second) << "-";
		std::cout << find_number( int_container[i].first) << " ";
	}
	if (size < int_container.size())
		std::cout << "[...]";
	std::cout << std::endl;
}
template<typename T, typename ELEM>
T insert(ELEM	element, T &A, size_t n)
{
	// jb_displayContaner(element,"ll");
	// std::cout <<n<< "test\n";
	if (n < 0)
		A[0] = element;
	else if (find_number(element.first) >= find_number((A[n]).first))
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

template<typename T>
T insertion_sort_pairs(T &split_array, unsigned int size)
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

template< typename L,typename ELEM>
bool compare_higher_than(L element1, ELEM element2){
	g_comperisons++;
	if (find_number(element1) > find_number(element2))
		return true;
	return false;
}
template< typename L,typename ELEM>
void insertion_sort2(L &final_container, ELEM element , unsigned int start, unsigned int size)
{
	// jb_displayContaner(final_container, "4");
	if (start >= size)
	{
		final_container.insert((final_container.begin()+start),element);
		return;
	}
	unsigned int middel = (size - start) / 2 + start;
	// std::cout <<"start; "<< start <<"middel; " <<middel <<" size; "<<size << " elem; "<< find_number(element)<< "\n";
	if ( compare_higher_than(element, final_container[middel]) )// find_number(final_container[middel]) < find_number(element))
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
			final_container.push_back(split_array[last_jacob + i].first);
	}
	unsigned int size = final_container.size() - 1;
	// std::cout <<"start; "<< last_jacob <<"middel; " << jacob_insertion_sequence <<" size; "<<split_array.size()<<" size; "<<final_container.size()<< "\n";
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
			insertion_sort2(final_container, split_array[jacob_insertion_sequence - i].second, 0, size);
		}
			// insertion_sort2(final_container, split_array[jacob_insertion_sequence - i].second, 0, (jacob_insertion_sequence -1) + last_jacob);
	}
}
template<typename T, typename L,typename ELEM>
void insertion_sort(T &split_array, L &final_container, ELEM stragler , bool is_stragler)
{
	unsigned int jacob_insertion_sequence = 0;
	unsigned int jacob_last = 1;
	unsigned int jacob_index = 3; // The first one that matters

	while (jacob_last < split_array.size() || is_stragler)
	{
		jacob_insertion_sequence = jacobsthal(jacob_index);
		insertion_sort1(split_array,final_container, stragler,jacob_last, jacob_insertion_sequence, is_stragler);
		jacob_index++;
		jacob_last = jacob_insertion_sequence;
		// jb_displayContaner(final_container, "ttt");
	}
}



// sorts a int container with the ford_johnson algaritme.
// the template strips the container argument type so we still need to define them, including the default allocator type.
// and I used container features that limit the containers pool to vectors and deques.
template<template<typename ELM,typename ALLOC> class T, typename TYPE, typename PAIR_TYPE>
T<TYPE,std::allocator<TYPE>> ford_johnson(T<TYPE,std::allocator<TYPE>> &container)
{
	size_t				size = container.size();
	// jb_displayContaner(container, "malloc; ");
	T<std::pair<PAIR_TYPE,PAIR_TYPE>,std::allocator<std::pair<PAIR_TYPE,PAIR_TYPE>>>	sub_container;
	// std::array<int,2>	pairs_container[size / 2]; // it needs to be a array or vector to make sure the contents are orderd after each other in memory
	
	// split container in pairs where the lager is after the smaller number
	// then make a pointer sub_container consisting of the addres of the larger number of each pair
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if ( compare_higher_than(container[i], container[i + 1]) )//find_number(container[i]) > find_number(container[i + 1]))
		{
			// pairs_container[i / 2] = container[i + 1];
			// pairs_container[i / 2][1] = container[i];
			sub_container.push_back(std::pair<PAIR_TYPE,PAIR_TYPE> (container[i], container[i + 1]));
		}
		else
		{
			// pairs_container[i / 2][0] = (container[i]);
			// pairs_container[i / 2][1] = (container[i + 1]);
			sub_container.push_back(std::pair<PAIR_TYPE,PAIR_TYPE> (container[i+1], container[i]));
		}
	}
	// jb_display_pairs(sub_container, "test; ", true);
	if (sub_container.size() > 1)
		sub_container = ford_johnson<T, std::pair::value_type, std::pair::value_type >(sub_container);
	// insertion_sort_pairs(sub_container, (sub_container.size() -1));
	// jb_display_pairs(sub_container, "test; ", false);

	// size = sub_container.size();
	T<TYPE,std::allocator<TYPE>> final_container;

	// save a comperison by manualy inerting the first pair
	final_container.push_back((sub_container[0].second));
	final_container.push_back((sub_container[0].first));
	if (size % 2 != 0)
		insertion_sort(sub_container,final_container,container.back(),true);
	else
		insertion_sort(sub_container,final_container,container.back(),false);
	// insert using lower_bound (a binary search) the smaler number of the pairs that was sorted by the larger numbers of each pair
	// then add at the back the larger number that we know should be the largest number at that moment
	// for (size_t i = 1; i < size; i++)
	// {
	// 	final_container.insert(std::lower_bound(final_container.begin(),final_container.end(),*(sub_container[i].second)),*(sub_container[i].second));
	// 	final_container.push_back(*(sub_container[i]));
	// }

	// // check for odd size and insert the last number if true
	// size = container.size();
	// if (size % 2 == 1)
	// 	final_container.insert(std::lower_bound(final_container.begin(),final_container.end(),container.back()),container.back());
	return final_container;
}
