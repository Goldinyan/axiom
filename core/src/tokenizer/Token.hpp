#pragma once

#include "TokenType.hpp"
#include <string>

namespace Axiom
{

struct Token
{
        std::string lexeme;
        TokenType type; 

        // Konstruktor hinzufügen, damit emplace_back weiß, was es tun soll
        Token(std::string l, TokenType t) : lexeme(l), type(t) {}
};

} // namespace Axiom
