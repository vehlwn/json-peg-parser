#pragma once

#include "Value.h"

#include <exception>
#include <memory>
#include <peglib.h>
#include <string>

namespace vehlwn::json {

class JsonBuilder
{
public:
    Value parse(std::shared_ptr<peg::Ast> ast);
};
} // namespace vehlwn::json
