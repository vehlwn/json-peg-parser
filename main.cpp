#include "AstBuilder.h"
#include "JsonBuilder.h"

#include <cassert>
#include <iostream>
#include <peglib.h>
#include <string>

namespace tests {
const std::string s1 = R"(
{
	"key array": [10, -30, 50.4, -73.145, -96.12e-1, 45.91e+1],
	"key bools": [true, false, true, true],
	"key null": null,
	"key object": {
		"nested key": [null, true, false]
	},
	"string key": "hello",
	"number key": 42
})";
} // namespace tests

int main()
{
    using namespace vehlwn::json;
    AstBuilder b;
    JsonBuilder compiler;
    {
        const auto ast = b.parse("true");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto trueValue = compiler.exec(ast);
        assert(trueValue.isBool());
        assert(trueValue.asBool() == true);
    }
    {
        const auto ast = b.parse("false");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto falseValue = compiler.exec(ast);
        assert(falseValue.isBool());
        assert(falseValue.asBool() == false);
    }
    {
        const auto ast = b.parse("null");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto nullValue = compiler.exec(ast);
        assert(nullValue.isNull());
        nullValue.asNull();
    }
    {
        const auto ast = b.parse("88005553535");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveIntValue = compiler.exec(ast);
        assert(positiveIntValue.isNumber());
        assert(positiveIntValue.asNumber() == 88005553535.0);
    }
    {
        const auto ast = b.parse("-88005553535");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeIntValue = compiler.exec(ast);
        assert(negativeIntValue.isNumber());
        assert(negativeIntValue.asNumber() == -88005553535.0);
    }
    {
        const auto ast = b.parse("880055.53535");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveFractionValue = compiler.exec(ast);
        assert(positiveFractionValue.isNumber());
        assert(positiveFractionValue.asNumber() == 880055.53535);
    }
    {
        const auto ast = b.parse("-880055.53535");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeFractionValue = compiler.exec(ast);
        assert(negativeFractionValue.isNumber());
        assert(negativeFractionValue.asNumber() == -880055.53535);
    }
    {
        const auto ast = b.parse("88005553535e10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveIntValueExp = compiler.exec(ast);
        assert(positiveIntValueExp.isNumber());
        assert(positiveIntValueExp.asNumber() == 88005553535e10);
    }
    {
        const auto ast = b.parse("-88005553535e10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeIntValueExp = compiler.exec(ast);
        assert(negativeIntValueExp.isNumber());
        assert(negativeIntValueExp.asNumber() == -88005553535e10);
    }
    {
        const auto ast = b.parse("880055.53535e10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveFractionValueExp = compiler.exec(ast);
        assert(positiveFractionValueExp.isNumber());
        assert(positiveFractionValueExp.asNumber() == 880055.53535e10);
    }
    {
        const auto ast = b.parse("-880055.53535e10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeFractionValueExp = compiler.exec(ast);
        assert(negativeFractionValueExp.isNumber());
        assert(negativeFractionValueExp.asNumber() == -880055.53535e10);
    }
    {
        const auto ast = b.parse("88005553535e+10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveIntValuePositiveExp = compiler.exec(ast);
        assert(positiveIntValuePositiveExp.isNumber());
        assert(positiveIntValuePositiveExp.asNumber() == 88005553535e+10);
    }
    {
        const auto ast = b.parse("-88005553535e+10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeIntPositiveExp = compiler.exec(ast);
        assert(negativeIntPositiveExp.isNumber());
        assert(negativeIntPositiveExp.asNumber() == -88005553535e+10);
    }
    {
        const auto ast = b.parse("880055.53535e+10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveFractionValuePositiveExp = compiler.exec(ast);
        assert(positiveFractionValuePositiveExp.isNumber());
        assert(positiveFractionValuePositiveExp.asNumber() == 880055.53535e+10);
    }
    {
        const auto ast = b.parse("-880055.53535e+10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeFractionValuePositiveExp = compiler.exec(ast);
        assert(negativeFractionValuePositiveExp.isNumber());
        assert(negativeFractionValuePositiveExp.asNumber() == -880055.53535e+10);
    }
    {
        const auto ast = b.parse("88005553535e-10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveIntValueNegativeExp = compiler.exec(ast);
        assert(positiveIntValueNegativeExp.isNumber());
        assert(positiveIntValueNegativeExp.asNumber() == 88005553535e-10);
    }
    {
        const auto ast = b.parse("-88005553535e-10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeIntNegativeExp = compiler.exec(ast);
        assert(negativeIntNegativeExp.isNumber());
        assert(negativeIntNegativeExp.asNumber() == -88005553535e-10);
    }
    {
        const auto ast = b.parse("880055.53535e-10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto positiveFractionValueNegativeExp = compiler.exec(ast);
        assert(positiveFractionValueNegativeExp.isNumber());
        assert(positiveFractionValueNegativeExp.asNumber() == 880055.53535e-10);
    }
    {
        const auto ast = b.parse("-880055.53535e-10");
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto negativeFractionValueNegativeExp = compiler.exec(ast);
        assert(negativeFractionValueNegativeExp.isNumber());
        assert(negativeFractionValueNegativeExp.asNumber() == -880055.53535e-10);
    }
    {
        const std::string s = "";
        const auto ast = b.parse('\"' + s + '\"');
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto emptyStringValue = compiler.exec(ast);
        assert(emptyStringValue.isString());
        assert(emptyStringValue.asString() == s);
    }
    {
        const std::string s = "Vladimir Putin congratulated Russia’s women on "
                              "International Women’s Day.";
        const auto ast = b.parse('\"' + s + '\"');
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto stringValue = compiler.exec(ast);
        assert(stringValue.isString());
        assert(stringValue.asString() == s);
    }
    {
        const std::string escaped =
            R"(\" \\ \/ \b \f \n \r \t \u0048\u0045\u004C\u004C\u004F\u0020\u0055\u004E\u0049\u0043\u004F\u0044\u0045\u000A\u044B)";
        const std::string unescaped =
            "\" \\ / \b \f \n \r \t "
            "\x48\x45\x4C\x4C\x4F\x20\x55\x4E\x49\x43\x4F\x44\x45\x0A\xD1\x8b";
        const auto ast = b.parse('\"' + escaped + '\"');
        std::cout << peg::ast_to_s(ast) << std::endl;
        const auto stringValue = compiler.exec(ast);
        assert(stringValue.isString());
        assert(stringValue.asString() == unescaped);
    }
}
