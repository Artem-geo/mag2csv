#include "Date.h"
#include <stdexcept>
#include <iostream>

 Date::Date(int year, int month, int day)
     : year(year), month(month), day(day) {  }
 Date::Date()
     : Date(1857, 07, 10) {  }
void Date::setYear(int year_input) {
    if (year_input<0) throw std::invalid_argument("Year value can't be negative");
    year = year_input;
}
void Date::setMonth(int month_input) {
    if(month_input<0) throw std::invalid_argument("Month can't be negative");
    if(month_input>12 || month_input==0) throw std::invalid_argument("Month can't be = 0 or > 12");
    month = month_input;
}
void Date::setDay(int day_input) {
    if(day_input<0) throw std::invalid_argument("Day can't be negative");
    if(day_input==0 || day_input>31) throw std::invalid_argument("Day can't be = 0 or > 31");
    day = day_input;
}
int Date::getYear() const {
    return year;
}
int Date::getMonth() const {
    return month;
}
int Date::getDay() const {
    return day;
}
std::string Date::toString() {
    std::string date_string = std::to_string(year) + "-";
     // add preceding zero if month and/or day is one digit number
    date_string += ((month<10) ? "0" : "") + std::to_string(month) + "-";
    date_string += ((day<10) ? "0" : "") + std::to_string(day);
    return date_string;
}




