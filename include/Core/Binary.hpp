#ifndef FUG_BINARY_HPP
#define FUG_BINARY_HPP

#include "Core/Resource.hpp"

#include <cstddef>

namespace fug {
    class FUG_RESOURCE(Binary) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        Binary(void);
        Binary(const Binary& other);
        ~Binary(void);
        const unsigned char *getBufferPtr(void) const;
        size_t getBufferSize(void) const;
    private:
        unsigned char* buffer_;
        size_t size_;
    };
}

#endif // FUG_BINARY_HPP
