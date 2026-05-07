#pragma once

#include "../math/Expression.hpp"
#include "Token.hpp"
#include <vector>

namespace Axiom
{

class Parser
{

public:
        Parser(const std::vector<Token> tokens);

        Expression convert();
private:
        std::vector<Token> m_tokens;

};
} // namespace Axiom
