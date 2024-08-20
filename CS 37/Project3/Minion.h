#ifndef MINION_H_
#define MINION_H_
#include <string>
#include <ostream>
#include <istream>
using namespace std;

class Minion{
public:

     Minion();

     int getBananas() const;
     string getName() const;

    
     static void printMinionCount();

     bool operator > (const Minion& minion) const; //overloaded the istream >> function so that the user won't have to repeat the tedious process himself
     bool operator < (const Minion& minion) const; 
     Minion operator ++ (int); //post decrement
     Minion& operator ++ ();  //pre decrement

     friend ostream& operator << (ostream& os, const Minion& minion);
     friend istream& operator >> (istream& is, Minion& minion); 
     static const Minion input_minion_const (istream& is); // util function for the const Minion minion1 requirement
     // static void printMinionCount();

private: 
     string name=""; // Initialize private members in .h file so that the user will be able to see default values without the need to look in the source code
     float height=0;
     int eyes=0;
     int bananasOwned=0;

     static int minionCount;

};


#endif