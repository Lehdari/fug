#ifndef FUG_TEXT_HPP
#define FUG_TEXT_HPP

#include "Core/Resource.hpp"

#include <cstddef>

namespace fug {
    class FUG_RESOURCE(Text) {
    public:
        FUG_RESOURCE_INIT_DESTROY_DECL
        Text(void);
        Text(const Text& other);
        ~Text(void);
        const char *getBufferPtr(void) const;
        size_t getBufferSize(void) const;
    private:
        char* buffer_;
        size_t size_;
    };
}

#endif // FUG_TEXT_HPP
