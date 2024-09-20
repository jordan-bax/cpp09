#pragma once
#include "../mycolor.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <iomanip>

// template section

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

// Merge two sorted halves into a single sorted array
template<typename T>
void merge(T & arr, int left, int mid, int right) {
	int left_size = mid - left + 1; // Size of the left half
	int right_size = right - mid;    // Size of the right half

	// Create temporary vectors for left and right halves
	T leftArr(left_size);
	T rightArr(right_size);

	// Copy data to temporary vectors
	for (int i = 0; i < left_size; ++i)
		leftArr[i] = arr[left + i];
	for (int j = 0; j < right_size; ++j)
		rightArr[j] = arr[mid + 1 + j];

	// Merge the temporary vectors back into the original array
	int i = 0, j = 0, k = left;
	while (i < left_size && j < right_size) {
		if (*leftArr[i] <= *rightArr[j]) {
			arr[k] = leftArr[i];
			++i;
		} else {
			arr[k] = rightArr[j];
			++j;
		}
		++k;
	}

	// Copy any remaining elements of leftArr
	while (i < left_size) {
		arr[k] = leftArr[i];
		++i;
		++k;
	}

	// Copy any remaining elements of rightArr
	while (j < right_size) {
		arr[k] = rightArr[j];
		++j;
		++k;
	}
}

// Recursive Merge Sort function
template<typename T>
void merge_sort(T& arr, int left, int right) {
	if (left >= right) {
		return; // Base case: when the array has one or zero elements, it's already sorted
	}

	int mid = left + (right - left) / 2;

	// Sort the first and second halves
	merge_sort(arr, left, mid);
	merge_sort(arr, mid + 1, right);

	// Merge the sorted halves
	merge(arr, left, mid, right);
}

// sorts a int container with the ford_johnson algaritme.
// the template strips the container argument type so we still need to define them, including the default allocator type.
// and I used container features that limit the containers pool to vectors and deques.
template<template<typename ELM,typename ALLOC> class T>
T<int,std::allocator<int>> ford_johnson(T<int,std::allocator<int>> &container)
{
	size_t				size = container.size();
	T<int*,std::allocator<int*>>	sub_container;
	std::array<int,2>	pairs_container[size / 2]; // it needs to be a array or vector to make sure the contents are orderd after each other in memory

	// split container in pairs where the lager is after the smaller number
	// then make a pointer sub_container consisting of the addres of the larger number of each pair
	for (size_t i = 0; i + 1 < size; i+=2)
	{
		if (container[i] > container[i + 1])
		{
			pairs_container[i / 2][0] = container[i + 1];
			pairs_container[i / 2][1] = container[i];
			sub_container.push_back(&pairs_container[i / 2][1]);
		}
		else
		{
			pairs_container[i / 2][0] = (container[i]);
			pairs_container[i / 2][1] = (container[i + 1]);
			sub_container.push_back(&pairs_container[i / 2][1]);
		}
	}

	// sort recursively the sub_container
	merge_sort(sub_container, 0, sub_container.size() - 1);
	size = sub_container.size();
	T<int,std::allocator<int>> final_container;

	// save a comperison by manualy inerting the first pair
	final_container.push_back(*(sub_container[0] - 1));
	final_container.push_back(*(sub_container[0]));

	// insert using lower_bound (a binary search) the smaler number of the pairs that was sorted by the larger numbers of each pair
	// then add at the back the larger number that we know should be the largest number at that moment
	for (size_t i = 1; i < size; i++)
	{
		final_container.insert(std::lower_bound(final_container.begin(),final_container.end(),*(sub_container[i]-1)),*(sub_container[i] - 1));
		final_container.push_back(*(sub_container[i]));
	}

	// check for odd size and insert the last number if true
	size = container.size();
	if (size % 2 == 1)
		final_container.insert(std::lower_bound(final_container.begin(),final_container.end(),container.back()),container.back());
	return final_container;
}
