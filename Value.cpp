#include "Value.h"

#include "AstBuilder.h"
#include "JsonBuilder.h"

namespace vehlwn::json {
Value parse(const std::string_view s)
{
    AstBuilder b;
    JsonBuilder compiler;
    const auto ast = b.parse(s);
    Value ret = compiler.exec(ast);
    return ret;
}
} // namespace vehlwn::json
