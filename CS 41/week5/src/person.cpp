#include "person.hpp"

std::istream &operator>>(std::istream &is, person &person)
{
     is >> person.name >> person.weight;
     return is;
}

std::ostream &operator<<(std::ostream &os, const person &person)
{
     os << person.name << " - " << person.weight;
     return os;
}
