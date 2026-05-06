#pragma once

#include "TokenType.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace Axiom
{

class Expression
{

public:
        float eval(std::optional<int32_t> x, std::optional<int32_t> y);

        // f(x) = x*y {x != 0}
        char func_name;
        std::vector<TokenType> function_body;
        std::vector<char> params;
        std::vector<std::string> limits;
};
} // namespace Axiom
