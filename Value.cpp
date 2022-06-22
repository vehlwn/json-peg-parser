#include "Value.h"

#include "AstBuilder.h"
#include "JsonBuilder.h"

namespace vehlwn::json {
Bool::Bool(bool v)
    : m_value{v}
{
}

bool Bool::get() const noexcept
{
    return m_value;
}
Number::Number(double x)
    : m_value{x}
{
}

double Number::get() const noexcept
{
    return m_value;
}
Array::Array(std::vector<Value> x)
    : m_value{std::move(x)}
{
}

const std::vector<Value>& Array::get() const noexcept
{
    return m_value;
}
Object::Object(std::map<std::string, Value> x)
    : m_value{std::move(x)}
{
}

const std::map<std::string, Value>& Object::get() const noexcept
{
    return m_value;
}
Value parse(const std::string_view s)
{
    AstBuilder b;
    JsonBuilder compiler;
    const auto ast = b.parse(s);
    Value ret = compiler.exec(ast);
    return ret;
}
} // namespace vehlwn::json
