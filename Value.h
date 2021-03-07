#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <variant>
#include <vector>

namespace vehlwn::json {

class Null
{
};
class Bool
{
    bool value;
};
class Number
{
public:
private:
    std::variant<std::int64_t, double> var;
};
class String
{
    std::string value;
};
class Value;
class Array
{
    std::vector<Value> val;
};
class Object
{
    std::map<std::string, Value> value;
};
class Value
{
public:
private:
    std::variant<Null, Bool, Number, String, Array, Object> var;
};
} // namespace vehlwn::json
