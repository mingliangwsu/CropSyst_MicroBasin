#pragma error This class is obsolete, now used CORN::Date                        //141222RLN

#include "BAO_date.h"
#include <iostream>
#include "util/pubtools.h"
namespace BAO {

Date::Date(const int& d, const int& m, const int& y)
{
    day_ = d;
    month_ = m;
    year_ = y; // this assumes year is given fully, not Y2K corrections
};

Date::Date(const int _year, const int _yday)
{
    int stday,edday;
    bool good = 0;
    year_ = _year;

    for (int i = 0; i < 12; i++) {
        if (bLeapYear(year_)) {
            stday = month_start_day_leapyear[i];
            edday = stday + monthdays_leapyear[i] - 1;
        } else {
            stday = month_start_day_nonleapyear[i];
            edday = stday + monthdays_nonleapyear[i] - 1;
        }

        if (_yday >= stday && _yday <= edday) {
            month_ = i + 1;
            day_ = _yday - stday + 1;
            good = 1;
            i = 12;
        }
    }
    if (!good) nrerror("Date is error!");
}

void Date::set_YD(const int _year,const int _yday)
{
    int stday,edday;
    bool good = 0;
    year_ = _year;

    for (int i = 0; i < 12; i++) {
        if (bLeapYear(year_)) {
            stday = month_start_day_leapyear[i];
            edday = stday + monthdays_leapyear[i] - 1;
        } else {
            stday = month_start_day_nonleapyear[i];
            edday = stday + monthdays_nonleapyear[i] - 1;
        }

        if (_yday >= stday && _yday <= edday) {
            month_ = i + 1;
            day_ = _yday - stday + 1;
            good = 1;
            i = 12;
        }
    }
    if (!good) nrerror("Date is error!");
}

///////////////////////////// inline definitions //////////
Date::Date() {year_ = 0; month_ = 0; day_ = 0;};
int Date::get_DOM() const {return day_;};
int Date::get_month() const {return month_;};
int Date::get_year() const {return year_;};
void Date::setDay (const int day) {day_ = day;};
void Date::setMonth(const int month) {month_ = month;};
void Date::set_YMD(const int year,const int month,const int day) {year_ = year;month_ = month;day_ = day;}
void Date::setYear (const int year) {year_ = year;};
bool Date::isFirstDayOfYear() const
{
    if (get_month()==1 && get_DOM()==1) return true;
    else return false;
}

bool Date::is_last_DOY() const
{
    if (get_month()==12 && get_DOM()==31) return true;
    else return false;
}

bool Date::valid() const
{
// This function will check the given date is valid or not.
// If the date is not valid then it will return the value false.
// Need some more checks on the year, though
    if (year_ < 0) return false;
    if (month_ > 12 || month_ < 1) return false;
    if (day_ > 31 || day_ < 1) return false;
    if ((day_ == 31 &&
            (month_ == 2 || month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11)))
        return false;
    if (day_ == 30 && month_ == 2) return false;
    //if ( year_ < 2000) {
        //if ((day_ == 29 && month_ == 2) && !((year_ - 1900)%4 == 0)) return false;
    //}
    //if ( year_ > 2000) {
        //if ((day_ ==29 && month_ ==2) && !((year_ - 2000)%4==0)) return false;
    //}
    if (((year_)%400) || (!((year_)%4) && ((year_)%100))) {   //not leap year
        if (day_ == 29 && month_ == 2) return false;
    }
    return true;
};

bool operator == (const Date& d1,const Date& d2)
{
    // check for equality
    if (!d1.valid()) {return false;};
    if (!d2.valid()) {return false;};
    if ((d1.get_DOM() == d2.get_DOM())
        && (d1.get_month() == d2.get_month())
        && (d1.get_year() == d2.get_year())) {
        return true;
    };
    return false;
};

bool operator !=(const Date& d1, const Date& d2)
{
    return !(d1==d2);
};

bool operator < (const Date& d1, const Date& d2) {
    if (!d1.valid()) {return false;}; // not meaningful, return anything
    if (!d2.valid()) {return false;}; // should really be an exception, but ?
    if (d1.get_year()<d2.get_year()) {return true;}
    else if (d1.get_year()>d2.get_year()) {
        return false;
    } else { // same year
        if (d1.get_month()<d2.get_month()) {return true;}
        else if (d1.get_month()>d2.get_month()) {return false;}
        else { // same month
            if ( d1.get_DOM()<d2.get_DOM()) {return true;}
            else {return false;}
        };
    };
    return false;
};

bool operator > (const Date& d1, const Date& d2)
{
    if (d1==d2) {return false;}; // this is strict inequality
    if (d1<d2) {return false;};
    return true;
};

bool operator <=(const Date& d1, const Date& d2)
{
    if (d1==d2) {return true;};
    return (d1<d2);
};

bool operator >=(const Date& d1, const Date& d2)
{
    if (d1==d2) {return true;};
    return (d1>d2);
};

inline Date next_date(const Date& d)
{
    Date ndat;
    if (!d.valid()) {return ndat;};
    ndat=Date((d.get_DOM()+1),d.get_month(),d.get_year()); if (ndat.valid()) return ndat;
    ndat=Date(1,(d.get_month()+1),d.get_year()); if (ndat.valid()) return ndat;
    ndat = Date(1,1,(d.get_year()+1)); return ndat;
};

inline Date previous_date(const Date& d)
{
    Date ndat;
    if (!d.valid()) {return ndat;}; // return zero
    ndat = Date((d.get_DOM()-1),d.get_month(),d.get_year()); if (ndat.valid()) return ndat;
    ndat = Date(31,(d.get_month()-1),d.get_year()); if (ndat.valid()) return ndat;
    ndat = Date(30,(d.get_month()-1),d.get_year()); if (ndat.valid()) return ndat;
    ndat = Date(29,(d.get_month()-1),d.get_year()); if (ndat.valid()) return ndat;
    ndat = Date(28,(d.get_month()-1),d.get_year()); if (ndat.valid()) return ndat;
    ndat = Date(31,12,(d.get_year()-1)); return ndat;
};

Date Date::operator ++(int) // postfix operator
{
    Date d = *this;
    *this = next_date(d);
    return d;
};

Date Date::operator ++() // prefix operator
{
    *this = next_date(*this);
    return *this;
};

Date Date::operator --(int) // postx operator, return current value
{
    Date d = *this;
    *this = previous_date(*this);
    return d;
};

Date Date::operator --() // prex operator, return new value
{
    *this = previous_date(*this);
    return *this;
};

inline long long_date(const Date& d)
{
    if (d.valid()) {return d.get_year() * 10000 + d.get_month() * 100 + d.get_DOM();};
    return -1;
};

std::ostream & operator << (std::ostream& os, const Date& d)
{
    if (d.valid()) {os << " " << long_date(d) << " " ;}
    else {os << " invalid date ";};
    return os;
};

bool Date::isLeapYear() const
{   //Leap year: 1
    return !((year_)%400) || (!((year_)%4) && ((year_)%100));
}

int Date::get_DOY() const
{
    //Return day of year: 1-365/366
    int yday;
    if (isLeapYear()) {
        yday = month_start_day_leapyear[month_-1] + day_ - 1;
    }
    else yday = month_start_day_nonleapyear[month_-1] + day_ - 1;

    return yday;
}

//______________________________________________________________________________
} // namespace BAO
