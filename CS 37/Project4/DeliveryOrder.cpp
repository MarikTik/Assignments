#include "DeliveryOrder.h"
#include <iostream>

// initializing static members of DeliveryOrder

size_t DeliveryOrder::orderCount = 0;
const float DeliveryOrder::taxRate = 0.09f;
const float DeliveryOrder::deliveryRate = 2.0f;

DeliveryOrder::DeliveryOrder(std::string name, std::string date, std::string phone, float miles)
     : orderBalance(0), name(name), date(date), phone(phone), miles(miles)
{
     orderCount++; // keeping track of order creation via static member increment
}

DeliveryOrder::~DeliveryOrder()
{
     std::cout << "DeliveryOrder destroyed.\n";
}

void DeliveryOrder::receipt() const
{
     std::cout << "Order Detail:" << "\n"
      << "\tName: " << name << "\n"
      << "\tDate: " << date << "\n"
      << "\tPhone: " << phone << "\n"
      << "\tOrder Balance: $" << orderBalance << std::endl;
}

float DeliveryOrder::getTotalBalance() const
{
     return orderBalance * (1 + taxRate) + miles * deliveryRate; // formula taken from the project manual
}

size_t DeliveryOrder::getOrderCount()
{
     return orderCount;
}
