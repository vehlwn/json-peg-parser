#include "Value.h"

#include <cassert>
#include <iostream>
#include <string>

int main()
{
    using vehlwn::json::parse;
    {
        const auto trueValue = parse("true");
        assert(trueValue.isBool());
        assert(trueValue.asBool() == true);
    }
    {
        const auto falseValue = parse("false");
        assert(falseValue.isBool());
        assert(falseValue.asBool() == false);
    }
    {
        const auto nullValue = parse("null");
        assert(nullValue.isNull());
        nullValue.asNull();
    }
    {
        const auto positiveIntValue = parse("88005553535");
        assert(positiveIntValue.isNumber());
        assert(positiveIntValue.asNumber() == 88005553535.0);
    }
    {
        const auto negativeIntValue = parse("-88005553535");
        assert(negativeIntValue.isNumber());
        assert(negativeIntValue.asNumber() == -88005553535.0);
    }
    {
        const auto positiveFractionValue = parse("880055.53535");
        assert(positiveFractionValue.isNumber());
        assert(positiveFractionValue.asNumber() == 880055.53535);
    }
    {
        const auto negativeFractionValue = parse("-880055.53535");
        assert(negativeFractionValue.isNumber());
        assert(negativeFractionValue.asNumber() == -880055.53535);
    }
    {
        const auto positiveIntValueExp = parse("88005553535e10");
        assert(positiveIntValueExp.isNumber());
        assert(positiveIntValueExp.asNumber() == 88005553535e10);
    }
    {
        const auto negativeIntValueExp = parse("-88005553535e10");
        assert(negativeIntValueExp.isNumber());
        assert(negativeIntValueExp.asNumber() == -88005553535e10);
    }
    {
        const auto positiveFractionValueExp = parse("880055.53535e10");
        assert(positiveFractionValueExp.isNumber());
        assert(positiveFractionValueExp.asNumber() == 880055.53535e10);
    }
    {
        const auto negativeFractionValueExp = parse("-880055.53535e10");
        assert(negativeFractionValueExp.isNumber());
        assert(negativeFractionValueExp.asNumber() == -880055.53535e10);
    }
    {
        const auto positiveIntValuePositiveExp = parse("88005553535e+10");
        assert(positiveIntValuePositiveExp.isNumber());
        assert(positiveIntValuePositiveExp.asNumber() == 88005553535e+10);
    }
    {
        const auto negativeIntPositiveExp = parse("-88005553535e+10");
        assert(negativeIntPositiveExp.isNumber());
        assert(negativeIntPositiveExp.asNumber() == -88005553535e+10);
    }
    {
        const auto positiveFractionValuePositiveExp = parse("880055.53535e+10");
        assert(positiveFractionValuePositiveExp.isNumber());
        assert(positiveFractionValuePositiveExp.asNumber() == 880055.53535e+10);
    }
    {
        const auto negativeFractionValuePositiveExp = parse("-880055.53535e+10");
        assert(negativeFractionValuePositiveExp.isNumber());
        assert(negativeFractionValuePositiveExp.asNumber() == -880055.53535e+10);
    }
    {
        const auto positiveIntValueNegativeExp = parse("88005553535e-10");
        assert(positiveIntValueNegativeExp.isNumber());
        assert(positiveIntValueNegativeExp.asNumber() == 88005553535e-10);
    }
    {
        const auto negativeIntNegativeExp = parse("-88005553535e-10");
        assert(negativeIntNegativeExp.isNumber());
        assert(negativeIntNegativeExp.asNumber() == -88005553535e-10);
    }
    {
        const auto positiveFractionValueNegativeExp = parse("880055.53535e-10");
        assert(positiveFractionValueNegativeExp.isNumber());
        assert(positiveFractionValueNegativeExp.asNumber() == 880055.53535e-10);
    }
    {
        const auto negativeFractionValueNegativeExp = parse("-880055.53535e-10");
        assert(negativeFractionValueNegativeExp.isNumber());
        assert(negativeFractionValueNegativeExp.asNumber() == -880055.53535e-10);
    }
    {
        const std::string s = "";
        const auto emptyStringValue = parse('\"' + s + '\"');
        assert(emptyStringValue.isString());
        assert(emptyStringValue.asString() == s);
    }
    {
        const std::string s = "Vladimir Putin congratulated Russia’s women on "
                              "International Women’s Day.";
        const auto stringValue = parse('\"' + s + '\"');
        assert(stringValue.isString());
        assert(stringValue.asString() == s);
    }
    {
        const std::string escaped =
            R"(\" \\ \/ \b \f \n \r \t \u0048\u0045\u004C\u004C\u004F\u0020\u0055\u004E\u0049\u0043\u004F\u0044\u0045\u000A\u044B)";
        const std::string unescaped =
            "\" \\ / \b \f \n \r \t "
            "\x48\x45\x4C\x4C\x4F\x20\x55\x4E\x49\x43\x4F\x44\x45\x0A\xD1\x8b";
        const auto stringValue = parse('\"' + escaped + '\"');
        assert(stringValue.isString());
        assert(stringValue.asString() == unescaped);
    }
    {
        const auto emptyArrayValue = parse("[]");
        assert(emptyArrayValue.isArray());
        assert(emptyArrayValue.asArray().empty());
    }
    {
        const auto arrayValue = parse("[42, 10, 1, 74]");
        assert(arrayValue.isArray());
        assert(arrayValue.asArray().size() == 4);
        assert(arrayValue[0].isNumber() && arrayValue[0].asNumber() == 42);
        assert(arrayValue[1].isNumber() && arrayValue[1].asNumber() == 10);
        assert(arrayValue[2].isNumber() && arrayValue[2].asNumber() == 1);
        assert(arrayValue[3].isNumber() && arrayValue[3].asNumber() == 74);
    }
    {
        const auto nestedArrayValue =
            parse(R"([23.59, "sss", ["nested", "array"]])");
        assert(nestedArrayValue.isArray());
        assert(nestedArrayValue.asArray().size() == 3);
        assert(
            nestedArrayValue[0].isNumber()
            && nestedArrayValue[0].asNumber() == 23.59);
        assert(
            nestedArrayValue[1].isString()
            && nestedArrayValue[1].asString() == "sss");
        const auto& nested = nestedArrayValue[2];
        assert(
            nested.isArray() && nested[0].isString()
            && nested[0].asString() == "nested");
        assert(
            nested.isArray() && nested[1].isString()
            && nested[1].asString() == "array");
    }
    {
        const auto objectValue = parse(R"({})");
        assert(objectValue.isObject());
    }
    {
        const auto objectValue = parse(R"({"key": 42})");
        assert(objectValue.isObject());
        const auto& v = objectValue["key"];
        assert(v.isNumber() && v.asNumber() == 42);
    }
    {
        const auto objectValue = parse(R"(
{
	"key array": [10, -30, 50.4, -73.145, -96.12e-1, 45.91e+1],
	"key bools": [true, false, true, true],
	"key null": null,
	"key object": {
		"nested key": [null, true, false]
	},
	"string key": "hello",
	"number key": 42
})");
        assert(objectValue.isObject());
        assert(objectValue["key array"][0].asNumber() == 10);
        assert(objectValue["key array"][1].asNumber() == -30);
        assert(objectValue["key array"][2].asNumber() == 50.4);
        assert(objectValue["key array"][3].asNumber() == -73.145);
        assert(objectValue["key array"][4].asNumber() == -96.12e-1);
        assert(objectValue["key array"][5].asNumber() == 45.91e+1);
        assert(objectValue["key bools"][0].asBool() == true);
        assert(objectValue["key bools"][1].asBool() == false);
        assert(objectValue["key bools"][2].asBool() == true);
        assert(objectValue["key bools"][3].asBool() == true);
        assert(objectValue["key null"].isNull());
        assert(objectValue["key object"]["nested key"][0].isNull());
        assert(objectValue["key object"]["nested key"][1].asBool() == true);
        assert(objectValue["key object"]["nested key"][2].asBool() == false);
        assert(objectValue["string key"].asString() == "hello");
        assert(objectValue["number key"].asNumber() == 42);
    }
}
