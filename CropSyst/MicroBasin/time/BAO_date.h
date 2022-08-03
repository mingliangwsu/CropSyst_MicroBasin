#ifndef DATE_H
#define DATE_H
#include <iostream>

//Code is copied from Bernt Arne Odegaard (2007)
namespace BAO                                                                    //131121
// Date must be in a namespace otherwise it is ambiguous. RLN
{
const int month_start_day_nonleapyear[] = {1,32,60,91,121,152,182,213,244,274,305,335};
const int month_start_day_leapyear[] = {1,32,61,92,122,153,183,214,245,275,306,336};
const int monthdays_nonleapyear[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const int monthdays_leapyear[] = {31,29,31,30,31,30,31,31,30,31,30,31};

//______________________________________________________________________________
class Date
{
protected:
    int year_;
    int month_;                 //1-12
    int day_;                   //1-31
public:
    Date();
    Date(const int& d, const int& m, const int& y);
    Date(const int _year, const int _yday); //_yday: 1-365/366
    bool valid(void) const;
    int get_DOM() const;
    int get_month() const;
    int get_year() const;
    int get_DOY() const;               //1-365/366
    void setDay (const int day);
    void setMonth (const int month);
    void setYear (const int year);
    void set_YMD(const int year,const int month,const int day);
    void set_YD(const int _year,const int _yday);
    bool isLeapYear() const;
    bool isFirstDayOfYear() const;
    bool is_last_DOY() const;


    Date operator ++();             // prefix
    Date operator ++(int);          // postfix
    Date operator --();               // prefix
    Date operator --(int);            // postfix
};

bool operator == (const Date&, const Date&); // comparison operators
bool operator != (const Date&, const Date&);
bool operator < (const Date&, const Date&);
bool operator > (const Date&, const Date&);
bool operator <= (const Date&, const Date&);
bool operator >= (const Date&, const Date&);
std::ostream& operator << ( std::ostream& os, const Date& d); // output operator
//______________________________________________________________________________
}
#endif // DATE_H
