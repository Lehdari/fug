#include "Core/Resource.hpp"
#include "Core/ResourceInitInfoMap.hpp"

#include "Engine/ResourceLoader.hpp"

#include <fstream>


using namespace fug;
using namespace nlohmann;


ResourceLoader::ResourceLoader(const std::string& fileName) {
    std::ifstream f(std::string(FUG_RES_DIRECTORY) + fileName);
    f >> _json;
}


void ResourceLoader::load(void) const {
    auto& root = _json;

    for (auto& resource : root["Resource"]) {
        std::string initInfoType = resource["initInfo"]["type"];
        printf("type: %s\n", initInfoType.c_str());
        FUG_RESOURCE_INIT_INFO_MAP.getInitFunc(initInfoType)(resource);
    }
}
