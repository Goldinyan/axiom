#include "Lexer.hpp"
#include "../utils/logger.hpp"
#include "TokenType.hpp"
#include "fmt/core.h"
#include <iostream>
#include <vector>

namespace Axiom
{

Lexer::Lexer(const std::string &expression)
{
        if (expression.empty())
        {
                Logger::err("Expression cannot be empty!");
        }

        m_expression = expression;
};

const std::vector<Token> &Lexer::tokenize()
{
        // std::cout << "Tokenize!\n";
        if (m_tokens.empty())
        {
                while (!is_at_end())
                {
                        m_start = m_current;
                        handle_token();
                }
        }

        return m_tokens;
};

void Lexer::handle_token()
{
        std::cout << "Handling Token!\n";
        auto c{current()};

        m_current++; // inc bc we already have cur c

        switch (c)
        {

#pragma region single_chars

        case 'x':
                add_token(TokenType::X);
                break;
        case 'y':
                add_token(TokenType::Y);
                break;
        case 'z':
                add_token(TokenType::Z);
                break;
        case '(':
                add_token(TokenType::LeftParen);
                break;
        case ')':
                add_token(TokenType::RightParen);
                break;
        case '+':
                add_token(TokenType::Plus);
                break;
        case '-':
                add_token(TokenType::Minus);
                break;
        case '*':
                add_token(TokenType::Star);
                break;
        case '/':
                add_token(TokenType::Slash);
                break;
        case '^':
                add_token(TokenType::Caret);
                break;
        case '=':
                add_token(TokenType::Equal);
                break;
        case ',':
                add_token(TokenType::Comma);
                break;

#pragma endregion

        case '!':
                add_token(match('=') ? TokenType::NotEqual : TokenType::Bang);
                break;
        case '<':
                add_token(match('=') ? TokenType::LessEqual : TokenType::Less);
                break;
        case '>':
                add_token(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
                break;

        // ignore white spaces
        case ' ':
        case '\r':
        case '\t':
        case '\n':
                break;

        default:

                if (std::isalpha(c))
                {
                }
        }
};

bool Lexer::is_at_end() const
{
        return m_current >= m_expression.size();
};

char Lexer::current() const
{
        if (is_at_end())
                return '\0'; // null term

        return m_expression[m_current];
};

bool Lexer::match(char c)
{
        if (current() == c)
        {
                m_current++;
                return true;
        }
        return false;
};

void Lexer::add_token(TokenType type)
{
        m_tokens.emplace_back(substr(), type);
        Logger::info(fmt::format("Token gefunden: Type {}\n", static_cast<int>(type)));
}

std::vector<Token> Lexer::get_tokens()
{
        return m_tokens;
};

std::string Lexer::substr() const
{
        return m_expression.substr(m_start, m_current - m_start);
}

} // namespace Axiom
