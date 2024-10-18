#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <memory>
#include <optional>
#include <functional>
#include "../collections/hash_table.hpp"

class context{
     public:
          context(std::shared_ptr<context> parent = nullptr);
          void add(const std::string &variable_name, const std::string &variable_value);
          // void add(const std::string & variable_name, std::string && variable_value);
          std::string& get(const std::string &variable_name);
          std::optional<std::reference_wrapper<std::string>> try_get(const std::string &variable_name);
          bool contains(const std::string &variable_name) const;

     private:
          std::shared_ptr<context> _parent;
          ds::named_table<std::string> _local_variables;
};
#endif