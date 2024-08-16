#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

using namespace std;

class DateTime {
private:
    int day;
    int month;
    int year;
    int hours;
    int minutes;
    int seconds;

    bool isLeapYear(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    int daysInMonth(int month, int year) const {
        switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            throw invalid_argument("Invalid month");
        }
    }

    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        if (hours >= 24) {
            day += hours / 24;
            hours %= 24;
        }

        while (day > daysInMonth(month, year)) {
            day -= daysInMonth(month, year);
            if (++month > 12) {
                month = 1;
                year++;
            }
        }
    }

public:
    DateTime(int d = 1, int m = 1, int y = 1970, int h = 0, int min = 0, int sec = 0)
        : day(d), month(m), year(y), hours(h), minutes(min), seconds(sec) {
        normalize();
    }

    DateTime(const DateTime& dt)
        : day(dt.day), month(dt.month), year(dt.year), hours(dt.hours), minutes(dt.minutes), seconds(dt.seconds) {}

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    int getHours() const { return hours; }
    int getMinutes() const { return minutes; }
    int getSeconds() const { return seconds; }

    void setDay(int d) { day = d; normalize(); }
    void setMonth(int m) { month = m; normalize(); }
    void setYear(int y) { year = y; normalize(); }
    void setHours(int h) { hours = h; normalize(); }
    void setMinutes(int min) { minutes = min; normalize(); }
    void setSeconds(int sec) { seconds = sec; normalize(); }

    DateTime operator+(const DateTime& dt) const {
        return DateTime(day + dt.day, month, year, hours + dt.hours, minutes + dt.minutes, seconds + dt.seconds);
    }

    DateTime operator-(const DateTime& dt) const {
        return DateTime(day - dt.day, month, year, hours - dt.hours, minutes - dt.minutes, seconds - dt.seconds);
    }

    DateTime& operator+=(int days) {
        day += days;
        normalize();
        return *this;
    }

    DateTime& operator-=(int days) {
        day -= days;
        normalize();
        return *this;
    }

    int operator[](const string& field) const {
        if (field == "day") return day;
        if (field == "month") return month;
        if (field == "year") return year;
        if (field == "hours") return hours;
        if (field == "minutes") return minutes;
        if (field == "seconds") return seconds;
        throw invalid_argument("Invalid field");
    }

    bool operator<(const DateTime& dt) const {
        if (year != dt.year) return year < dt.year;
        if (month != dt.month) return month < dt.month;
        if (day != dt.day) return day < dt.day;
        if (hours != dt.hours) return hours < dt.hours;
        if (minutes != dt.minutes) return minutes < dt.minutes;
        return seconds < dt.seconds;
    }

    bool operator>(const DateTime& dt) const {
        return dt < *this;
    }

    bool operator<=(const DateTime& dt) const {
        return !(dt < *this);
    }

    bool operator>=(const DateTime& dt) const {
        return !(*this < dt);
    }

    bool operator==(const DateTime& dt) const {
        return year == dt.year && month == dt.month && day == dt.day && hours == dt.hours && minutes == dt.minutes && seconds == dt.seconds;
    }

    bool operator!=(const DateTime& dt) const {
        return !(*this == dt);
    }

    friend ostream& operator<<(ostream& os, const DateTime& dt);
    friend istream& operator>>(istream& is, DateTime& dt);
};

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.year << "-" << dt.month << "-" << dt.day << " " << dt.hours << ":" << dt.minutes << ":" << dt.seconds;
    return os;
}

istream& operator>>(istream& is, DateTime& dt) {
    cout << "Enter year: ";
    is >> dt.year;
    cout << "Enter month: ";
    is >> dt.month;
    cout << "Enter day: ";
    is >> dt.day;
    cout << "Enter hours: ";
    is >> dt.hours;
    cout << "Enter minutes: ";
    is >> dt.minutes;
    cout << "Enter seconds: ";
    is >> dt.seconds;
    dt.normalize();
    return is;
}

int main() {
    DateTime dt1(1, 1, 2024, 12, 30, 45);
    DateTime dt2(15, 3, 2024, 14, 45, 30);

    cout << "DateTime 1: " << dt1 << endl;
    cout << "DateTime 2: " << dt2 << endl;

    DateTime dt3 = dt1 + dt2;
    cout << "DateTime 3 (dt1 + dt2): " << dt3 << endl;

    DateTime dt4 = dt2 - dt1;
    cout << "DateTime 4 (dt2 - dt1): " << dt4 << endl;

    dt1 += 10;
    cout << "DateTime 1 after += 10 days: " << dt1 << endl;

    dt2 -= 5;
    cout << "DateTime 2 after -= 5 days: " << dt2 << endl;

    cout << "dt1['year']: " << dt1["year"] << endl;

    cout << "Logical operations:" << endl;
    cout << "dt1 < dt2: " << (dt1 < dt2) << endl;
    cout << "dt1 > dt2: " << (dt1 > dt2) << endl;
    cout << "dt1 <= dt2: " << (dt1 <= dt2) << endl;
    cout << "dt1 >= dt2: " << (dt1 >= dt2) << endl;
    cout << "dt1 == dt2: " << (dt1 == dt2) << endl;
    cout << "dt1 != dt2: " << (dt1 != dt2) << endl;
}