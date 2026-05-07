#include "Parser.hpp"
#include "../utils/logger.hpp"
#include "../math/Expression.hpp"
#include "TokenType.hpp"
#include <vector>

namespace Axiom
{

Parser::Parser(const std::vector<Token> tokens)
{
        if (tokens.empty())
        {
                Logger::err("Tokens cannot be empty!");
        }

        m_tokens = tokens;
};

Expression Parser::convert()
{
        Expression exp;

        for (auto &token : m_tokens)
        {
                if(token.type == TokenType::Char)
                        exp.func_name = token.lexeme.at(0);

                
        }

        return exp;
}

} // namespace Axiom
