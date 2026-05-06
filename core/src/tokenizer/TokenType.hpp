#pragma once

#include <vector>

namespace Axiom
{
enum class TokenType
{
        // Literals & Variables
        Number,
        X,
        Y,
        Z,

        // Single Character Tokens
        LeftParen,  // (
        RightParen, // )
        Plus,       // +
        Minus,      // -
        Star,       // *
        Slash,      // /
        Caret,      // ^ (für x^2)
        Equal,      // =
        Comma,      // ,

        // Logic & Comparison
        Bang,    // !
        NotEqual,
        Less,    // <
        Greater, // >
        LessEqual,
        GreaterEqual,

        // Math Functions (Multi-Character)
        Sin,
        Cos,
        Tan,
        Sqrt, // Wurzel

        // Meta
        EndOfFile,
        Unknown
};

static std::vector<TokenType> KEYWORDS{
    TokenType::Number,
    TokenType::X, // x, y, z
    TokenType::Y, // x, y, z
    TokenType::Z, // x, y, z

    // Single Character Tokens
    TokenType::LeftParen,  // (
    TokenType::RightParen, // )
    TokenType::Plus,       // +
    TokenType::Minus,      // -
    TokenType::Star,       // *
    TokenType::Slash,      // /
    TokenType::Caret,      // ^ (für x^2)
    TokenType::Equal,      // =
    TokenType::Comma,      // ,

    // Logic & Comparison
    TokenType::Bang,    // !
    TokenType::Less,    // <
    TokenType::Greater, // >
    TokenType::LessEqual,
    TokenType::GreaterEqual,

    // Math Functions (Multi-Character)
    TokenType::Sin,
    TokenType::Cos,
    TokenType::Tan,
    TokenType::Sqrt, // Wurzel

    // Meta
    TokenType::EndOfFile,
    TokenType::Unknown

};
} // namespace Axiom
