#pragma once
#include "../mycolor.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iomanip>

// template section
template<typename T>
void	jb_argumentToContaner(T & int_container, int argc, char const **argv)
{
	for (int i = 1; i < argc; i++)
	{
		int_container.push_back(std::stoi(argv[i]));
	}
}
template<typename T>
void	jb_displayContaner(T & int_container, std::string message)
{
	int		size = int_container.size();

	if (size > 30)
		size = 30
	std::cout << std::setw(15) << std::left << message;
	for (int i = 0; i < size; i++)
	{
		std::cout << int_container[i] << " ";
	}
	if (size < int_container.size())
		std::cout << "[...]";
	std::cout << std::endl;
}
/*
67 85 31 24
67 58 13 24
7834
lv 2
78 34
78 34
84
lv 3
48
l2 
48
348
b search 7
3478
lv 1
3478
13478
b search 2
b search 5
b search 6
12345678
*/
std::vector<int> ford_jonson(std::vector<int> container)
{
	std::vector<int> sub_container;
	for (size_t i = 0; i < container.size(); i+=2)
	{
		
	}
	
}