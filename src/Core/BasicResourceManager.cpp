#include "Core/BasicResourceManager.hpp"


using namespace fug;


void BasicResourceManager::loadResource(const RId& resourceId, bool waitForFinish)
{
    auto& resourceInfo = _resourceInfos.at(resourceId);
    (this->*resourceInfo.init)(resourceId, resourceInfo);
}
