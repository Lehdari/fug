#ifndef FUG_RESOURCE_LOADER_HPP
#define FUG_RESOURCE_LOADER_HPP


#include <string>

#include "json/json.hpp"


namespace fug {

    class ResourceLoader {
    public:
        ResourceLoader(const std::string& fileName);

        void load(void) const;

    private:
        nlohmann::json    _json;
    };

}


#endif // FUG_RESOURCE_LOADER_HPP
