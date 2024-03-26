// Created by Will Balding on 11/9/2022.

#ifndef PIZZAPROJECT_DRIVER_HPP
#define PIZZAPROJECT_DRIVER_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include "Time.hpp"
#include "Order.hpp"

using namespace std;

//---------------------------------------------------------------------------------------//
//                                                                                       //
//                                Driver Class Definition                                //
//                                                                                       //
//---------------------------------------------------------------------------------------//

class Driver {
private:
    // Driver Data Members:

    // name
    // Type: String
    // Function: A string that contains the name of the driver.
    string name;

    // tip
    // Type: Double
    // Function: A double that stores the amount of tips a driver receives.
    double tips;

    // logInTime
    // Type: Time
    // Function: A variable that stores the time a driver logged in, organized in a xx:xx format.
    Time logInTime;

    // logInTime
    // Type: Time
    // Function: A variable that stores the time a driver logged out, organized in a xx:xx format.
    Time logOutTime;

    // logInTime
    // Type: Time
    // Function: A variable that stores the time a driver begins a delivery, organized in a xx:xx format.
    Time departureTime;

    // logInTime
    // Type: Time
    // Function: A variable that stores the time a driver delivers an order, organized in a xx:xx format.
    Time deliveryTime;

    // logInTime
    // Type: Time
    // Function: A variable that stores the time a driver returns to the restaurant, organized in a xx:xx format.
    Time returnTime;

    // totalDeliveryTime
    // Type: Integer
    // Function: A variable that stores the total delivery time of a driver.
    int totalDeliveryTime;

    // totalDriveTime
    // Type: Integer
    // Function: A variable that stores the total driving time of a driver.
    int totalDriveTime;

    // status
    // Type: Boolean
    // Function: A boolean that stores whether the driver is logged in (true) or not (false).
    bool status;

    // location
    // Type: Integer
    // Function: An integer that tracks where the driver is and whether they are logged in.
    // At restaurant = 0, delivering = 1, driving back = 2.
    int location;

    // deliveries
    // Type: Integer
    // Function: An integer that tracks the total amount of deliveries.
    int deliveries;

public:
    // Constructor
    // Pre: None
    // Post: Initializes a new driver with the given name and logs the driver in.
    Driver(const string name);

    // Log-In Status Checkers
    // Pre: The driver is not logged in.
    // Post: Logs the driver in.
    void logIn(const Time signInTime) throw (logic_error);

    // Pre: The driver is logged in and must be at the restaurant.
    // Post: Logs the driver out.
    void logOut(const Time signOutTime) throw (logic_error);

    // Delivery Operations
    // Pre: The driver is logged in and must be at the restaurant.
    // Post: The driver is set to be delivering, and the departure time is recorded.
    void driverDeparture(const Time depTime) throw (logic_error);

    // Pre: The driver is currently logged in, delivering, and the tips are >= 0.
    // Post: The driver is set to be not delivering, updating the driver's stats and tips.
    void driverDelivery(const Time delTime, double tip) throw (logic_error);

    // Pre: The driver is logged in and driving but not delivering.
    // Post: Driver is set to be in the restaurant, updating the driver's stats.
    void driverReturn(const Time rTime) throw (logic_error);

    // Name Getter
    // Pre: None
    // Post: Returns the name of the driver.
    string getName() const;

    // Shift Validation
    // Pre: None
    // Post: Returns true if the driver is logged in, false otherwise.
    bool isOnShift() const;

    // Totals Getters
    // Pre: None
    // Post: Returns the number of completed deliveries.
    int totalDeliveries();

    // Pre: None
    // Post: Returns the amount of time spent delivering, defined as the amount
    // of time between the departure and delivery commands.
    int totalTimeOnDeliveries();

    // Pre: None
    // Post: Returns the amount of time spent driving, defined as the amount
    // of time between the delivery and arrival commands.
    int totalDrivingTime();

    // Pre: None
    // Post: Returns the dollar amount of tips received in $xx.xx format.
    double tipsTotal();

    // Pre: None
    // Post: Returns the name and log-in status of a driver, as well departure time (if delivering) of a driver.
    string driverStatus();
};

//---------------------------------------------------------------------------------------//
//                                                                                       //
//                               Driver Class Implementation                             //
//                                                                                       //
//---------------------------------------------------------------------------------------//

Driver::Driver(const string n) {
    name = n;
    status = true;
    location = 0;
    tips = 0.0;
    deliveries = 0;
}

//---------------------------------------------------------------------------------------//


void Driver::logIn(const Time inTime) throw (logic_error) {
    if (isOnShift()) {
        throw logic_error("Error: Driver is already logged in.");
    }

    status = true;
    logInTime = inTime;
}

//---------------------------------------------------------------------------------------//

void Driver::logOut(const Time outTime) throw (logic_error) {
    if (!isOnShift()) {
        throw logic_error("Error: Driver is not logged in.");
    }

    if (location != 0) {
        throw logic_error("Error: Driver must be at restaurant.");
    }

    status = false;
    logOutTime = outTime;
}

//---------------------------------------------------------------------------------------//

void Driver::driverDeparture(const Time depTime) throw (logic_error) {
    if (!isOnShift()) {
        throw logic_error("Error: Driver is not logged in.");
    }

    if (location != 0) {
        throw logic_error("Error: Driver must be at restaurant.");
    }

    location = 1;
    departureTime = depTime;
}

//---------------------------------------------------------------------------------------//

void Driver::driverDelivery(const Time delTime, double deliveryTip) throw (logic_error) {
    if (!isOnShift()) {
        throw logic_error("Error: Driver is not logged in.");
    }

    if (location != 1) {
        throw logic_error("Error: Driver must be delivering.");
    }

    if (tips < 0) {
        throw logic_error("Error: You cannot have a negative tip amount.");
    }

    location = 2;
    deliveryTime = delTime;

    tips = tips + deliveryTip;
    deliveries++;

    cout << "Order delivered!" << endl;
    cout << "The tips received on this order was: $" << deliveryTip << endl;
}

//---------------------------------------------------------------------------------------//

void Driver::driverReturn(const Time rTime) throw (logic_error) {
    if (!isOnShift()) {
        throw logic_error("Error: Driver is not logged in.");
    }

    if (location != 2) {
        throw logic_error("Error: Driver must be driving back to the restaurant.");
    }

    location = 0;
    returnTime = rTime;
}

//---------------------------------------------------------------------------------------//

string Driver::getName() const {
    return name;
}

//---------------------------------------------------------------------------------------//

bool Driver::isOnShift() const {
    if (status) {
        return true;
    }

    else {
        return false;
    }
}

//---------------------------------------------------------------------------------------//

int Driver::totalDeliveries() {
    return deliveries;
}

//---------------------------------------------------------------------------------------//

int Driver::totalTimeOnDeliveries() {
    double totalDeliveryTime = Time::elapsedMin(departureTime,deliveryTime);
    return totalDeliveryTime;
}

//---------------------------------------------------------------------------------------//

int Driver::totalDrivingTime() {
    totalDriveTime = Time::elapsedMin(deliveryTime,returnTime);
    return totalDriveTime;
}

//---------------------------------------------------------------------------------------//

double Driver::tipsTotal() {
    return tips;
}

//---------------------------------------------------------------------------------------//

string Driver::driverStatus() {
    string driverStats = "";

    if (location == 1) {
        driverStats = "Driver: " + name + "\n" + "Logged in?: " + to_string(isOnShift()) +
                      "\n" + "Departure Time: " +
                      departureTime.toString();
    }

    else {
        driverStats = "Driver: " + name + "\n" + "Logged in?: " + to_string(isOnShift());
    }

    return driverStats;
}
#endif //PIZZAPROJECT_DRIVER_HPP









