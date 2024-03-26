#include <iostream>
#include "Restaurant.hpp"

using namespace std;

int main() {
    Restaurant pizza;

    Driver john("John");
    Driver mike("Mike");

    pizza.addDriver(john);
    pizza.addDriver(mike);

    Time time1(5,10);
    Time time2(5,25);
    Time time3(5,30);
    Time time4(5,55);
    Time time5(6,10);
    Time time6(6,15);
    Time time7(6,25);
    Time time8(6, 40);
    Time time9(6,55);

    Order order1;
    order1.placeOrder("581 South Hampton Ave", time1, "Pepperoni Pizza");
    pizza.addOrder(order1);
    pizza.serveOrder();
    pizza.departOrder(time2);
    john.driverDeparture(time2);
    john.driverDelivery(time3,4.5);
    cout << "-----------------------------------------" << endl;

    pizza.status();

    Order order2;
    order2.placeOrder("1 Wooster Ave", time3, "Hawaiian Pizza");
    pizza.addOrder(order2);
    pizza.serveOrder();
    pizza.departOrder(time4);
    mike.driverDeparture(time4);
    mike.driverDelivery(time5,6.3);
    mike.driverReturn(time6);

    Order order3;
    order3.placeOrder("7563 Zero Cir", time4, "Cheese Pizza");
    pizza.addOrder(order3);
    pizza.serveOrder();
    pizza.departOrder(time7);
    mike.driverDeparture(time7);
    mike.driverDelivery(time8,3.5);
    mike.driverReturn(time9);
    cout << "-----------------------------------------" << endl;

    cout << "Order Summary" << endl << endl;
    pizza.summary(john);
    pizza.summary(mike);
    cout << "-----------------------------------------" << endl;

    cout << "Restaurant Summary" << endl << endl;
    pizza.res_summary();
}
