#include "BobaOrder.h"
#include <iostream>
#include <unordered_map>
#include "InvalidInputException.h"

BobaOrder::BobaOrder(std::string name, std::string date, std::string phone, float miles, std::string shopName)
     : DeliveryOrder::DeliveryOrder(name, date, phone, miles), shopName(shopName)
{
}

BobaOrder::~BobaOrder()
{
     std::cout << "BobaOrder destroyed.\n";
}

void BobaOrder::receipt() const
{    
     DeliveryOrder::receipt();
     std::cout << "\tDrinks Count: " << drinksCount << std::endl;
}

float BobaOrder::VIPdiscount()
{
     if (drinksCount > 10)
          return 0.8f;
     if (drinksCount > 5)
          return 0.9f;
     if (drinksCount > 2)
          return 0.95f;

     return 1;
}
 
void BobaOrder::addDrink(std::string name, bool addBoba, uint32_t drinksCount)
{
     static const std::unordered_map<std::string, float> drinkCost // dictionary that stores the names of drinks with their price in pairs
     {
          {"Green Tea Latte", 5.8f},
          {"Brown Sugar Boba Milk", 7.8f},
          {"Brown Sugar Pearl Milk", 9.8f}
     };
     auto costIterator = drinkCost.find(name);

     if (costIterator == drinkCost.end()) // if the name wasn't found
          throw InvalidInput(name);

     //little function that computes the cost of the drink
     auto computeCost = [&](){
          float itemCost = costIterator->second;  //'second' member of costIterator points to the value corresponding to the name in the dictionary
          float drinksCountF = static_cast<float>(drinksCount); // keeping conversion explicit (undecided if this is the right way yet)
          
          return (itemCost + addBoba) * drinksCountF; // formula according to manual
     };
     this->orderBalance += computeCost(); 
     this->drinksCount += drinksCount; // incrementing by the amount of drinks ordered

}
