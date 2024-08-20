#include <iostream>
#include "Minion.h"
#include <fstream>

using namespace std;

int main(){

 
     ifstream input_stream("minion.txt");

     const Minion minion1 = Minion::input_minion_const(input_stream);
     
     Minion minion2{};
     Minion minion3{};

     input_stream >> minion2 >> minion3;


     if (minion1 > minion2) {
          cout << minion1.getName() << " is taller than " << minion2.getName();
     } 
     if (minion2 < minion3) {
          cout << minion3.getName() << " is taller than " << minion2.getName();
     }
     cout << endl << endl;
     cout << minion2;
     cout << minion2.getName() << " getting bananas.\n";
     
     
     cout << "The minion now has " << (++(++minion2)).getBananas() << " banana(s).\n" << endl;
     cout << minion3;
      cout << minion3.getName() << " getting bananas.\n";
     cout << "Before getting bananas, the minion had " << minion3++.getBananas() << " banana(s).\n";
     cout << "After getting bananas, the minion has " << minion3.getBananas() << " banana(s).\n" << endl;

     Minion::printMinionCount();

}