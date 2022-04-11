#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date {
	int year;
	int month;
	int day;
public:
	Date();

	Date(int, int, int);
	Date(string date)
	{
		date += '/';
		string d;
		int arr[3] = { 0 };
		for (int i = 0, k = 0; i < date.length(); i++)
		{
			if (date[i] != '/')
				d += date[i];
			else
			{
				arr[k] = stoi(d);
				k++;
				d = "";
			}
		}
		day = arr[0];
		month = arr[1];
		year = arr[2];
	}
	int getDay()
	{
		return day;
	}
	void setDay(int d)
	{
		day = d;
	}

	int getMonth()const;
	int getYear()const;
	bool isLeapYear()const;
	string toString();
	string getDate();
	void setDate(string date)
	{
		date += '/';
		string d;
		int arr[3] = { 0 };
		for (int i = 0, k = 0; i < date.length(); i++)
		{
			if (date[i] != '/')
				d += date[i];
			else
			{
				arr[k] = stoi(d);
				k++;
				d = "";
			}
		}
		day = arr[0];
		month = arr[1];
		year = arr[2];
	}
	bool operator<(const Date& d)
	{
		if (year < d.year)
			return true;
		else if (year == d.year)
		{
			if (month < d.month)
				return true;
			else if (month == d.month)
			{
				if (day < d.day)
					return true;
			}
		}
		return false;
	}
	bool operator>(const Date& d)
	{
		if (year > d.year)
			return true;
		else if (year == d.year)
		{
			if (month > d.month)
				return true;
			else if (month == d.month)
			{
				if (day > d.day)
					return true;
			}
		}
		return false;
	}
	bool operator==(const Date& d)
	{
		return ((!((*this) > d)) && (!((*this) < d)));
	}
	Date& operator=(const Date& d)
	{
		year = d.year;
		month = d.month;
		day = d.day;
		return *this;
	}

};
Date::Date(int year, int month, int day)
{
	if (year >= 0)
	{
		this->year = year;
	}
	if (month >= 0 && month <= 12)
	{
		this->month = month;
	}
	if (day >= 0 && day <= 31)
	{
		this->day = day;
	}
}
Date::Date()
{
	this->year = 2000;
	this->month = 1;
	this->day = 1;
}
int Date::getMonth()const
{
	return month;
}
int Date::getYear()const
{
	return year;
}
bool Date::isLeapYear()const
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return true;
			}
		}
	}
	return false;
}
string Date::toString()
{
	string s;
	s += to_string(day);
	s += "/";
	s += to_string(month);
	s += "/";
	s += to_string(year);
	return s;

}
string Date::getDate()
{
	return (toString());
}


class Time {
	int hours;
	int minutes;
public:
	Time();
	Time(int, int);
	Time(string time)
	{
		time += ':';
		string d;
		int arr[2] = { 0 };
		for (int i = 0, k = 0; i < time.length(); i++)
		{
			if (time[i] != ':')
				d += time[i];
			else
			{
				arr[k] = stoi(d);
				k++;
				d = "";
			}
		}
		hours = arr[0];
		minutes = arr[1];
	}
	void setTime(int h, int m);
	string getTime();
	int& getHours()
	{
		return hours;
	}
	void setTime(string time)
	{
		time += ':';
		string d;
		int arr[2] = { 0 };
		for (int i = 0, k = 0; i < time.length(); i++)
		{
			if (time[i] != ':')
				d += time[i];
			else
			{
				arr[k] = stoi(d);
				k++;
				d = "";
			}
		}
		hours = arr[0];
		minutes = arr[1];
	}
	bool operator<(const Time& t)
	{
		if (hours < t.hours)
			return true;
		else if (hours == t.hours)
		{
			if (minutes < t.minutes)
				return true;
		}
		return false;
	}
	bool operator>(const Time& t)
	{
		if (hours > t.hours)
			return true;
		else if (hours == t.hours)
		{
			if (minutes > t.minutes)
				return true;
		}
		return false;
	}
	bool operator==(const Time& t)
	{
		return ((!((*this) > t)) && (!((*this) < t)));
	}
	Time& operator=(const Time& t)
	{
		hours = t.hours;
		minutes = t.minutes;
		return *this;
	}

	Time& operator-(const Time& t)
	{
		hours = hours - t.hours;
		minutes = minutes - t.minutes;
		return *this;
	}


};
Time::Time()
{
	hours = 0;
	minutes = 0;
}
Time::Time(int h, int m)
{
	if (h >= 0)
		hours = h;
	if (m >= 0)
		minutes = m;
}
void Time::setTime(int h, int m)
{
	if (h >= 0)
		hours = h;
	if (m >= 0)
		minutes = m;
}
string Time::getTime()
{
	string s;
	s += to_string(hours);
	s += ":";
	s += to_string(minutes);
	return s;
}