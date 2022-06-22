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
public:
    Array(std::vector<Value> x)
        : m_value{std::move(x)}
    {
    }

    const std::vector<Value>& get() const noexcept
    {
        return m_value;
    }

private:
    std::vector<Value> m_value;
};

class Object
{
public:
    Object(std::map<std::string, Value> x)
        : m_value{std::move(x)}
    {
    }

    const std::map<std::string, Value>& get() const noexcept
    {
        return m_value;
    }

private:
    std::map<std::string, Value> m_value;
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

    bool isArray() const noexcept
    {
        return std::holds_alternative<Array>(m_variant);
    }
    const std::vector<Value>& asArray() const
    {
        return std::get<Array>(m_variant).get();
    }
    const Value& operator[](const std::size_t i) const
    {
        return asArray()[i];
    }

    bool isObject() const noexcept
    {
        return std::holds_alternative<Object>(m_variant);
    }
    const std::map<std::string, Value>& asObject() const
    {
        return std::get<Object>(m_variant).get();
    }
    const Value& operator[](const std::string i) const
    {
        return asObject().at(i);
    }

private:
    std::variant<Null, Bool, Number, String, Array, Object> m_variant;
};
} // namespace vehlwn::json
