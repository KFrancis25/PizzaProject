//
// Created by miles on 11/10/2022
//

#include <string>
#include "Time.hpp"

using namespace std;
#ifndef UNTITLED1_ORDERS_HPP
#define UNTITLED1_ORDERS_HPP

class Order
{
public:

    Order();

    string Status();

    void Depart(Time timeDeparted) ;
    ////DEPARTS ORDER FROM THE RESTAURANT -
    ////*********************************


    void placeOrder(string address, Time timeOrdered, string order);
    ////ORDERS A NEW ORDER FROM THE RESTUARANT
    ////*********************************

    void Deliver(Time timeDelivered);
    ////DELIVERS ORDER TO THE ADDRESS -
    ////*********************************

    void Display();
    ////ORDERS A NEW ORDER FROM THE RESTUARANT
    ////*********************************

    Time getOrderTime();

private:
    string orderAddress;
    string orderInfo;
    string driver;
    Time orderTime;
    Time departTime;
    bool delivered;
    bool departed;
    bool ordered;
    friend class Time;



};



//Pre: None
//Post: Constructor
Order::Order()
        : orderAddress(), orderInfo(), delivered(false) , departed(false), ordered(false)
{

}

//Pre: ordered must be true
//Post: departs restaurant and takes input to determine driver -
//provides a summary of where the order is headed and who is carrying it

void Order::Depart(Time timeDeparted) {
    if(ordered) {
        departed = true;
        departTime = timeDeparted;
        cout << "enter driver: " << endl;
        cin >> driver;


        cout << "-----------------------------------------" << endl;
        cout << driver << " has left base with " << orderInfo << " heading towards: " << orderAddress << endl
             << "at: " << timeDeparted.toString() << endl;
        cout << "-----------------------------------------" << endl;
    }
    else
    {
        throw "No order has been placed to depart!";
    }
}
//// Departs the restaurant and changes private data departed to true,
//// asks the user for input regarding who the driver is

//Pre:none
//Post: Displays All essential order information
void Order::Display() {

    if(delivered){
        cout << "-----------------------------------------" << endl;
        cout << "ORDER STATUS: Delivered" << endl;
        cout << "-----------------------------------------" << endl;
    }
    else {
        cout << "-----------------------------------------" << endl;
        cout << "ORDER INFO: " << endl;
        cout << "Address: " << orderAddress << endl;
        cout << "Order: " << orderInfo << endl;
        cout << "Driver: " << driver << endl;
        cout << "-----------------------------------------" << endl;

        if (departed && !delivered) {
            cout << "-----------------------------------------" << endl;
            cout << "ORDER STATUS: En route" << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
    /// Displays the order - if the order has been delivered then function outputs a message telling you so,
    /// if not then displays the current status of the order by including Address, Driver, and Order information.
    /// lastly if the order has departed the restaurant
    /// then the function will output a message describing the status of the order


}

//Pre: none
//Post: "places" order and fills in private data of orderAdress, orderTime and orderInfo
void Order::placeOrder(string address, Time timeOrdered, string order) {

    orderInfo = order;
    orderAddress = address;
    orderTime = timeOrdered;
    ordered = true;

    cout << "-----------------------------------------" << endl;
    cout << "Order Menu: " << orderInfo << endl << "Order Time: " << orderTime.toString() << endl << "Delivery address: "
         << orderAddress << endl;
    cout << "-----------------------------------------" << endl;

    //// Places order and sets private data 'ordered' to true - sets private data: orderInfo and orderAddress
    /// takes string containing address, Time ordered and, string containing the order as parameters





}
//Pre: departed must be true
//Post: delivers order - gives a rundown of the delivery - gives a time analysis
void Order::Deliver( Time timeDelivered){

    delivered = true;

    Time timeElapsed;

    int delivery_time = timeElapsed.elapsedMin(departTime,timeDelivered);



    if(!departed){
        throw "Order cannot be Delivered as it has not departed from PizzaPalace.";
    }
    cout << "-----------------------------------------" << endl;
    cout << "Order cointaining: " << orderInfo << " was delivered to: " << orderAddress << endl << "by: " << driver << ", at: "
         << timeDelivered.toString() << endl;

    cout << "delivery took: " << delivery_time << " minutes" << endl;

    cout << "-----------------------------------------" << endl;

    //// Delivers order - sets private data delivered to true -
    /// provides summary of what was delivered where and by who
    /// also mentions how long the order took

}

string Order::Status() {
    string status;


    if(delivered){
        status = "delivered";
    }
    if(departed && !delivered){
        status = "departed";
    }
    if(ordered && !departed && !delivered){
        status = "cooking";
    }
    return status;

}

Time Order::getOrderTime(){
    return orderTime;

}

#endif //UNTITLED1_ORDERS_HPP


