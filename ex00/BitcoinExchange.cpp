#include "BitcoinExchange.hpp"
#include "../mycolor.hpp"

BitcoinExchange::BitcoinExchange() {
	
}

BitcoinExchange::BitcoinExchange( std::string const & src ) {

}
BitcoinExchange::BitcoinExchange( BitcoinExchange const & src ) {

}
BitcoinExchange::~BitcoinExchange() {

}

BitcoinExchange & BitcoinExchange::operator=( BitcoinExchange const & rhs ) {
	
}
// std::ostream & operator<<( std::ostream & o, BitcoinExchange const & rhs) {
// 	o << ;
// 	return o;
// }

std::string			BitcoinExchange::getDateWithOffset(int offset)const {

}
bool				BitcoinExchange::validDate( BitcoinExchange const & rhs ) {
	if (rhs._month < 1 || rhs._month > 12)
	{
		std::cout << rhs.
		return false;
	}
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

