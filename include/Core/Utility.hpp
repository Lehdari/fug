#ifndef FUG_UTILITY_HH
#define FUG_UTILITY_HH

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

// Returns human-readable versions of types' printable representations
template <typename Type>
std::string str() {
	int status;
	char* demangled = abi::__cxa_demangle(typeid(Type).name(), NULL, NULL, &status);
	if (!status) {
		auto ret = std::string(demangled);
		free(demangled);
		return ret;
	}
	return "???";
}

// Overload for the function above, for printing a variable's type
template <typename Type>
std::string str(Type&&) {
	return str<Type>();
}

} // namespace util

} // namespace fug


#endif // FUG_UTILITY_HH
