#ifndef FUG_UTILITY_HH
#define FUG_UTILITY_HH

#include <cstdlib>
#include <string>
#include <cxxabi.h>


namespace fug {

namespace util {


// A mixin class that makes derived classes non-copyable
class noncopyable {
	protected:
		noncopyable() {}
		~noncopyable() {}
	
	private:
		noncopyable(noncopyable const&);
		noncopyable& operator=(noncopyable const&);
};

// Returns human-readable version of type's printable representation
template <typename Type>
std::string str()
{
    const char* name = typeid(Type).name();

#ifdef _WIN32
    return std::string(name);
#else
    int status;

    char* demangled = abi::__cxa_demangle(name, NULL, NULL, &status);
    if (!demangled)
        return std::string(name);

    auto ret = std::string(demangled);
    free(demangled);
    return ret;
#endif
}

// Overload for the function above, for printing a variable's type
template <typename Type>
std::string str(Type&&) {
	return str<Type>();
}

} // namespace util

} // namespace fug


#endif // FUG_UTILITY_HH
