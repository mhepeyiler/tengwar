#ifndef TENGWAR_INCLUDE_FREADER_HPP_
#define TENGWAR_INCLUDE_FREADER_HPP_

#include <string_view>

#include <sys/stat.h>


namespace tengwar::fs {

class FReader {
public:
    FReader() noexcept = default;
    FReader(std::string_view filepath);
    
    FReader(FReader&& other);
    FReader& operator=(FReader&& other);

    ~FReader();

    void open();
    void open(std::string_view filepath);
    void close();

    char get_char() const;
    
    void advance();
    void advance(size_t size);

    void reverse();
    void reverse(size_t size);

    bool is_opened() noexcept;
    
    

private:

    std::string_view filepath_;
    int fd_;
    char *maddr_;
    struct stat finfo_;

    bool opened_;
};

}

#endif