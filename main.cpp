#include "AstBuilder.h"
#include "peglib.h"

#include <iostream>
int main()
{
    using namespace vehlwn::json;
    AstBuilder b;
    auto ast = b.parse(R"(
{
	"key array": [10, -30, 50.4, -73.145, -96.12e-1, 45.91e+1],
	"key bools": [true, false, true, true],
	"key null": null,
	"key object": {
		"nested key": [null, true, false]
	},
	"string key": "hello",
	"number key": 42
}
    )");
    std::cout << peg::ast_to_s(ast) << std::endl;
}
