#include "BitcoinExchange.hpp"
#include "../mycolor.hpp"

BitcoinExchange::BitcoinExchange() {
	
}

BitcoinExchange::BitcoinExchange( std::string const & date ) {
	this->_year = std::atoi(date.c_str());
	this->_month = std::atoi(date.substr(5,2).c_str());
	this->_days = std::atoi(date.substr(8,2).c_str());
}
BitcoinExchange::BitcoinExchange( BitcoinExchange const & src ) {
	*this = src;
}
BitcoinExchange::~BitcoinExchange() {

}

BitcoinExchange & BitcoinExchange::operator=( BitcoinExchange const & rhs ) {
	this->_year = rhs._year;
	this->_month = rhs._month;
	this->_days = rhs._days;
	return *this;
}
std::ostream & operator<<( std::ostream & o, BitcoinExchange const & rhs) {
	o << rhs.getDateWithOffset(0);
	return o;
}

std::string			BitcoinExchange::getDateWithOffset(int offset)const {
	std::string new_date;
	int			days = this->_days + offset;
	int			month = this->_month;
	int			year = this->_year;

	while (days > BitcoinExchange::daysInMonth(this->_month, this->_year)){
		days -= BitcoinExchange::daysInMonth(this->_month, this->_year);
		month += 1;
		if (month > 12)
		{
			year += 1;
			month = 1;
		}
	}
	new_date = std::to_string(year);
	new_date += "-";
	if (month < 10)
		new_date += "0";
	new_date += std::to_string(month);
	new_date += "-";
	if (days < 10)
		new_date += "0";
	new_date += std::to_string(days);
	return new_date;
}
bool				BitcoinExchange::validDate( BitcoinExchange const & rhs ) {
	if (rhs._month < 1 || rhs._month > 12)
	{
		return false;
	}
	if (rhs._days < 1 || rhs._days > BitcoinExchange::daysInMonth(rhs._month, rhs._year))
	{
		return false;
	}
	return true;
}
bool				BitcoinExchange::isLeapYear(int year ) {
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
int					BitcoinExchange::daysInMonth( int month, int year ) {
		static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (month == 2 && isLeapYear(year)) {
			return 29;
		}
		return daysInMonth[month - 1];
}

