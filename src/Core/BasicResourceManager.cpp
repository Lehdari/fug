#include "Core/BasicResourceManager.hpp"


using namespace fug;


uint64_t    BasicResourceManager::_resourceTypeId = 0;


void BasicResourceManager::loadResource(const RId& resourceId, bool waitForFinish)
{
    auto& resourceInfo = _resourceInfos.at(resourceId);
    (this->*resourceInfo.init)(resourceId, resourceInfo);
}
