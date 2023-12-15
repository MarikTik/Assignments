#ifndef BOBA_ORDER_H_
#define BOBA_ORDER_H_
#include "DeliveryOrder.h"
#include <cstddef>
#include <string>

class BobaOrder : public DeliveryOrder{
     public:
          BobaOrder(std::string name,
                    std::string date,
                    std::string phone,
                    float miles,
                    std::string shopName
                    );
          ~BobaOrder() override;
          void receipt() const override;
          float VIPdiscount() override;
          void addDrink(std::string name, bool addBoba=true, uint32_t drinksCount=1);
     private:
          std::string shopName;
          size_t drinksCount=0;
};

#endif