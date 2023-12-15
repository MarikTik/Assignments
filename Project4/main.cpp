#include <iostream>
#include "InvalidInputException.h"
#include "DeliveryOrder.h"
#include "BobaOrder.h"
#include "FoodOrder.h"
#include "Account.h"
#include <iomanip>

float applyDiscount(DeliveryOrder* order, const Account& account){
    auto status = account.getStatus();
    auto balance = order->getTotalBalance();

    if (status == "Owner")
        return 0.1f * balance;
    if (status == "VIP")
        return order->VIPdiscount() * balance;

    return balance;  
}

int main(){
    const Account StuartAccount{"Stuart", "Owner"};
    Account KevinAccount{"Kevin", "VIP"};
    Account BobAccount{"Bob"};
 
    std::cout << std::fixed << std::setprecision(2);

    
    std::cout << "Kevin is placing order.\n";
    BobaOrder KevinBobaOrder{"Kevin", "11/20/2023", "123-456-0000", 10.4f, "M Tea"};
    try{
        KevinBobaOrder.addDrink("Green Tea Latte");
        KevinBobaOrder.addDrink("Brown Sugar Pearl Milk", false);
        KevinBobaOrder.addDrink("Brown Sugar Boba Milk", false, 2);
        KevinBobaOrder.addDrink("Iron Goddess");
    }
    catch(InvalidInput& e){
        e.reason();
        std::cout << "Not serving requested drinks. Drink order ignored.\n\n";
    }

    KevinBobaOrder.receipt();
    std::cout << "Balance: $" << KevinBobaOrder.getTotalBalance() << "\n"
              << "Discounted Balance: $" << applyDiscount(&KevinBobaOrder, KevinAccount) << "\n\n";



    std::cout << "Stuart is placing order.\n";
    FoodOrder StuartFoodOrder{"Stuart", "11/20/2023", "123-456-1111", 25.5f, "Tavern Green"};
    try{
        StuartFoodOrder.addFood("Thick Cauliflower Steaks", 1, true);
        StuartFoodOrder.addFood("Organic Scottish Salmon", 0);
        StuartFoodOrder.addFood("Rack of Lamb", 0, true);
    }
    catch(InvalidInput& e){
        e.reason();
        std::cout << "Not serving requested food. Food order ignored.\n\n";
    }

    StuartFoodOrder.receipt();
    std::cout << "Balance: $" << StuartFoodOrder.getTotalBalance() << "\n"
              << "Discounted Balance: $" << applyDiscount(&StuartFoodOrder, StuartAccount) << "\n\n";
     
    
    
    DeliveryOrder* BobOrder = &StuartFoodOrder;
    std::cout << "Bob decided to log in to his account and see whether he can afford ordering the same order as Stuart.\n";
    BobOrder->receipt();
    BobOrder->getTotalBalance();
    std::cout << "Balance: $" << BobOrder->getTotalBalance() << "\n"
              << "Discounted Balance: $" << applyDiscount(BobOrder, BobAccount) << "\n\n";

    std::cout << "Bob upset, cancelling order :(\n\n"
              << "Total order placed: " << BobOrder->getOrderCount() << ".\n\n";
    
   
}

