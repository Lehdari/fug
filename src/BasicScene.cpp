#include "BasicScene.hpp"

#include <iostream>


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
    parentIt->children.push_back(++_nodeId);
    auto it = parentIt + (parentIt->size-1);
    _nodes.emplace(it, _nodeId, parentIt->id);

    return _nodeId;
}
#endif

void BasicScene::removeNode(const NodeId& id)
{
    auto it = _nodes.begin();
    findNode(id, it);
    if (it == _nodes.end())
        return;

    auto parentId = it->parent;
    std::vector<NId> children = it->children;

    for (auto& childId : children)
        removeNode(childId);

    it = _nodes.begin();
    findNode(id, it);

    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    decreaseNodeSize(parentIt);

    _nodes.erase(it);
}

#ifdef FUG_DEBUG
void BasicScene::print(const NodeIterator& beginIt, const NodeIterator& endIt, uint32_t level) {
    NodeIterator it = beginIt;
    for (;it<endIt;) {
        for (auto i=0u; i<level; ++i)
            std::cout << "  ";
        std::cout << "Id: " << it->id << ", Size: " << it->size;

        if (it->components.size() > 0) {
            std::cout << " Comp: ";
            for (auto& c : it->components)
                std::cout << "[" << c.first << ", " << c.second << "] ";
        }

        if (it->children.size() > 0) {
            std::cout << ", Children: ";
            for (auto& childId : it->children)
                std::cout << childId << ", ";
            std::cout << std::endl;

            auto endIt2 = it+it->size;
            print(++it, endIt2, level+1);
            it = endIt2;
        }
        else {
            std::cout << std::endl;
            ++it;
        }
    }
}
#endif

int BasicScene::findNode(const NId& nodeId, NodeIterator& it, const NodeIterator& endIt)
{
    if (it->id == nodeId)
        return 0;

    for (++it; it<endIt; ++it) {
        if (it->id == nodeId)
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

void BasicScene::decreaseNodeSize(NodeIterator& it)
{
    --it->size;
    if (it->parent == 0)
        return;
    auto parentIt = _nodes.begin();
    findNode(it->parent, parentIt);
    increaseNodeSize(parentIt);
}
