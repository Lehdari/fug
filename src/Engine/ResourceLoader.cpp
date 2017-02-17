#include "Engine/ResourceLoader.hpp"

#include <fstream>


using namespace fug;
using namespace nlohmann;


ResourceLoader::ResourceLoader(const std::string& fileName) {
    std::ifstream f(FUG_RES_DIRECTORY+fileName);
    f >> _json;
}


void ResourceLoader::load(void) const {
    auto& root = _json;

    for (auto& resource : root["Resource"]) {
        std::string initInfoType = resource["initInfo"]["type"];
        printf("%s\n", initInfoType.c_str());
        //(FUG_RESOURCE_INIT_INFO_MAP.at(initInfoType))(resource);
    }
}
