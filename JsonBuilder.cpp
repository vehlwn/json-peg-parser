#include "JsonBuilder.h"

#include "Value.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unicode/unistr.h>

namespace {
vehlwn::json::Value compileValue(const std::shared_ptr<peg::Ast>& ast);
vehlwn::json::Object compileObject(const std::shared_ptr<peg::Ast>& ast);
vehlwn::json::Array compileArray(const std::shared_ptr<peg::Ast>& ast);
vehlwn::json::String compileString(const std::shared_ptr<peg::Ast>& ast);
vehlwn::json::Number compileNumber(const std::shared_ptr<peg::Ast>& ast);

vehlwn::json::Value compileValue(const std::shared_ptr<peg::Ast>& ast)
{
    std::cout << __func__ << '\n';
    std::cout << "  name = " << ast->name << '\n';
    std::cout << "  choise = " << ast->choice << '\n';
    std::cout << "  token = " << ast->token << '\n';
    std::cout << "  nodes.size = " << ast->nodes.size() << '\n';
    switch(ast->choice)
    {
    case 0:
        return compileObject(ast->nodes[0]);
    case 1:
        return compileArray(ast->nodes[0]);
    case 2:
        return compileString(ast->nodes[0]);
    case 3:
        return compileNumber(ast->nodes[0]);
    case 4:
        return vehlwn::json::Bool{true};
    case 5:
        return vehlwn::json::Bool{false};
    case 6:
        return vehlwn::json::Null{};
    }
    return vehlwn::json::Null{};
}

vehlwn::json::Object compileObject(const std::shared_ptr<peg::Ast>& ast)
{
    std::cout << __func__ << '\n';
    std::cout << "  name = " << ast->name << '\n';
    std::cout << "  choise = " << ast->choice << '\n';
    std::cout << "  token = " << ast->token << '\n';
    std::cout << "  nodes.size = " << ast->nodes.size() << '\n';
    return vehlwn::json::Object{};
}
vehlwn::json::Array compileArray(const std::shared_ptr<peg::Ast>& ast)
{
    return vehlwn::json::Array{};
}
vehlwn::json::String compileString(const std::shared_ptr<peg::Ast>& ast)
{
    std::cout << __func__ << '\n';
    std::cout << "  name = " << ast->name << '\n';
    std::cout << "  choise = " << ast->choice << '\n';
    std::cout << "  token = " << ast->token << '\n';
    std::cout << "  nodes.size = " << ast->nodes.size() << '\n';
    icu::UnicodeString u{
        ast->token.data(),
        static_cast<std::int32_t>(ast->token.size())};
    u = u.unescape();
    std::string ret;
    u.toUTF8String(ret);
    return vehlwn::json::String{std::move(ret)};
}
vehlwn::json::Number compileNumber(const std::shared_ptr<peg::Ast>& ast)
{
    std::cout << __func__ << '\n';
    std::cout << "  name = " << ast->name << '\n';
    std::cout << "  choise = " << ast->choice << '\n';
    std::cout << "  token = " << ast->token << '\n';
    std::cout << "  nodes.size = " << ast->nodes.size() << '\n';
    const std::string copy{ast->token.begin(), ast->token.end()};
    const double result = std::stod(copy);
    return vehlwn::json::Number{result};
}

} // namespace

namespace vehlwn::json {
Value JsonBuilder::exec(const std::shared_ptr<peg::Ast>& start)
{
    std::cout << "name = " << start->name << '\n';
    std::cout << "choise = " << start->choice << '\n';
    std::cout << "token = " << start->token << '\n';
    std::cout << "nodes.size = " << start->nodes.size() << '\n';
    const auto& json = start->nodes[0];
    const auto& element = json->nodes[0];
    const auto& value = element->nodes[1];
    return compileValue(value);
}
} // namespace vehlwn::json
