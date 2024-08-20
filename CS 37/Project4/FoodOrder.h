#ifndef FOOD_ORDER_H_
#define FOOD_ORDER_H_
#include "DeliveryOrder.h"

class FoodOrder : public DeliveryOrder{
     public:
          FoodOrder(std::string name,
                    std::string date,
                    std::string phone,
                    float miles,
                    std::string restaurantName
                    );
          void receipt() const override;
          float VIPdiscount() override; 
          ~FoodOrder() override;

          void addFood(std::string name, uint32_t sides, bool addSoup = false);
          
     private:
          std::string restaurantName;
          size_t foodCount=0;
};

#endif