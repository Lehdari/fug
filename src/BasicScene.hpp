#ifndef FUG_BASIC_SCENE_HPP
#define FUG_BASIC_SCENE_HPP


#include <vector>
#include <tuple>
//#ifdef FUG_DEBUG
#include <iostream>
//#endif

#include "Scene.hpp"
#include "Macros.hpp"
#include "TemplateUtils.hpp"
#include "Component.hpp"


namespace fug {


    //Basic Scene CRTP implementation, see Scene.hpp
    template <typename... T_SceneComponents>
    class BasicScene : public SceneBase<SceneImplementation> {
    public:
        struct Node {
            NId                 id;
            NId                 parent;
            uint64_t            size;
            std::vector<NId>    children;
            uint64_t            componentPos;

            Node(const NId& id, const NId& parent = NId()) :
                id(id), parent(parent), size(1) {}
        };

        using NodeIterator  = typename std::vector<Node>::iterator;


        template<typename T_FirstComponent, typename... T_Components>
        NId addNode(T_FirstComponent&& firstComponent, T_Components&&... components);

        NId addNode(void);

        NId addChildNode(const NId& parent);


        template<typename... T_Components>
        NId addChildNode(const NId& parent, T_Components&&... components);

        void removeNode(const NodeId& id);

        template<typename T_Visitor, typename... T_Components>
        void accept(Visitor<T_Visitor, T_Components...>& visitor);

        #ifdef FUG_DEBUG
        void print(const NodeIterator& beginIt = _nodes.begin(),
                   const NodeIterator& endIt = _nodes.end(),
                   uint32_t level = 0);
        #endif

    private:
        static NId                  _nodeId;    //  running node id, should last to end of the known universe
        static std::vector<Node>    _nodes;     //  vector for nodes

        //  Find node by id
        int findNode(const NId& nodeId, NodeIterator& it, const NodeIterator& endIt = _nodes.end());
        //  Increase/decrease size of a node and its ancestors
        void increaseNodeSize(NodeIterator& it);
        void decreaseNodeSize(NodeIterator& it);

        template <typename T_Component>
        std::vector<T_Component>& accessComponents(void);


        template <typename T_Component>
        using CIter = typename std::vector<T_Component>::iterator;


        template <typename T_FirstComponent, typename... T_Components>
        void addComponents(T_FirstComponent&& firstComponent,
                           T_Components&&... components,
                           uint64_t pos);

        template <typename T_Component>
        void addComponents(T_Component&& component,
                           uint64_t pos);


        template <typename... T_Components>
        std::tuple<std::vector<T_Components>&...> accessCollection(void);


        template <typename T_FirstComponent, typename... T_Components>
        inline static void initIterators(std::vector<T_FirstComponent>& firstVector,
                                         std::vector<T_Components>&... restVectors,
                                         CIter<T_FirstComponent>& firstIter,
                                         CIter<T_Components>&... restIters);

        template <typename T_Component>
        inline static void initIterators(std::vector<T_Component>& vector,
                                         CIter<T_Component>& iter);

        template <typename T_FirstComponent, typename... T_Components>
        inline static bool iterate(std::vector<T_FirstComponent>& firstVector,
                                   std::vector<T_Components>&... restVectors,
                                   CIter<T_FirstComponent>& firstIter,
                                   CIter<T_Components>&... restIters,
                                   NId& maxId);

        template <typename T_Component>
        inline static bool iterate(std::vector<T_Component>& vector,
                                   CIter<T_Component>& iter,
                                   NId& maxId);
    };


    template <typename... T_SceneComponents>
    NId                             BasicScene<T_SceneComponents...>::_nodeId;
    template <typename... T_SceneComponents>
    std::vector<typename BasicScene<T_SceneComponents...>::Node>   BasicScene<T_SceneComponents...>::_nodes;


    template <typename... T_SceneComponents>
    NId BasicScene<T_SceneComponents...>::addNode(void)
    {
        _nodes.emplace_back(++_nodeId);
        return _nodeId;
    }

    template <typename... T_SceneComponents>
    template <typename T_FirstComponent, typename... T_Components>
    NId BasicScene<T_SceneComponents...>::addNode(T_FirstComponent&& firstComponent,
                            T_Components&&... components)
    {
        _nodes.emplace_back(++_nodeId);

        /*addComponents<T_FirstComponent, T_Components...>(std::forward<T_FirstComponent>(firstComponent),
                                                         std::forward<T_Components>(components)...,
                                                         _nodes.end()-1);*/
        return _nodeId;
    }

    template <typename... T_SceneComponents>
    NId BasicScene<T_SceneComponents...>::addChildNode(const NId& parent)
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

    template <typename... T_SceneComponents>
    void BasicScene<T_SceneComponents...>::removeNode(const NodeId& id)
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


    template <typename... T_SceneComponents>
    template <typename... T_Components>
    NId BasicScene<T_SceneComponents...>::addChildNode(const NId& parent, T_Components&&... components)
    {
        auto parentIt = _nodes.begin();
        findNode(parent, parentIt, _nodes.end());
        if (parentIt == _nodes.end())
            return NId();

        increaseNodeSize(parentIt);
        parentIt->children.push_back(++_nodeId);
        auto childIt = parentIt + (parentIt->size-1);
        _nodes.emplace(childIt, _nodeId, parentIt->id);

        for (auto nIt = parentIt; nIt != _nodes.end(); ++nIt)
            ++nIt->componentPos;

        addComponents<T_Components...>(std::forward<T_Components>(components)..., parentIt->componentPos);

        return _nodeId;
    }

    template <typename... T_SceneComponents>
    int BasicScene<T_SceneComponents...>::findNode(const NId& nodeId, NodeIterator& it, const NodeIterator& endIt)
    {
        if (it->id == nodeId)
            return 0;

        for (++it; it<endIt; ++it) {
            if (it->id == nodeId)
                return 0;
        }
        return 1;
    }

    template <typename... T_SceneComponents>
    void BasicScene<T_SceneComponents...>::increaseNodeSize(NodeIterator& it)
    {
        ++it->size;
        if (it->parent == 0)
            return;
        auto parentIt = _nodes.begin();
        findNode(it->parent, parentIt);
        increaseNodeSize(parentIt);
    }

    template <typename... T_SceneComponents>
    void BasicScene<T_SceneComponents...>::decreaseNodeSize(NodeIterator& it)
    {
        --it->size;
        if (it->parent == 0)
            return;
        auto parentIt = _nodes.begin();
        findNode(it->parent, parentIt);
        increaseNodeSize(parentIt);
    }


    template <typename... T_SceneComponents>
    template <typename T_Visitor, typename... T_Components>
    void BasicScene<T_SceneComponents...>::accept(Visitor<T_Visitor, T_Components...>& visitor)
    {
        static auto collection = accessCollection<T_Components...>();

        std::tuple<CIter<T_Components>...> iters;

        initIterators<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                       std::get<CIter<T_Components>>(iters)...);

        auto nodeId = NId();
        ++nodeId;
        if (!iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                      std::get<CIter<T_Components>>(iters)...,
                                      nodeId))
            return;

        if (!visitor(*std::get<CIter<T_Components>>(iters)...))
            nodeId += _nodes[nodeId].size;


        while(iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                       ++std::get<CIter<T_Components>>(iters)...,
                                       nodeId)) {
            if (!visitor(*std::get<CIter<T_Components>>(iters)...))
                nodeId += _nodes[nodeId].size;
        }
    }

    #ifdef FUG_DEBUG
    template <typename... T_SceneComponents>
    void BasicScene<T_SceneComponents...>::print(const NodeIterator& beginIt, const NodeIterator& endIt, uint32_t level) {
        NodeIterator it = beginIt;
        for (;it<endIt;) {
            for (auto i=0u; i<level; ++i)
                std::cout << "  ";
            std::cout << "Id: " << it->id << ", Size: " << it->size;

            std::cout << " Components pos: " << it->componentPos << std::endl;

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

    template <typename... T_SceneComponents>
    template <typename T_Component>
    std::vector<T_Component>& BasicScene<T_SceneComponents...>::accessComponents(void)
    {
        static std::vector<T_Component> v;
        return v;
    }

    template <typename... T_SceneComponents>
    template <typename T_FirstComponent, typename... T_Components>
    void BasicScene<T_SceneComponents...>::addComponents(T_FirstComponent&& firstComponent,
                                   T_Components&&... components,
                                   uint64_t pos)
    {
        auto& v = accessComponents<T_FirstComponent>();
        auto cIt = v.insert(v.begin()+pos, std::forward<T_FirstComponent>(firstComponent));
        cIt->_nodeId = _nodeId;

        //  add rest of the components
        addComponents<T_Components...>(std::forward<T_Components>(components)..., pos);
    }

    template <typename... T_SceneComponents>
    template <typename T_Component>
    void BasicScene<T_SceneComponents...>::addComponents(T_Component&& component, uint64_t pos)
    {
        auto& v = accessComponents<T_Component>();
        auto cIt = v.insert(v.begin()+pos, std::forward<T_Component>(component));
        cIt->_nodeId = _nodeId;
    }

    template <typename... T_SceneComponents>
    template <typename... T_Components>
    std::tuple<std::vector<T_Components>&...> BasicScene<T_SceneComponents...>::accessCollection(void)
    {
        return std::tie(accessComponents<T_Components>()...);
    }

    template <typename... T_SceneComponents>
    template <typename T_FirstComponent, typename... T_Components>
    void BasicScene<T_SceneComponents...>::initIterators(std::vector<T_FirstComponent>& firstVector,
                                   std::vector<T_Components>&... restVectors,
                                   CIter<T_FirstComponent>& firstIter,
                                   CIter<T_Components>&... restIters)
    {
        firstIter = firstVector.begin();
        initIterators<T_Components...>(restVectors..., restIters...);
    }

    template <typename... T_SceneComponents>
    template <typename T_Component>
    void BasicScene<T_SceneComponents...>::initIterators(std::vector<T_Component>& vector,
                                   CIter<T_Component>& iter)
    {
        iter = vector.begin();
    }

    template <typename... T_SceneComponents>
    template <typename T_FirstComponent, typename... T_Components>
    bool BasicScene<T_SceneComponents...>::iterate(std::vector<T_FirstComponent>& firstVector,
                             std::vector<T_Components>&... restVectors,
                             CIter<T_FirstComponent>& firstIter,
                             CIter<T_Components>&... restIters,
                             NId& maxId)
    {

        for (;firstIter != firstVector.end() && maxId > firstIter->_nodeId; ++firstIter);

        if (firstIter == firstVector.end())
            return false;

        maxId = firstIter->_nodeId;

        if (!iterate<T_Components...>(restVectors..., restIters..., maxId))
            return false;

        for (;firstIter != firstVector.end() && maxId > firstIter->_nodeId;) {
            for (;maxId > firstIter->_nodeId && firstIter != firstVector.end(); ++firstIter);
            if (firstIter == firstVector.end() || !iterate<T_Components...>(restVectors..., restIters..., maxId))
                return false;
            maxId = firstIter->_nodeId;
        }

        return true;
    }

    template <typename... T_SceneComponents>
    template <typename T_Component>
    bool BasicScene<T_SceneComponents...>::iterate(std::vector<T_Component>& vector,
                             CIter<T_Component>& iter,
                             NId& maxId)
    {
        for (;iter != vector.end() && maxId > iter->_nodeId; ++iter);
        if (iter == vector.end())
            return false;
        maxId = iter->_nodeId;
        return true;
    }


}   //  namespace fug


#endif // FUG_BASIC_SCENE_HPP
