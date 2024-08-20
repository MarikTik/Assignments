#ifndef PERSON_HPP_
#define PERSON_HPP_
#include <istream>

struct person{
     friend std::istream &operator >> (std::istream &in, person person);
     
     std::string name;
     float weight;
};

#endif