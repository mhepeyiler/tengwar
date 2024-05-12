#ifndef TENGWAR_LEXER_HPP_
#define TENGWAR_LEXER_HPP_

#include <list>
#include <memory>

#include "freader.hpp"
#include "expression.hpp"

namespace tengwar::fe {

class Lexer {
public:
    Lexer() = default;
    Lexer(fs::FReader file) : file_{std::move(file)} {};
    Lexer(std::string_view filepath) : file_{fs::FReader{filepath}} {};

    void set_file(fs::FReader file) { file_ = std::move(file); }
    void set_file(std::string_view filepath) { set_file(fs::FReader{filepath}); }

    std::unique_ptr<fe::Expression> process_next_token();

private:
    fs::FReader file_;

    std::unique_ptr<fe::Expression> numeric_lexer();
    std::unique_ptr<fe::Expression> alpha_lexer();

};

}

#endif