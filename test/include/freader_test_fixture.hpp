#ifndef TENGWAR_TEST_INCLUDE_FREADER_TEST_FIXTURE_HPP_
#define TENGWAR_TEST_INCLUDE_FREADER_TEST_FIXTURE_HPP_

#include "freader.hpp" 

#include "gtest/gtest.h"

namespace tengwar::test {

class FReaderTestFixture : public testing::Test {
protected:

    FReaderTestFixture() : file_{"files/fs/reader_test.txt"} {}

    tengwar::fs::FReader file_;
};

}
#endif