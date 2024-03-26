//
// Created by Keeyeon Choi on 2022/11/17.
//

#ifndef PIZZAPROJECT_TIME_HPP
#define PIZZAPROJECT_TIME_HPP


#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Time
{
private:
    // Type: integer
    // Function: An integer that contains the hour part of the time (0 <= hour <= 23)
    int hour;

    // Type: integer
    // Function: An integer that contains the minute part of the time (0 <= minute <= 59)
    int min;

    // Type: integer
    // Function: An integer that contains the hour and minute of current time
    int curr_time;

public:
    //Pre: None
    //Post: Creates a time with default values for data members
    Time();

    //Pre: 0 <= hour <= 23 and 0 <= min <= 59
    //Post: Creates a time with the given hour and minute.
    Time(int hour, int min) throw (logic_error);

    //Pre: None
    //Post: Returns the difference in minutes between t1 and t2. Assumes t2 is between 00:00 and 23:59 hours after t1
    static int elapsedMin(Time t1, Time t2);

    //Pre: None
    //Post: Returns a string containing the hour and minute (e.g., “13:01”).
    string toString();
};

//---------------------------------------------------------------------------------------//
//                                                                                       //
//                               Time Class Implementation                               //
//                                                                                       //
//---------------------------------------------------------------------------------------//

//Default constructor
//Pre: None
//Post: Creates a time with default values for data members
Time::Time()
{
    hour = 0;
    min = 0;
    curr_time = (hour * 60) + min;
}

//Parameterized Constructor
//Pre: 0 <= hour <= 23 and 0 <= min <= 59
//Post: Creates a time with the given hour and minute.
Time::Time(int hour, int min) throw (logic_error)
{
    if(hour < 0 || hour > 24)
    {
        throw logic_error("Error: Hour should be between 0 and 23");
    }
    if(min < 0 || min > 60)
    {
        throw logic_error("Error: Minute should be between 0 and 59");
    }
    this -> hour = hour;
    this -> min = min;
    curr_time = (hour * 60) + min;
}

//Pre: None
//Post: Returns the difference in minutes between t1 and t2. Assumes t2 is between 00:00 and 23:59 hours after t1
int Time::elapsedMin(Time t1, Time t2)
{
    int min_diff;
    min_diff = (t2.hour * 60 + t2.min) - (t1.hour * 60 + t1.min);
    if (min_diff < 0)
    {
        min_diff = min_diff * -1;
    }
    return min_diff;
}

//Pre: None
//Post: Returns a string containing the hour and minute (e.g., “13:01”).
string Time::toString()
{
    string t_time;
    string space = "";

    if (min < 10)
    {
        space = "0";
    }

    string time_hour = to_string(hour);
    string min_hour = space + to_string(min);

    t_time = time_hour + ":" + min_hour;

    return t_time;
}

#endif //PIZZAPROJECT_TIME_HPP
