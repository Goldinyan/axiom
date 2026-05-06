#pragma once

#include "Token.hpp"
#include "TokenType.hpp"
#include <string>
#include <vector>

namespace Axiom
{

class Lexer
{

public:
        Lexer(const std::string &expression);

        const std::vector<Token> &tokenize();
        std::vector<Token> get_tokens();

private:
        void handle_token();
        void add_token(TokenType type);

private:
        bool is_at_end() const;
        char current() const; // const bc it doesnt change anything;
        bool match(char c);
        std::string substr() const;

private:
        std::vector<Token> m_tokens{};
        std::string m_expression{};

        size_t m_current{};
        size_t m_start{};
};

} // namespace Axiom
