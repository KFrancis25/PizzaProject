//
// Created by kaial on 11/18/2022.
//

#ifndef PIZZAPROJECT_RESTAURANT_HPP
#define PIZZAPROJECT_RESTAURANT_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <deque>
#include "Order.hpp"
#include "Driver.hpp"
#include "Time.hpp"
using namespace std;

//---------------------------------------------------------------------------------------//
//                                                                                       //
//                                Restaurant Class Definition                            //
//                                                                                       //
//---------------------------------------------------------------------------------------//

class Restaurant{
private:
    //Restaurant keeps track of all drivers and orders in the system, including logged-out drivers and completed orders.
    list <Driver> drivers;
    deque <Order> incoming_order;
    deque <Order> outgoing_order;
    list <Order> delivered;
    int order_completed;
    int total_time;

public:
    //class
    Restaurant();
    //status of order and driver location
    void status();
    //order summary
    void summary(Driver &driver);
    //restaurant summary
    void res_summary();
    // receives the name of the driver
    Driver *getDriver(string name) throw (logic_error);
    // adds driver to list
    void addDriver(Driver &driver);
    //adds order to queue
    void addOrder(Order &order);
    // Pre: The cooking queue must not be empty.
    // Post: Places first order in cooking queue into the delivery queue
    // and removes item from cooking queue.
    void serveOrder() throw (logic_error);
    // Pre: The delivery queue must not be empty.
    // Post: Removes the first order in the delivery queue and returns it.
    Order departOrder(Time departTime) throw (logic_error);

//    Restaurant& operator=(const Restaurant &other);
//    Restaurant& operator=(Restaurant &&other);
//    void refreshList;
//    void removefromList;
};

//---------------------------------------------------------------------------------------//
//                                                                                       //
//                               Restaurant Class Implementation                         //
//                                                                                       //
//---------------------------------------------------------------------------------------//
Restaurant::Restaurant() : order_completed(0), total_time(0)
{

}

void Restaurant::status()
{
    cout << "Waiting for the orders to be ready... " << endl;
    for (auto &incoming_orders : incoming_order)
    {
        cout << "\t" << incoming_orders.Status() << endl;
    }

    //cout << "Orders are waiting to be depart: " << endl;
    for (auto &outgoing_orders : outgoing_order)
    {
        cout << "\t" << outgoing_orders.Status() << endl;
    }

    cout << "Availability for drivers:" << endl;
    cout<< "(Not available = 0, Available = 1)" << endl << endl;
    for (Driver Driver : drivers)
    {
        cout << Driver.driverStatus() << endl;
    }
    cout << endl;
}

void Restaurant::res_summary()
{
    cout << "Total order restaurant received: " << order_completed << endl;
    cout << "The average time for the order: " << (float)total_time / order_completed << endl;
}

void Restaurant::summary(Driver &driver) {
    cout << "Driver: " << driver.getName() << endl;
    cout << "The number of deliveries completed: " << driver.totalDeliveries() << endl;
    if (driver.totalDeliveries() != 0)
        cout << "The average time for the delivery: "
             << ((driver.totalTimeOnDeliveries()) / double((driver.totalDeliveries()))) << endl;
    cout << "The total driving time: " << driver.totalTimeOnDeliveries() << endl;
    if (driver.getName() == driver.getName())
        cout << "The total tips: $" << driver.tipsTotal() << endl;
}

Driver * Restaurant::getDriver(string name) throw(logic_error)
{
    for (list<Driver>::iterator it = drivers.begin(); it != drivers.end(); it++)
    {
        if (it -> getName() == name)
        {
            return &*it;
        }
    }
    throw logic_error("There are no drivers that are available.");
}


void Restaurant::addDriver(Driver &driver)
{
    drivers.push_back(driver);
}

void Restaurant::addOrder(Order &order)
{
    incoming_order.push_back(order);
}

void Restaurant::serveOrder() throw(logic_error)
{
    if (incoming_order.empty())
    {
        throw logic_error("No incoming order is getting ready.");
    }

    Order serve = incoming_order.front();
    incoming_order.pop_front();
    outgoing_order.push_back(serve);
}

Order Restaurant::departOrder(Time departTime) throw(logic_error)
{
    if (outgoing_order.empty())
    {
        throw logic_error ("No outgoing order is getting ready.");
    }

    Order depart = outgoing_order.front();

    //calulcate elapsed time from depart.placed to depart.depart
    total_time = total_time + Time::elapsedMin(departTime, depart.getOrderTime());
    outgoing_order.pop_front();
    order_completed = order_completed + 1;

    return depart;
}


#endif //PIZZAPROJECT_RESTAURANT_HPP