#include "Core/BasicResourceManager.hpp"


using namespace fug;


uint64_t    BasicResourceManager::_typeId = 0;


BasicResourceManager::~BasicResourceManager(void)
{
    //static members are destoryed before calling this constructor
    //for (auto& rInfo : _resourceInfos)
    //    (this->*rInfo.second.destroy)(rInfo.second);
}

void BasicResourceManager::loadResource(const RId& resourceId, bool waitForFinish)
{
    auto& resourceInfo = _resourceInfos.at(resourceId);
    (this->*resourceInfo.init)(resourceInfo);
}
