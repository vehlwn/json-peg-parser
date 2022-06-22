#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace vehlwn::json {

class Null
{
};
class Bool
{
public:
    Bool(bool v)
        : m_value{v}
    {
    }

    bool get() const noexcept
    {
        return m_value;
    }

private:
    bool m_value;
};

class Number
{
public:
    Number(double x)
        : m_value{x}
    {
    }

    double get() const noexcept
    {
        return m_value;
    }

private:
    double m_value;
};

class String
{
public:
    String(std::string x)
        : m_value{std::move(x)}
    {
    }

    const std::string& get() const noexcept
    {
        return m_value;
    }

private:
    std::string m_value;
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
    Value(Null x)
        : m_variant{x}
    {
    }
    Value(Bool x)
        : m_variant{x}
    {
    }
    Value(Number x)
        : m_variant{x}
    {
    }
    Value(String x)
        : m_variant{std::move(x)}
    {
    }
    Value(Array x)
        : m_variant{std::move(x)}
    {
    }
    Value(Object x)
        : m_variant{x}
    {
    }

    bool isNull() const noexcept
    {
        return std::holds_alternative<Null>(m_variant);
    }
    void asNull() const
    {
        std::get<Null>(m_variant);
    }

    bool isBool() const noexcept
    {
        return std::holds_alternative<Bool>(m_variant);
    }
    bool asBool() const
    {
        return std::get<Bool>(m_variant).get();
    }

    bool isNumber() const noexcept
    {
        return std::holds_alternative<Number>(m_variant);
    }
    double asNumber() const
    {
        return std::get<Number>(m_variant).get();
    }

    bool isString() const noexcept
    {
        return std::holds_alternative<String>(m_variant);
    }
    const std::string& asString() const
    {
        return std::get<String>(m_variant).get();
    }

private:
    std::variant<Null, Bool, Number, String, Array, Object> m_variant;
};
} // namespace vehlwn::json
