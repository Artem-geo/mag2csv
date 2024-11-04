#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
    Date(int year, int month, int day);
    Date();
    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    std::string toString();
private:
    int year, month, day;
};



#endif //DATE_H
