#include <vector>

#include "gtest/gtest.h"
#include "lexer.hpp"

using namespace tengwar;

TEST(LexerTest, SetFile) {
    fe::Lexer lex;
    lex.set_file("files/fe/basic_lexer_test.txt");
    auto token = lex.process_next_token();
    EXPECT_EQ(token->get_type(), fe::ExpressionType::kOpenBrace);
}

TEST(LexerTest, ProcessBasicToken) {
    fe::Lexer lex{"files/fe/basic_lexer_test.txt"};
    std::vector<fe::ExpressionType> token_result_vec{
        fe::ExpressionType::kOpenBrace,
        fe::ExpressionType::kCloseBrace,
        fe::ExpressionType::kOpenParenthesis,
        fe::ExpressionType::kCloseParenthesis,
        fe::ExpressionType::kSemicolon,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kIdentifier,
        fe::ExpressionType::kIntegralLiteral,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kOperator,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kKeyword,
        fe::ExpressionType::kOperator
    };

    for (int i = 0; i < token_result_vec.size(); ++i) {
        auto token = lex.process_next_token();
        EXPECT_EQ(token->get_type(), token_result_vec[i]);
    }

    EXPECT_EQ(lex.process_next_token(), nullptr);
}

template<typename T>
static std::unique_ptr<T> get_derived_expression(fe::Lexer& lex, fe::ExpressionType type) {
    auto token = lex.process_next_token();
    EXPECT_EQ(token->get_type(), type);
    auto* tmp = static_cast<T*>(token.get());
    EXPECT_NE(tmp, nullptr);
    token.release();
    auto ret = std::unique_ptr<T>(tmp);
    return ret;
}

TEST(LexerTest, KeywordExpression) {
    fe::Lexer lex{"files/fe/keyword.txt"};
    
    auto tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "int");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "return");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "for");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "while");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "do");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "if");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "else");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "break");

    tokenKeyword = get_derived_expression<fe::KeywordExpression>(lex, fe::ExpressionType::kKeyword);
    EXPECT_EQ(tokenKeyword->get_keyword(), "continue");
}

TEST(LexerTest, IdentifierExpression) {
    fe::Lexer lex{"files/fe/identifier.txt"};
    
    auto tokenIdentifier = get_derived_expression<fe::IdentifierExpression>(lex, fe::ExpressionType::kIdentifier);
    EXPECT_EQ(tokenIdentifier->get_identifier(), "foo");

    tokenIdentifier = get_derived_expression<fe::IdentifierExpression>(lex, fe::ExpressionType::kIdentifier);
    EXPECT_EQ(tokenIdentifier->get_identifier(), "func");
}

TEST(LexerTest, IntegerExpression) {
    fe::Lexer lex{"files/fe/integer.txt"};
    
    auto tokenIdentifier = get_derived_expression<fe::IntegerExpression>(lex, fe::ExpressionType::kIntegralLiteral);
    EXPECT_EQ(tokenIdentifier->get_integer(), "2145");

    tokenIdentifier = get_derived_expression<fe::IntegerExpression>(lex, fe::ExpressionType::kIntegralLiteral);
    EXPECT_EQ(tokenIdentifier->get_integer(), "45");
}

TEST(LexerTest, OperatorExpression) {
    fe::Lexer lex{"files/fe/operator.txt"};
    
    auto tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kMinus);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kBitwise);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kLogicalNegation);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kAddition);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kMultiplication);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kDivision);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kBitwiseAND);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kAND);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kBitwiseOR);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kOR);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kEquality);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kNotEquality);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kSmaller);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kSmallerEquality);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kGreater);

    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kGreaterEquality);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kColon);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kQuestionMark);
    
    tokenIdentifier = get_derived_expression<fe::OperatorExpression>(lex, fe::ExpressionType::kOperator);
    EXPECT_EQ(tokenIdentifier->get_operator_type(), fe::OperatorType::kComma);
}
