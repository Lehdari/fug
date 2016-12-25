#include "Scene.hpp"


using namespace fug;


NId                         Scene::_nodeId;
std::vector<Scene::Node>    Scene::_nodes;


Scene& Scene::instance(void)
{
    static Scene scene;
    return scene;
}

Scene::Scene(void)
{
}

#if __cplusplus > 201402L   //  TODO_CPP_VERSION
#ifdef FUG_DEV
#warning "C++17 supported, cleanup possible"
#endif // FUG_DEV
#else
NId Scene::addNode(void)
{
    //_nodes.emplace_back(++_nodeId);
    return _nodeId;
}
#endif
