#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include "../mycolor.hpp"

bool isLeapYear(int year) {  
    if (year % 4 == 0) {  
        if (year % 100 == 0) {  
            if (year % 400 == 0) {  
                return true;  
            } else {  
                return false;  
            }  
        } else {  
            return true;  
        }  
    } else {  
        return false;  
    }  
}
 int daysInMonth(int m, int y) {
        static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (m == 2 && isLeapYear(y)) {
            return 29;
        }
        return daysInMonth[m - 1];
    }

int		date_to_days(std::string date)
{
	int days = 0;
	int year = std::stoi(date.substr(0,4));
	int month = std::stoi(date.substr(5,2));

	for (int i = 0; i < year; ++i)
		days += isLeapYear(i) ? 366 : 365;
	for (int i = 1; i < month; ++i)
		days += daysInMonth(i, year);
	std::cout << days << "\n";
	days += std::stoi(date.substr(8));
	// return year * 365 + month * 30 + day; 
	return days;
}
int		days_in_differance(std::string date1, std::string date2)
{
	int days;

	days = date_to_days(date1) - date_to_days(date2);
	if (days < 0)
		days *= -1;
	return days;
}

bool	is_date(char a)
{
	std::string str("0123456789-");
	// std::cout << " : "<< a << "-"<< static_cast<int>(a)<<" : ";
	if (a != '\0' && str.find(a) < str.size())
		return true;
	// std::cout << "false";
	return false;
}

void splitDateAndNumber(std::string& date, float& number) {
	unsigned int index = 0;
	while(index < date.size() && is_date(date[index]))
		index++;
	while(index < date.size() && !is_date(date[index]))
		index++;
	// std::cout << date.substr(index);
    // Split the string into date and number
	if (is_date(date[index]))
		number = std::stod(date.substr(index));
	else
		number = -1;
	index = 0;
	while(index < date.size() && is_date(date[index]))
		index++;
    date = date.substr(0, index);
	// std::cout << date <<"/>"<< number<< std::endl;
}
void	get_from_files(std::map<std::string , float> &data, std::string file){
	std::fstream	read_file;
	std::string		line;
	float			number;

	read_file.open(file.c_str(),std::fstream::in);
	while (std::getline(read_file,line))
	{
		splitDateAndNumber(line, number);
		data.insert(std::pair<std::string , int> (line, number));
	}
}
// void splitDateAndNumber2(std::map<std::string , float> &data, std::string& date, float& number) {
// 	unsigned int index = 0;
// 	while(index < date.size() && is_date(date[index]))
// 		index++;
// 	while(index < date.size() && !is_date(date[index]))
// 		index++;
// 	// std::cout << date.substr(index);
//     // Split the string into date and number
// 	if (is_date(date[index]))
// 		number = std::stod(date.substr(index));// test for
// 	else
// 		number = -1;
// 	index = 0;
// 	while(index < date.size() && is_date(date[index]))
// 		index++;
//     date = date.substr(0, index);
// 	// std::cout << date <<"/>"<< number<< std::endl;
// }
// void	get_from_files2(std::map<std::string , float> &data, std::string file){
// 	std::fstream	read_file;
// 	std::string		line;
// 	float			number;

// 	read_file.open(file.c_str(),std::fstream::in);
// 	while (std::getline(read_file,line))
// 	{
// 		splitDateAndNumber(line, number);
// 	}
// 	read_file.close();
// }

int		main(int argc, char const *argv[]){
	std::map<std::string , float> data;
	std::map<std::string , float> input;

	if (argc != 2)
	{
		std::cout << FG_RED"Program needs a file name"<< FG_DEFAULT<< std::endl;
		return 1;
	}
	get_from_files(data, "data.csv");
	get_from_files(input, argv[1]);
	std::map<std::string , float>::iterator it;
	it = data.find("2014-06-27");
	std::cout<< it->first << " " << it ->second << "\n";//,577.34
	std::cout<< days_in_differance("2028-02-28","2028-03-01") << "\n";
		

	return 0;
}
