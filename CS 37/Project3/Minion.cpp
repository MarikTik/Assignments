#include "Minion.h"
#include <iostream>
int Minion::minionCount;


Minion::Minion(){
     minionCount++;
}

int Minion::getBananas() const
{
     return bananasOwned;

}

string Minion::getName() const
{
     return name;
}

void Minion::printMinionCount(){
     cout << minionCount << " minions created." << endl;
}
 

bool Minion::operator>(const Minion &minion) const
{
     return height > minion.height;
}

bool Minion::operator<(const Minion &minion) const
{
     return height < minion.height;
}

Minion Minion::operator++(int)
{
     Minion previous(*this);
     bananasOwned++;
     return previous;
}

Minion &Minion::operator++()
{
     bananasOwned++;
     return *this;
}

const Minion Minion::input_minion_const(istream &is)
{
     Minion minion;
     is >> minion;
     return minion;
}

ostream &operator<<(ostream &os, const Minion &minion)
{
     os << "The minion " << minion.name << " is " << minion.height << 
     " tall, has " << minion.eyes << " eye(s), and owns " <<
     minion.bananasOwned << " banana(s).\n"; 
 
     return os;
}

istream &operator>>(istream &is, Minion &minion)
{
     is >> minion.name >> minion.height >> minion.eyes >> minion.bananasOwned;

     return is;
}


