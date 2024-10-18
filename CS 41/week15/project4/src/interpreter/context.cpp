#include "context.hpp"
#include <stdexcept>

context::context(std::shared_ptr<context> parent)
     : _parent(parent)
{
}

 
void context::add(const std::string &variable_name, const std::string &variable_value){
     _local_variables.insert_or_assign(variable_name, variable_value);
}

std::string &context::get(const std::string &variable_name){
     auto it = _local_variables.find(variable_name);
     if (it != _local_variables.end()) return it->second;
     if (_parent) return _parent->get(variable_name);
     throw std::out_of_range("NameError: name \'"+variable_name+"\' is not found");
}

std::optional<std::reference_wrapper<std::string>> context::try_get(const std::string &variable_name)
{
     auto it = _local_variables.find(variable_name);
     if (it != _local_variables.end()) return std::ref(it->second);
     if (_parent) return _parent->try_get(variable_name);
     return std::nullopt;
}

bool context::contains(const std::string &variable_name) const
{
     return _local_variables.contains(variable_name) or (_parent and _parent->contains(variable_name));
}
