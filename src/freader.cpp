
#include <new>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include "freader.hpp"

namespace tengwar::fs {

FReader::FReader(std::string_view filepath)  : 
    filepath_{filepath},
    fd_{},
    maddr_{},
    finfo_{},
    opened_{} {
        open();
}

FReader::FReader(FReader&& other)  :
    filepath_{other.filepath_},
    fd_{other.fd_},
    maddr_{other.maddr_},
    finfo_{other.finfo_},
    opened_{other.opened_} {
        other.fd_ = -1;
        other.maddr_ = nullptr;
        other.finfo_ = {};
        other.opened_ = false;
}

FReader& FReader::operator=(FReader&& other)  {
    close();
    fd_ = other.fd_;
    maddr_ = other.maddr_;
    finfo_ = other.finfo_;
    opened_ = other.opened_;

    other.fd_ = -1;
    other.maddr_ = nullptr;
    other.finfo_ = {};
    other.opened_ = false;
    
    return *this;
}



FReader::~FReader() {
    close();
}


void FReader::open() {
    if ((fd_ = ::open(filepath_.data(), O_RDONLY)) == -1) {
        //@todo log
        return;
    }

    if (fstat(fd_, &finfo_) == -1) {
        //@todo log
        return;
    }

    if ((maddr_ = static_cast<char*>(mmap(NULL, finfo_.st_size, PROT_READ, MAP_SHARED, fd_, 0))) == MAP_FAILED) {
        //@todo log
        return;
    }
    opened_ = true;
}

void FReader::open(std::string_view filepath) {
    filepath_ = filepath;
    open();
}

void FReader::close() {
    if (fd_ == -1 && opened_ == false) {
        return;
    }
    if (munmap(maddr_, finfo_.st_size) == -1) {
        //@todo log
    }
    ::close(fd_);
}

char FReader::get_char() const {
    return *maddr_;
}
 
void FReader::advance() {
    maddr_++;
}

void FReader::advance(size_t size) {
    maddr_ += size;
}

void FReader::reverse() {
    maddr_--;
}

void FReader::reverse(size_t size) {
    maddr_ -= size;
}

bool FReader::is_opened() noexcept {
    return opened_;
}

}