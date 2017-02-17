#include "Core/Text.hpp"

#include <cstring>
#include <cstdio>

using namespace fug;

Text::Text(void) :
    buffer_(nullptr),
    size_(0)
{
}

Text::Text(const Text& other)
{
    buffer_ = new char[other.size_];
    memcpy(buffer_, other.buffer_, other.size_);
    size_ = other.size_;
}

const char *Text::getBufferPtr(void) const
{
    return buffer_;
}

size_t Text::getBufferSize(void) const
{
    return size_;
}

Text::~Text(void)
{
    if (buffer_)
        delete[] buffer_;
}
