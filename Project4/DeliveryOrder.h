#ifndef DELIVERY_ORDER_H_
#define DELIVERY_ORDER_H_
#include <string>
#include <cstddef>

// eliveryOrder

// Class DeliveryOrder will have the following member attributes:

//     name(string - customer's name)
//     date(string - date of the order)
//     phone(string - phone number of the customer)
//     miles (float - number of miles for the delivery)
//     orderBalance(float - balance of the order which doesn't include delivery fee and tax)

// The class DeliveryOrder also has three static members including orderCount, 
//which is used to calculate how many orders are placed, and two constant variables taxRate and deliveryRate.

// All of these attributes are private to class DeliveryOrder, except the orderBalance which should only be directly accessible by the inherited classes (protected).

// Class DeliveryOrder will have a constructor, a destructor, and four functions:

//     The constructor will initialize customer's name, date of the order (month/day/year), phone number, 
//     and number of miles of the delivery from the parameters. It will initialize the orderBalance to be 0, 
//     then increase the orderCount so that we can count how many orders are created

//     The destructor will output a string "DeliveryOrder destroyed.\n".
//     The four functions include

//         constant receipt() function that will print out the order receipt
//         constant getTotalBalance() function that will return the total balance(with delivery fee and tax)
//         static getOrderCount() function that will return the orderCount
//         pure virtual function VIPdiscount() that will calculate and return the discount for the order


class DeliveryOrder{
     public:
          DeliveryOrder(std::string name,
                        std::string date,
                        std::string phone,
                        float miles
                        );
          virtual ~DeliveryOrder();
         
          float getTotalBalance() const;
          static size_t getOrderCount();
          virtual void receipt() const;
          virtual float VIPdiscount() = 0;
          
     protected:
          float orderBalance = 0.0f;

     private:
          std::string name, date, phone;

          float miles;

          static const float taxRate, deliveryRate;

          static size_t orderCount; 
};

#endif