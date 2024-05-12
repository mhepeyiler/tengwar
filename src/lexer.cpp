#include <set>
#include <cctype>

#include "lexer.hpp"

using namespace tengwar;


std::unique_ptr<fe::Expression> fe::Lexer::process_next_token() {
    if (!file_.is_opened() || file_.get_char() == EOF) {
        // @todo: Log error
        return nullptr;
    }
    
    while(file_.get_char() == ' ' || file_.get_char() == '\n' || file_.get_char() == '\r') {
        file_.advance();
    }

    std::unique_ptr<fe::Expression> ret;
    if (char c = file_.get_char(); c == '{') {
        ret = std::make_unique<fe::ExecutionExpression>(fe::ExpressionType::kOpenBrace);
    } else if (c == '}') {
        ret = std::make_unique<fe::ExecutionExpression>(fe::ExpressionType::kCloseBrace);
    } else if (c == '(') {
        ret = std::make_unique<fe::ExecutionExpression>(fe::ExpressionType::kOpenParenthesis);
    } else if (c == ')') {
        ret = std::make_unique<fe::ExecutionExpression>(fe::ExpressionType::kCloseParenthesis);
    } else if (c == ';') {
        ret = std::make_unique<fe::ExecutionExpression>(fe::ExpressionType::kSemicolon);
    } else if (c == '-') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kMinus);
    } else if (c == '~') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kBitwise);
    } else if (c == '+') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kAddition);
    } else if (c == '*') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kMultiplication);
    } else if (c == '/') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kDivision);
    } else if (c == ':') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kColon);
    } else if (c == '?') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kQuestionMark);
    } else if (c == ',') {
        ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kComma);
    } else if (c == '&') {
        file_.advance();
        if (file_.get_char() == '&') {
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kAND);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kBitwiseAND);
        }
    } else if (c == '|') {
        file_.advance();
        if (file_.get_char() == '|') {
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kOR);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kBitwiseOR);
        }
    } else if (c == '<') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kSmallerEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kSmaller);
        }
    } else if (c == '>') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kGreaterEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kGreater);
        }
    } else if (c == '!') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kNotEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kLogicalNegation);
        }
    } else if (c == '=') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorExpression>(fe::ExpressionType::kOperator, fe::OperatorType::kAssign);
        }
    } else if (std::isalpha(static_cast<unsigned char>(c))) {
        ret = alpha_lexer(); 
    } else if (std::isalnum(static_cast<unsigned char>(c))) {
        ret = numeric_lexer();
    } else {
        // @todo log error
    }

    file_.advance();
    return ret;
}

std::unique_ptr<fe::Expression> fe::Lexer::alpha_lexer() {
    static std::set<std::string> keyword_set{"int", "return", "if", "else", "for", "while", "do", "break", "continue"};
    std::string alpha;
    
    char c = file_.get_char();

    while (std::isalpha(static_cast<unsigned char>(c)) || std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
        alpha += c;
        file_.advance();
        c = file_.get_char();
    }

    if (keyword_set.contains(alpha)) {
        return std::make_unique<fe::KeywordExpression>(fe::ExpressionType::kKeyword, std::move(alpha));
    }

    return std::make_unique<fe::IdentifierExpression>(fe::ExpressionType::kIdentifier, std::move(alpha));
}

std::unique_ptr<fe::Expression> fe::Lexer::numeric_lexer() {
    std::string numeric;

    char c = file_.get_char();
    
    while (std::isalnum(static_cast<unsigned char>(c))) {
        numeric += c;
        file_.advance();
        c = file_.get_char();
    }

    return std::make_unique<fe::IntegerExpression>(fe::ExpressionType::kIntegralLiteral, numeric);
}

