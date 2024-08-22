#ifndef PERSON_HPP_
#define PERSON_HPP_
#include <istream>
#include <ostream>

struct person{
     friend std::istream &operator >> (std::istream &is, person &person);
     friend std::ostream &operator << (std::ostream &os, const person &person);

     std::string name;
     float weight;
};

#endif