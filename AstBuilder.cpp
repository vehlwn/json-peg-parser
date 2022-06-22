#include "AstBuilder.h"

#include <algorithm>
#include <string_view>

namespace {
constexpr const char* GRAMMAR = R"(
    Start           <- json !(.)
    json            <- element
    value           <- object / array / string / number / 'true' / 'false' / 'null'
    object          <- '{' ws '}' / '{' members '}'
    members         <- member (',' member)*
    member          <- ws string ws ':' element
    array           <- '[' ws ']' / '[' elements ']'
    elements        <- element (',' element)*
    element         <- ws value ws
    string          <- ["] < characters > ["]
    characters      <- character*
    character       <- [^\\"\u0000-\u001F] / '\\' escape
    escape          <- ["] / [\\] / [/] / 'b' / 'f'/ 'n'/ 'r' / 't' / 'u' hex hex hex hex
    hex             <- digit / [A-F] / [a-f]
    number          <- < integer fraction? exponent? >
    integer         <- onenine digits / digit / '-' onenine digits / '-' digit
    digits          <- digit+
    digit           <- '0' / onenine
    onenine         <- [1-9]
    fraction        <- '.' digits
    exponent        <- 'E' sign? digits / 'e' sign? digits
    sign            <- '+' / '-'
    ws              <- ('\u0020' / '\u000A' / '\u000D' / '\u0009')*
)";
} // namespace

namespace vehlwn::json {
AstBuilder::AstBuilder()
{
    m_parser.log =
        [](const std::size_t line, const std::size_t col, const std::string& msg) {
            throw ParserError{line, col, std::move(msg)};
        };
    const bool ok = m_parser.load_grammar(GRAMMAR);
    if(!ok)
        throw std::runtime_error("load_grammar failed");
    m_parser.enable_ast();
    m_parser.enable_packrat_parsing();
}

std::shared_ptr<peg::Ast> AstBuilder::parse(const std::string_view s)
{
    std::shared_ptr<peg::Ast> ast;
    if(m_parser.parse(s, ast))
    {
        return ast;
    }
    throw std::runtime_error("syntax error");
}
} // namespace vehlwn::json
