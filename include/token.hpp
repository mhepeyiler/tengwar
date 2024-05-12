#ifndef TENGWAR_INCLUDE_Token_HPP_
#define TENGWAR_INCLUDE_Token_HPP_

#include <string>

namespace tengwar::fe
{
    
enum class TokenType {
    kNone,
    kOpenBrace,
    kCloseBrace,
    kOpenParenthesis,
    kCloseParenthesis,
    kSemicolon,
    kKeyword,
    kIdentifier,
    kIntegralLiteral,
    kOperator,
};

enum class OperatorType {
    kMinus,
    kBitwise,
    kLogicalNegation,
    kAddition,
    kMultiplication,
    kDivision,
    kBitwiseAND,
    kBitwiseOR,
    kAND,
    kOR,
    kEquality,
    kNotEquality,
    kSmaller,
    kSmallerEquality,
    kGreater,
    kGreaterEquality,
    kAssign,
    kColon,
    kQuestionMark,
    kComma,
};

class Token {
public:
    Token() = default;
    Token(TokenType type) : type_{type} {}
    virtual ~Token() = default;
    virtual TokenType get_type() const {
        return type_;
    }
protected:
    TokenType type_;
};

class ExecutionToken : public Token {
public:
    using Token::Token;
};

class KeywordToken : public Token {
public:
    using Token::Token;
    KeywordToken(TokenType type, std::string keyword) : Token{type}, keyword_{keyword} {} 
    
    std::string get_keyword() && {
        return keyword_;
    }

    const std::string& get_keyword() const& {
        return keyword_;
    }

private:
    std::string keyword_;
};

class IdentifierToken : public Token {
public:
    using Token::Token;
    IdentifierToken(TokenType type, std::string identifier) : Token{type}, identifier_{identifier} {} 
    
    std::string get_identifier() && {
        return identifier_;
    }

    const std::string& get_identifier() const& {
        return identifier_;
    }

private:
    std::string identifier_;
    
};

class IntegerToken : public Token {
public:
    using Token::Token;
    IntegerToken(TokenType type, std::string integer) : Token{type}, integer_{integer} {} 
    
    std::string get_integer() && {
        return integer_;
    }

    const std::string& get_integer() const& {
        return integer_;
    }

private:
    std::string integer_;
};

class OperatorToken : public Token {
public:
    using Token::Token;
    OperatorToken(TokenType type, OperatorType op_type) : Token{type}, op_type_{op_type} {}

    OperatorType get_operator_type() const {
        return op_type_;
    }

private:
    OperatorType op_type_;
};

} // namespace tengwar::fe

#endif