#ifndef PERSON_HPP_
#define PERSON_HPP_
#include <string>
#include <ostream>
#include <istream>

struct person{
     std::string name;
     float weight;
     
     bool operator < (const person &other){
          return name < other.name;
     }
     friend std::ostream &operator << (std::ostream &os, const person &p){
          os << "{" << p.name << ", " << p.weight << "}"; 
          return os;
     }
     friend std::istream &operator >> (std::istream &is, person &p){
          is >> p.name >> p.weight;
          return is;
     }
};

#endif