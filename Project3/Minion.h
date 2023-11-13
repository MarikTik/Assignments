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

     bool operator > (const Minion& minion) const;
     bool operator < (const Minion& minion) const;
     Minion operator ++ (int); //post decrement
     Minion& operator ++ ();  //pre decrement

     friend ostream& operator << (ostream& os, Minion& minion);
     friend istream& operator >> (istream& is, Minion& minion);
     static const Minion input_minion_const (istream& is); // util function for the const Minion minion1 requirement
     // static void printMinionCount();

private:
     string name="";
     float height=0;
     int eyes=0;
     int bananasOwned=0;

     static int minionCount;

};


#endif