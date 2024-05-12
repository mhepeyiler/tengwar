#include "freader_test_fixture.hpp"

using namespace tengwar;
using namespace tengwar::test;

TEST_F(FReaderTestFixture, IsOpen) {
    EXPECT_TRUE(file_.is_opened());
}

TEST_F(FReaderTestFixture, Move) {
    EXPECT_TRUE(file_.is_opened());

    fs::FReader file = std::move(file_);
    EXPECT_FALSE(file_.is_opened());
    EXPECT_TRUE(file.is_opened());
}

TEST_F(FReaderTestFixture, GetChar) {
    EXPECT_EQ(file_.get_char(), 'H');
}

TEST_F(FReaderTestFixture, Advance) {
    EXPECT_EQ(file_.get_char(), 'H');
    file_.advance();
    EXPECT_EQ(file_.get_char(), 'i');
}

TEST_F(FReaderTestFixture, MultipleAdvance) {
    EXPECT_EQ(file_.get_char(), 'H');
    file_.advance(4);
    EXPECT_EQ(file_.get_char(), 'T');
}


TEST_F(FReaderTestFixture, Reverse) {
    EXPECT_EQ(file_.get_char(), 'H');
    file_.advance();
    EXPECT_EQ(file_.get_char(), 'i');
    file_.reverse();
    EXPECT_EQ(file_.get_char(), 'H');
}

TEST_F(FReaderTestFixture, MultipleReverse) {
    EXPECT_EQ(file_.get_char(), 'H');
    file_.advance(4);
    EXPECT_EQ(file_.get_char(), 'T');
    file_.reverse(4);
    EXPECT_EQ(file_.get_char(), 'H');
}
