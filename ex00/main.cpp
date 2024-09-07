#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include "../mycolor.hpp"
#include "BitcoinExchange.hpp"
#include <iomanip>
// int		date_to_days(std::string date)
// {
// 	int days = 0;
// 	int year = std::stoi(date.substr(0,4));
// 	int month = std::stoi(date.substr(5,2));

// 	for (int i = 0; i < year; ++i)
// 		days += isLeapYear(i) ? 366 : 365;
// 	std::cout << days << "\n";
// 	for (int i = 1; i < month; ++i)
// 		days += daysInMonth(i, year);
// 	days += std::stoi(date.substr(8));
// 	// return year * 365 + month * 30 + day; 
// 	return days;
// }
// int		date_to_day(std::string date)
// {
// 	int days = 0;
// 	int year = std::stoi(date.substr(0,4));
// 	int month = std::stoi(date.substr(5,2));

// 	for (int i = 0; i < year; ++i)
// 		days += isLeapYear(i) ? 366 : 365;
// 	std::cout << days << "\n";
// 	for (int i = 1; i < month; ++i)
// 		days += daysInMonth(i, year);
// 	days += std::stoi(date.substr(8));
// 	// return year * 365 + month * 30 + day; 
// 	return days;
// }
// int		days_in_differance(std::string date1, std::string date2)
// {
// 	int days;

// 	days = date_to_days(date1) - date_to_days(date2);
// 	if (days < 0)
// 		days *= -1;
// 	return days;
// }

bool	is_date(char a)
{
	std::string str("0123456789-");
	if (a != '\0' && str.find(a) < str.size())
		return true;
	return false;
}

void splitDateAndNumber(std::string& date, float& number) {
	unsigned int index = 0;
	while(index < date.size() && is_date(date[index]))
		index++;
	while(index < date.size() && !is_date(date[index]))
		index++;
	if (is_date(date[index]))
		number = std::stod(date.substr(index));
	else
		number = -1;
	index = 0;
	while(index < date.size() && is_date(date[index]))
		index++;
    date = date.substr(0, index);
}

void	find_bitexchange(std::map<std::string , float> &data, std::string & line, float & number){
	BitcoinExchange bitcoin(line);
	std::map<std::string , float>::iterator it;
	std::map<std::string , float>::iterator ite = data.end();
	int	offset = 0;
	if (number > 1000)
	{
		std::cout << FG_RED << "Error: too large a number. => "<< line << FG_DEFAULT << std::endl;
		return;
	}
	if (number < 0)
	{
		std::cout << FG_RED << "Error: negative or no number. => "<< line << FG_DEFAULT << std::endl;
		return;
	}
	
	if (!BitcoinExchange::validDate(bitcoin)){
		std::cout << FG_RED << "Error: date invalid => "<< line << FG_DEFAULT << std::endl;
		return;
	}
	while ((it = data.find(bitcoin.getDateWithOffset(offset))) == ite && offset < 1000)
		offset++;
	if (offset >= 1000){
		std::cout << FG_RED << "Error: no date found within 1000 days => "<< line << FG_DEFAULT << std::endl;
		return;
	}
	std::cout << FG_LBLUE << line << " >= " << number << " = " << std::setprecision(5)<< number * it->second << FG_DEFAULT << std::endl;
	// std::cout << FG_LBLUE << line << " >= " << number << " = "<< it->first<<" " << std::setprecision(5)<< it->second << FG_DEFAULT << std::endl;
}

void	get_from_files2(std::map<std::string , float> &data, std::string file){
	std::fstream	read_file;
	std::string		line;
	float			number;

	read_file.open(file.c_str(),std::fstream::in);
	if (!read_file.is_open()){
		std::cout << FG_RED << "Error: can't open file => "<< file << FG_DEFAULT << std::endl;
		return;
	}
	std::getline(read_file,line);
	while (std::getline(read_file,line))
	{
		splitDateAndNumber(line, number);
		find_bitexchange(data, line, number);
	}
	read_file.close();
}

void	get_from_files(std::map<std::string , float> &data, std::string file){
	std::fstream	read_file;
	std::string		line;
	float			number;

	read_file.open(file.c_str(),std::fstream::in);
	if (!read_file.is_open()){
		std::cout << FG_RED << "Error: can't open file => "<< file << FG_DEFAULT << std::endl;
		return;
	}
	while (std::getline(read_file,line))
	{
		splitDateAndNumber(line, number);
		data.insert(std::pair<std::string , float> (line, number));
	}
}

int		main(int argc, char const *argv[]){
	std::map<std::string , float> data;

	if (argc != 2)
	{
		std::cout << FG_RED"Error: Program needs a file name"<< FG_DEFAULT<< std::endl;
		return 1;
	}
	get_from_files(data, "data.csv");
	get_from_files2(data, argv[1]);
	return 0;
}
