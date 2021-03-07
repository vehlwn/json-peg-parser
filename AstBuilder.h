#pragma once

#include <exception>
#include <memory>
#include <peglib.h>
#include <string>

namespace vehlwn::json {
class AstBuilder
{
public:
    AstBuilder();
    std::shared_ptr<peg::Ast> parse(std::string s);

private:
    peg::parser m_parser;
    std::string m_s;
};

struct ParserError : std::exception
{
    ParserError(const std::size_t line, const std::size_t col, std::string msg)
        : line{line}
        , col{col}
        , msg{std::move(msg)}
    {
    }
    const char* what() const noexcept override
    {
        return msg.c_str();
    }

    const std::size_t line;
    const std::size_t col;
    const std::string msg;
};

} // namespace vehlwn::json
