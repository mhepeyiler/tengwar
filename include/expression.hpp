#ifndef TENGWAR_INCLUDE_EXPRESSION_HPP_
#define TENGWAR_INCLUDE_EXPRESSION_HPP_

#include <string>

namespace tengwar::fe
{
    
enum class ExpressionType {
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

class Expression {
public:
    Expression() = default;
    Expression(ExpressionType type) : type_{type} {}
    virtual ~Expression() = default;
    virtual ExpressionType get_type() const {
        return type_;
    }
protected:
    ExpressionType type_;
};

class ExecutionExpression : public Expression {
public:
    using Expression::Expression;
};

class KeywordExpression : public Expression {
public:
    using Expression::Expression;
    KeywordExpression(ExpressionType type, std::string keyword) : Expression{type}, keyword_{keyword} {} 
    
    std::string get_keyword() && {
        return keyword_;
    }

    const std::string& get_keyword() const& {
        return keyword_;
    }

private:
    std::string keyword_;
};

class IdentifierExpression : public Expression {
public:
    using Expression::Expression;
    IdentifierExpression(ExpressionType type, std::string identifier) : Expression{type}, identifier_{identifier} {} 
    
    std::string get_identifier() && {
        return identifier_;
    }

    const std::string& get_identifier() const& {
        return identifier_;
    }

private:
    std::string identifier_;
    
};

class IntegerExpression : public Expression {
public:
    using Expression::Expression;
    IntegerExpression(ExpressionType type, std::string integer) : Expression{type}, integer_{integer} {} 
    
    std::string get_integer() && {
        return integer_;
    }

    const std::string& get_integer() const& {
        return integer_;
    }

private:
    std::string integer_;
};

class OperatorExpression : public Expression {
public:
    using Expression::Expression;
    OperatorExpression(ExpressionType type, OperatorType op_type) : Expression{type}, op_type_{op_type} {}

    OperatorType get_operator_type() const {
        return op_type_;
    }

private:
    OperatorType op_type_;
};

} // namespace tengwar::fe

#endif