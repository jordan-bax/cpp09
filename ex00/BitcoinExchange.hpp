#pragma once
#include <iostream>
#include <map>

class BitcoinExchange :public std::map<std::string , float>
{
private:
	// std::map<std::string , float> _data;
	int _year;
	int _month;
	int _days;
	BitcoinExchange();

public:
	BitcoinExchange( std::string const & src );
	BitcoinExchange( BitcoinExchange const & src );
	~BitcoinExchange();

	BitcoinExchange &	operator=( BitcoinExchange const & rhs );
	std::string			getDateWithOffset(int offset)const;
	static bool			validDate( BitcoinExchange const & rhs );
	static bool			isLeapYear(int year );
	static int			daysInMonth( int month, int year );
};

std::ostream & operator<<( std::ostream & o, BitcoinExchange const & rhs);
