#include <set>
#include <cctype>

#include "lexer.hpp"

using namespace tengwar;


std::unique_ptr<fe::Token> fe::Lexer::process_next_token() {
    if (!file_.is_opened() || file_.get_char() == EOF) {
        // @todo: Log error
        return nullptr;
    }
    
    while(file_.get_char() == ' ' || file_.get_char() == '\n' || file_.get_char() == '\r') {
        file_.advance();
    }

    std::unique_ptr<fe::Token> ret;
    if (char c = file_.get_char(); c == '{') {
        ret = std::make_unique<fe::ExecutionToken>(fe::TokenType::kOpenBrace);
    } else if (c == '}') {
        ret = std::make_unique<fe::ExecutionToken>(fe::TokenType::kCloseBrace);
    } else if (c == '(') {
        ret = std::make_unique<fe::ExecutionToken>(fe::TokenType::kOpenParenthesis);
    } else if (c == ')') {
        ret = std::make_unique<fe::ExecutionToken>(fe::TokenType::kCloseParenthesis);
    } else if (c == ';') {
        ret = std::make_unique<fe::ExecutionToken>(fe::TokenType::kSemicolon);
    } else if (c == '-') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kMinus);
    } else if (c == '~') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kBitwise);
    } else if (c == '+') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kAddition);
    } else if (c == '*') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kMultiplication);
    } else if (c == '/') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kDivision);
    } else if (c == ':') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kColon);
    } else if (c == '?') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kQuestionMark);
    } else if (c == ',') {
        ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kComma);
    } else if (c == '&') {
        file_.advance();
        if (file_.get_char() == '&') {
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kAND);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kBitwiseAND);
        }
    } else if (c == '|') {
        file_.advance();
        if (file_.get_char() == '|') {
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kOR);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kBitwiseOR);
        }
    } else if (c == '<') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kSmallerEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kSmaller);
        }
    } else if (c == '>') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kGreaterEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kGreater);
        }
    } else if (c == '!') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kNotEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kLogicalNegation);
        }
    } else if (c == '=') {
        file_.advance();
        if (file_.get_char() == '=') {
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kEquality);
        } else {
            file_.reverse();
            ret = std::make_unique<fe::OperatorToken>(fe::TokenType::kOperator, fe::OperatorType::kAssign);
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

std::unique_ptr<fe::Token> fe::Lexer::alpha_lexer() {
    static std::set<std::string> keyword_set{"int", "return", "if", "else", "for", "while", "do", "break", "continue"};
    std::string alpha;
    
    char c = file_.get_char();

    while (std::isalpha(static_cast<unsigned char>(c)) || std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
        alpha += c;
        file_.advance();
        c = file_.get_char();
    }

    if (keyword_set.contains(alpha)) {
        return std::make_unique<fe::KeywordToken>(fe::TokenType::kKeyword, std::move(alpha));
    }

    return std::make_unique<fe::IdentifierToken>(fe::TokenType::kIdentifier, std::move(alpha));
}

std::unique_ptr<fe::Token> fe::Lexer::numeric_lexer() {
    std::string numeric;

    char c = file_.get_char();
    
    while (std::isalnum(static_cast<unsigned char>(c))) {
        numeric += c;
        file_.advance();
        c = file_.get_char();
    }

    return std::make_unique<fe::IntegerToken>(fe::TokenType::kIntegralLiteral, numeric);
}

