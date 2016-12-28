#include "BasicScene.hpp"


using namespace fug;


NId                             BasicScene::_nodeId;
std::vector<BasicScene::Node>   BasicScene::_nodes;


#if __cplusplus > 201402L   //  TODO_CPP_VERSION
#ifdef FUG_DEV
#warning "C++17 supported, cleanup possible"
#endif // FUG_DEV
#else
NId BasicScene::addNode(void)
{
    _nodes.emplace_back(++_nodeId);
    return _nodeId;
}

NId BasicScene::addChildNode(const NId& parent)
{
    auto parentIt = _nodes.begin();
    findNode(parent, parentIt, _nodes.end());
    if (parentIt == _nodes.end())
        return NId();

    increaseNodeSize(parentIt);
    auto it = parentIt + (parentIt->size-1);
    _nodes.emplace(it, ++_nodeId, parentIt->id);

    return _nodeId;
}
#endif

int BasicScene::findNode(const NId& nodeId, NodeIterator& it, const NodeIterator& endIt)
{
    if (it->id == nodeId)
        return 0;

    for (++it; it<endIt;) {
        if (it->id == nodeId)
            return 0;
        else if (it->id > nodeId)
            return 1;
        if (findNode(nodeId, it, it+it->size) == 0)
            return 0;
    }
    return 1;
}

void BasicScene::increaseNodeSize(NodeIterator& it)
{
    ++it->size;
    if (it->parent == 0)
        return;
    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    increaseNodeSize(parentIt);
}