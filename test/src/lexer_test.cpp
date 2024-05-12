#include <vector>

#include "gtest/gtest.h"
#include "lexer.hpp"

using namespace tengwar;

TEST(LexerTest, SetFile) {
    fe::Lexer lex;
    lex.set_file("files/fe/basic_lexer_test.txt");
    auto token = lex.process_next_token();
    EXPECT_EQ(token->get_type(), fe::TokenType::kOpenBrace);
}

TEST(LexerTest, ProcessBasicToken) {
    fe::Lexer lex{"files/fe/basic_lexer_test.txt"};
    std::vector<fe::TokenType> token_result_vec{
        fe::TokenType::kOpenBrace,
        fe::TokenType::kCloseBrace,
        fe::TokenType::kOpenParenthesis,
        fe::TokenType::kCloseParenthesis,
        fe::TokenType::kSemicolon,
        fe::TokenType::kKeyword,
        fe::TokenType::kKeyword,
        fe::TokenType::kIdentifier,
        fe::TokenType::kIntegralLiteral,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kKeyword,
        fe::TokenType::kKeyword,
        fe::TokenType::kOperator,
        fe::TokenType::kOperator,
        fe::TokenType::kKeyword,
        fe::TokenType::kKeyword,
        fe::TokenType::kKeyword,
        fe::TokenType::kKeyword,
        fe::TokenType::kKeyword,
        fe::TokenType::kOperator
    };

    for (int i = 0; i < token_result_vec.size(); ++i) {
        auto token = lex.process_next_token();
        EXPECT_EQ(token->get_type(), token_result_vec[i]);
    }

    EXPECT_EQ(lex.process_next_token(), nullptr);
}

template<typename T>
static std::unique_ptr<T> get_derived_Token(fe::Lexer& lex, fe::TokenType type) {
    auto token = lex.process_next_token();
    EXPECT_EQ(token->get_type(), type);
    auto* tmp = static_cast<T*>(token.get());
    EXPECT_NE(tmp, nullptr);
    token.release();
    auto ret = std::unique_ptr<T>(tmp);
    return ret;
}

TEST(LexerTest, KeywordToken) {
    fe::Lexer lex{"files/fe/keyword.txt"};
    
    auto tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "int");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "return");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "for");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "while");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "do");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "if");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "else");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "break");

    tokenKeyword = get_derived_Token<fe::KeywordToken>(lex, fe::TokenType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "continue");
}

TEST(LexerTest, IdentifierToken) {
    fe::Lexer lex{"files/fe/identifier.txt"};
    
    auto tokenIdentifier = get_derived_Token<fe::IdentifierToken>(lex, fe::TokenType::kIdentifier);
    EXPECT_EQ(tokenIdentifier->get_identifier(), "foo");

    tokenIdentifier = get_derived_Token<fe::IdentifierToken>(lex, fe::TokenType::kIdentifier);
    EXPECT_EQ(tokenIdentifier->get_identifier(), "func");
}

TEST(LexerTest, IntegerToken) {
    fe::Lexer lex{"files/fe/integer.txt"};
    
    auto tokenIdentifier = get_derived_Token<fe::IntegerToken>(lex, fe::TokenType::kIntegralLiteral);
    EXPECT_EQ(tokenIdentifier->get_integer(), "2145");

    tokenIdentifier = get_derived_Token<fe::IntegerToken>(lex, fe::TokenType::kIntegralLiteral);
    EXPECT_EQ(tokenIdentifier->get_integer(), "45");
}

TEST(LexerTest, OperatorToken) {
    fe::Lexer lex{"files/fe/operator.txt"};
    
    auto tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kMinus);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kBitwise);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kLogicalNegation);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kAddition);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kMultiplication);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kDivision);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kBitwiseAND);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kAND);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kBitwiseOR);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kOR);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kEquality);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kNotEquality);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kSmaller);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kSmallerEquality);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kGreater);

    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kGreaterEquality);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kColon);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kQuestionMark);
    
    tokenIdentifier = get_derived_Token<fe::OperatorToken>(lex, fe::TokenType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kComma);
}
