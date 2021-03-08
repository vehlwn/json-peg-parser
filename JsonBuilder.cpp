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
    if(ast->choice == 0)
        return vehlwn::json::Object{{}};

    const auto& members = ast->nodes[0];
    std::map<std::string, vehlwn::json::Value> ret;
    for(const auto& member : members->nodes)
    {
        std::string key{member->nodes[1]->token};
        vehlwn::json::Value value = compileValue(member->nodes[3]->nodes[1]);
        ret.emplace(std::move(key), std::move(value));
    }
    return ret;
}
vehlwn::json::Array compileArray(const std::shared_ptr<peg::Ast>& ast)
{
    if(ast->choice == 0)
        return vehlwn::json::Array{{}};

    const auto& elements = ast->nodes[0];
    std::vector<vehlwn::json::Value> ret;
    ret.reserve(elements->nodes.size());
    for(const auto& element : elements->nodes)
    {
        const auto& value = element->nodes[1];
        ret.push_back(compileValue(value));
    }
    return ret;
}
vehlwn::json::String compileString(const std::shared_ptr<peg::Ast>& ast)
{
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
    const std::string copy{ast->token.begin(), ast->token.end()};
    const double result = std::stod(copy);
    return vehlwn::json::Number{result};
}

} // namespace

namespace vehlwn::json {
Value JsonBuilder::exec(const std::shared_ptr<peg::Ast>& start)
{
    const auto& json = start->nodes[0];
    const auto& element = json->nodes[0];
    const auto& value = element->nodes[1];
    return compileValue(value);
}
} // namespace vehlwn::json
