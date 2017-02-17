#include "Core/Binary.hpp"

#include <cstring>
#include <cstdio>

using namespace fug;

Binary::Binary(void) :
    buffer_(nullptr),
    size_(0)
{
}

Binary::Binary(const Binary& other)
{
    buffer_ = new unsigned char[other.size_];
    memcpy(buffer_, other.buffer_, other.size_);
    size_ = other.size_;
}

const unsigned char *Binary::getBufferPtr(void) const
{
    return buffer_;
}

size_t Binary::getBufferSize(void) const
{
    return size_;
}

Binary::~Binary(void)
{
    if (buffer_)
        delete[] buffer_;
}
