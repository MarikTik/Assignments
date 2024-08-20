#include "person.hpp"

std::istream &operator>>(std::istream &in, person person)
{
     in >> person.name >> person.weight;
}
