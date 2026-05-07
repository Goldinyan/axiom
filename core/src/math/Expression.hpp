#pragma once

#include "../tokenizer/TokenType.hpp"
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace Axiom
{

class Expression
{

public:
        Expression() = default;

        float eval(std::optional<float> x, std::optional<float> y);

        // f(x) = x*y {x != 0}
        char func_name;
        std::vector<TokenType> function_body;
        std::array<bool, 2> params; // 0 -> x, 1 -> y
        std::vector<std::string> limits;
};
} // namespace Axiom
