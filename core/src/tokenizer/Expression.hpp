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
        std::int32_t eval(std::optional<int32_t> x, std::optional<int32_t> y);

private:
        std::vector<TokenType> tokens;
        std::vector<char> params;
        std::vector<std::string> limits;
};
} // namespace Axiom
