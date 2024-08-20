#include "FoodOrder.h"
#include <iostream>
#include <unordered_map>
#include "InvalidInputException.h"

FoodOrder::FoodOrder(std::string name, std::string date, std::string phone, float miles, std::string restaurantName)
     : DeliveryOrder::DeliveryOrder(name, date, phone, miles), restaurantName(restaurantName)
{
}

void FoodOrder::receipt() const
{
     DeliveryOrder::receipt();
     std::cout << "\tFood Count: " << foodCount << std::endl;
}


float FoodOrder::VIPdiscount()
{
     if (orderBalance > 50)
          return 0.8f;
     if (orderBalance > 30)
          return 0.9f;
     if (orderBalance > 20)
          return 0.95f;

     return 1;
}
FoodOrder::~FoodOrder()
{
     std::cout << "FoodOrder destroyed.\n";
}
 

void FoodOrder::addFood(std::string name, uint32_t sides, bool addSoup)
{
     static const std::unordered_map<std::string, float> foodCost = { // adding a dictionary to help tracking prices if further foods are added
          {"Thick Cauliflower Steaks", 15},
          {"Rack of Lamb", 38},
          {"Organic Scottish Salmon", 23},
          {"Grilled Lobster Risotto", 46}
     };

     auto costIterator = foodCost.find(name);
     
     if (costIterator == foodCost.end()) // if name wasn't found 
          throw InvalidInput(name);

     // little function that regulates computing the cost
     auto computeCost = [&](){ 
          float itemCost = costIterator->second; // 'second' member gives the value of the dictionary
          float sidesF = static_cast<float>(sides); // making type conversions explicit
          return itemCost + addSoup * 5 + sidesF * 6; // done according to manual formula
     };

     this->orderBalance += computeCost();
     this->foodCount += 1;

}
