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
	// 	int i = pairs[0];
	// 	return i;
	// }
	// else if (!std::is_same<int, T>::value)
	// 	return	find_number(pairs[0]);
	return find_number(pairs[0]);
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
			std::cout << find_number(int_container[i][int_container[i].size() / 2]) << "-";
		std::cout << find_number( int_container[i]) << " ";
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

template<typename T>
T merge_container(T first, T second)
{
	T container(first);
	for (typename T::iterator it = second.begin(); it != second.end(); it++)
		container.push_back(*it);
	return container;
}
int split_container_front(int pairs)
{
	return pairs;
}
int split_container_back(int pairs)
{
	return pairs;
}
template<typename T>
T split_container_front(T pairs)
{
	T container;
	for (typename T::iterator it = pairs.begin(); it != pairs.begin() + pairs.size() / 2; it++)
		container.push_back(*it);
	return container;
}
template<typename T>
T split_container_back(T pairs)
{
	T container;
	for (typename T::iterator it = pairs.begin() + pairs.size() / 2; it != pairs.end(); it++)
		container.push_back(*it);
	return container;
}
// arg1 > arg2
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
	// jb_displayContaner(final_container, "4");
	if (start >= size)
	{
		final_container.insert((final_container.begin()+start),element);
		return;
	}
	unsigned int middel = (size - start) / 2 + start;
	std::cout <<"start; "<< start <<"middel; " <<middel <<" size; "<<size << " elem; "<< find_number(element)<< "\n";
	if ( compare_higher_than(element, final_container[middel]) )// find_number(final_container[middel]) < find_number(element))
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
			insertion_sort2(final_container, split_container_back(split_array[jacob_insertion_sequence - i])[0], 0, size);
		}
			// insertion_sort2(final_container, split_array[jacob_insertion_sequence - i].second, 0, (jacob_insertion_sequence -1) + last_jacob);
	}
}
template<typename T, typename L>
void insertion_sort(T &split_array, L &final_container, int stragler , bool is_stragler)
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
	std::cout <<"start; "<< start <<"middel; " <<middel <<" size; "<<size << " elem; "<< find_number(element)<< "\n";
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
			final_container.push_back(split_container_front(split_array[last_jacob + i]));
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
			insertion_sort2(final_container, split_container_back(split_array[jacob_insertion_sequence - i]), 0, size);
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


/*
726498521
72 64 98 53 1
7264 9853 
9853 7264
 
98 72 64 53
987654321*/
template<typename T>
T ford_johnson1(T &container, int level)
{
	size_t		size = container.size();
	T			sub_container;
	
	// split container in pairs where the lager is after the smaller number
	// then make a pointer sub_container consisting of the addres of the larger number of each pair
	int com = g_comperisons;
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if ( compare_higher_than(container[i], container[i + 1]) )//find_number(container[i]) > find_number(container[i + 1]))
		{
			sub_container.push_back(merge_container(container[i], container[i + 1]));
		}
		else
		{
			sub_container.push_back(merge_container(container[i+1], container[i]));
		}
	}
	(void)level;
	jb_display_pairs(sub_container, "test; ", true);
	if (sub_container.size() > 1)
		sub_container = ford_johnson1(sub_container, level++);
	// insertion_sort_pairs(sub_container, (sub_container.size() -1));
	// jb_display_pairs(sub_container, "test; ", false);

	T final_container;

	// save a comperison by manualy inerting the first pair
	final_container.push_back(split_container_back(sub_container[0]));
	final_container.push_back(split_container_front(sub_container[0]));
	if (size % 2 != 0)
		insertion_sort(sub_container,final_container,container.back(),true);
	else
		insertion_sort(sub_container,final_container,container.back(),false);
	jb_display_pairs(final_container, "final; ", true);
	std::cout << std::setw(15) << std::left << g_comperisons  - com<< "\n";
	return final_container;
}

// sorts a int container with the ford_johnson algaritme.
// the template strips the container argument type so we still need to define them, including the default allocator type.
// and I used container features that limit the containers pool to vectors and deques.
template<template<typename ELM,typename ALLOC> class T, typename TYPE, typename PAIR_TYPE>
T<TYPE,std::allocator<TYPE>> ford_johnson(T<TYPE,std::allocator<TYPE>> &container, int level)
{
	size_t				size = container.size();
	T<T<TYPE,std::allocator<TYPE>>,std::allocator<T<TYPE,std::allocator<TYPE>>>>	sub_container;
	
	// split container in pairs where the lager is after the smaller number
	// then make a pointer sub_container consisting of the addres of the larger number of each pair
	int com = g_comperisons;
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if ( compare_higher_than(container[i], container[i + 1]) )//find_number(container[i]) > find_number(container[i + 1]))
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
	// sub_container.push_back(merge_container(sub_container[2],sub_container[1]));
	// sub_container.push_back(split_container_back(sub_container.back()));
	// sub_container.push_back(split_container_front(sub_container[sub_container.size() -2]));
	jb_display_pairs(sub_container, "test; ", true);
	(void)level;
	if (sub_container.size() > 1)
		sub_container = ford_johnson1(sub_container, level++);
	// insertion_sort_pairs(sub_container, (sub_container.size() -1));
	jb_display_pairs(sub_container, "test; ", true);

	T<TYPE,std::allocator<TYPE>> final_container;
	// save a comperison by manualy inerting the first pair
	final_container.push_back(split_container_back(sub_container[0])[0]);
	final_container.push_back(split_container_front(sub_container[0])[0]);
	if (size % 2 != 0)
		insertion_sort(sub_container,final_container,container.back(),true);
	else
		insertion_sort(sub_container,final_container,container.back(),false);
	std::cout << std::setw(15) << std::left << g_comperisons  - com<< "\n";
	return final_container;
}
