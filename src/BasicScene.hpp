#ifndef FUG_BASIC_SCENE_HPP
#define FUG_BASIC_SCENE_HPP


#include <vector>
#include <tuple>

#include "Scene.hpp"
#include "Macros.hpp"
#include "TemplateUtils.hpp"
#include "Component.hpp"


namespace fug {


    //Basic Scene CRTP implementation, see Scene.hpp
    class BasicScene : public SceneBase<BasicScene> {
    public:
        struct Node {
            NId                                     id;
            NId                                     parent;
            uint64_t                                size;
            std::vector<NId>                        children;
            std::vector<std::pair<CId, uint64_t>>   components;

            Node(const NId& id, const NId& parent = NId()) :
                id(id), parent(parent), size(1) {}
        };

        using NodeIterator  = std::vector<Node>::iterator;

        #if __cplusplus > 201402L
        #ifdef FUG_DEV
        #warning "C++17 supported, cleanup possible"
        #endif // FUG_DEV

        template<typename... T_Components>
        NId addNode(T_Components&&... components);
        #else
        template<typename T_FirstComponent, typename... T_Components>
        NId addNode(T_FirstComponent&& firstComponent, T_Components&&... components);

        NId addNode(void);

        NId addChildNode(const NId& parent);
        #endif

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
        static NId                  _nodeId;
        static std::vector<Node>    _nodes;

        //  Find node by id
        int findNode(const NId& nodeId, NodeIterator& it, const NodeIterator& endIt = _nodes.end());
        //  Increase/decrease size of a node and its ancestors
        void increaseNodeSize(NodeIterator& it);
        void decreaseNodeSize(NodeIterator& it);

        template <typename T_Component>
        std::vector<T_Component>& accessComponents(void);



        template <typename T_Component>
        using CIter = typename std::vector<T_Component>::iterator;

        #if __cplusplus > 201402L   //  TODO_CPP_VERSION
        #ifdef FUG_DEV
        #warning "C++17 supported, cleanup possible"
        #endif // FUG_DEV

        template <typename T_FirstComponent, typename... T_Components>
        void addComponents(T_FirstComponent&& firstComponent,
                           T_Components&&... components);
        #else
        template <typename T_FirstComponent, typename... T_Components>
        void addComponents(T_FirstComponent&& firstComponent,
                           T_Components&&... components,
                           const NodeIterator& nodeIter);

        template <typename T_Component>
        void addComponents(T_Component&& component,
                           const NodeIterator& nodeIter);
        #endif

        template <typename T_FirstComponent, typename... T_Components>
        void addChildComponents(T_FirstComponent&& firstComponent,
                                T_Components&&... components,
                                NodeIterator& parentIter);

        template <typename T_Component>
        void addChildComponents(T_Component&& component,
                                NodeIterator& parentIter);

        template <typename T_Component>
        inline CIter<T_Component> findComponent(const NodeIterator& nodeIter);


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


    #if __cplusplus > 201402L   //  TODO_CPP_VERSION
    #ifdef FUG_DEV
    #warning "C++17 supported, cleanup possible"
    #endif // FUG_DEV

    template<typename... T_Components>
    NId BasicScene::addNode(T_Components&&... components)
    {
        _nodes.emplace_back(++_nodeId);
        if constexpr (sizeof...(T_Components)>0)
            addComponents<T_Components...>(std::forward<T_Components>(components)...);

        return _nodeId;
    }
    #else
    template <typename T_FirstComponent, typename... T_Components>
    NId BasicScene::addNode(T_FirstComponent&& firstComponent,
                            T_Components&&... components)
    {
        _nodes.emplace_back(++_nodeId);

        addComponents<T_FirstComponent, T_Components...>(std::forward<T_FirstComponent>(firstComponent),
                                                         std::forward<T_Components>(components)...,
                                                         _nodes.end()-1);
        return _nodeId;
    }
    #endif

    #if __cplusplus > 201402L
    #ifdef FUG_DEV
    #warning "C++17 supported, cleanup possible"
    #endif // FUG_DEV

    template <typename... T_Components>
    NId BasicScene::addChildNode(const NId& parent, T_Components&&... components)
    {
        auto parentIt = _nodes.begin();
        findNode(parent, parentIt, _nodes.end());
        if (parentIt == _nodes.end())
            return NId();

        increaseNodeSize(parentIt);
        auto it = parentIt + (parentIt->size-1);
        _nodes.emplace(it, ++_nodeId, parentIt->id);

        if constexpr (sizeof...(T_Components) > 0)
        addComponents<T_Components...>(std::forward<T_Components>(components)...);
        return _nodeId;
    }
    #else
    template <typename... T_Components>
    NId BasicScene::addChildNode(const NId& parent, T_Components&&... components)
    {
        auto parentIt = _nodes.begin();
        findNode(parent, parentIt, _nodes.end());
        if (parentIt == _nodes.end())
            return NId();

        increaseNodeSize(parentIt);
        parentIt->children.push_back(++_nodeId);
        auto it = parentIt + (parentIt->size-1);
        _nodes.emplace(it, _nodeId, parentIt->id);

        auto nnIter = _nodes.begin();
        findNode(_nodeId, nnIter, _nodes.end());
        if (nnIter == _nodes.end())
            return NId();

        addComponents<T_Components...>(std::forward<T_Components>(components)..., nnIter);

        return _nodeId;
    }
    #endif

    template <typename T_Visitor, typename... T_Components>
    void BasicScene::accept(Visitor<T_Visitor, T_Components...>& visitor)
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

    template <typename T_Component>
    std::vector<T_Component>& BasicScene::accessComponents(void)
    {
        static std::vector<T_Component> v;
        return v;
    }

    #if __cplusplus > 201402L
    #ifdef FUG_DEV
    #warning "C++17 supported, cleanup possible"
    #endif // FUG_DEV

    template <typename T_FirstComponent, typename... T_Components>
    void BasicScene::addComponents(T_FirstComponent&& firstComponent,
                                   T_Components&&... components)
    {
        accessComponents<T_FirstComponent>().push_back(firstComponent);

        if constexpr (sizeof...(T_Components) > 0)
            addComponents<T_Components...>(std::forward<T_Components>(components)...);
    }
    #else
    template <typename T_FirstComponent, typename... T_Components>
    void BasicScene::addComponents(T_FirstComponent&& firstComponent,
                                   T_Components&&... components,
                                   const NodeIterator& nodeIter)
    {
        auto& v = accessComponents<T_FirstComponent>();

        //  find iterator for component position
        CId id = Component::typeId<T_FirstComponent>();
        auto cIter = v.end();
        for (auto nIter = nodeIter; nIter < _nodes.end(); ++nIter) {
            for (auto& e : nIter->components) {
                if (e.first == id) {
                    cIter = v.begin() + e.second;
                    break;
                }
            }
        }

        auto ncIter = v.insert(cIter, std::forward<T_FirstComponent>(firstComponent));
        ncIter->_nodeId = _nodeId;

        //  add component id to the node
        nodeIter->components.push_back(std::make_pair(Component::typeId<T_FirstComponent>(),
                                                      v.size()-1));

        //  increase all component ids in nodes after the parent node
        for (auto pIter2 = nodeIter+1; pIter2 != _nodes.end(); ++pIter2)
            for (auto& e : pIter2->components)
                if (e.first == id)
                    ++e.second;

        //  add rest of the components
        addComponents<T_Components...>(std::forward<T_Components>(components)...,
                                       nodeIter);
    }

    template <typename T_Component>
    void BasicScene::addComponents(T_Component&& component,
                                   const NodeIterator& nodeIter)
    {
        auto& v = accessComponents<T_Component>();

        //  find iterator for component position
        CId id = Component::typeId<T_Component>();
        auto cIter = v.end();
        for (auto nIter = nodeIter; nIter < _nodes.end(); ++nIter) {
            for (auto& e : nIter->components) {
                if (e.first == id) {
                    cIter = v.begin() + e.second;
                    break;
                }
            }
        }

        printf("Component position: %llu\n", cIter-v.begin());

        //auto cIter = findComponent<T_Component>(nodeIter);
        //if (cIter != v.end())
            //++cIter;    //  because insert adds in front of given iterator

        auto ncIter = v.insert(cIter, std::forward<T_Component>(component));
        ncIter->_nodeId = _nodeId;

        //  add component id to the node
        nodeIter->components.push_back(std::make_pair(Component::typeId<T_Component>(),
                                                      v.size()-1));

        //  increase all component ids in nodes after the parent node
        for (auto pIter2 = nodeIter+1; pIter2 != _nodes.end(); ++pIter2)
            for (auto& e : pIter2->components)
                if (e.first == id)
                    ++e.second;
    }
    #endif
/*
    template <typename T_FirstComponent, typename... T_Components>
    void BasicScene::addChildComponents(T_FirstComponent&& firstComponent,
                                        T_Components&&... components,
                                        NodeIterator& parentIter)
    {
        auto& v = accessComponents<T_FirstComponent>();
        auto iter = findComponent<T_FirstComponent>(parentIter);
        ++iter;
        auto nIter = v.insert(iter, std::forward<T_FirstComponent>(firstComponent));
        nIter->_nodeId = _nodeId;

        nodeIter->components.push_back(std::make_pair(Component::typeId<T_Component>(),
                                                      v.size()-1));

        CId id = Component::typeId<T_FirstComponent>();
        for (auto pIter2 = parentIter; pIter2 != _nodes.end(); ++pIter2)
            for (auto& e : pIter2->components)
                if (e.first == id)
                    ++e.second;

        addChildComponents<T_Components...>(std::forward<T_Components>(components)..., parentIter);
    }

    template <typename T_Component>
    void BasicScene::addChildComponents(T_Component&& component,
                                        NodeIterator& parentIter)
    {
        auto& v = accessComponents<T_Component>();
        auto iter = findComponent<T_Component>(parentIter);
        ++iter;
        auto nIter = v.insert(iter, std::forward<T_Component>(component));
        nIter->_nodeId = _nodeId;

        CId id = Component::typeId<T_Component>();
        for (auto pIter2 = parentIter; pIter2 != _nodes.end(); ++pIter2)
            for (auto& e : pIter2->components)
                if (e.first == id)
                    ++e.second;
    }
*/
    //  returns component pointed by the node or any node before it containing component of correct type
    template <typename T_Component>
    BasicScene::CIter<T_Component> BasicScene::findComponent(const NodeIterator& nodeIter)
    {
        auto& v = accessComponents<T_Component>();
        CId id = Component::typeId<T_Component>();

        auto cIter = v.begin();
        for (auto nIter = _nodes.begin(); nIter < nodeIter; ++nIter) {
            for (auto& e : nIter->components) {
                if (e.first == id)
                    cIter = v.begin() + e.second;
            }
        }
        return cIter;
    }


    template <typename... T_Components>
    std::tuple<std::vector<T_Components>&...> BasicScene::accessCollection(void)
    {
        return std::tie(accessComponents<T_Components>()...);
    }

    template <typename T_FirstComponent, typename... T_Components>
    void BasicScene::initIterators(std::vector<T_FirstComponent>& firstVector,
                                   std::vector<T_Components>&... restVectors,
                                   CIter<T_FirstComponent>& firstIter,
                                   CIter<T_Components>&... restIters)
    {
        firstIter = firstVector.begin();
        initIterators<T_Components...>(restVectors..., restIters...);
    }

    template <typename T_Component>
    void BasicScene::initIterators(std::vector<T_Component>& vector,
                                   CIter<T_Component>& iter)
    {
        iter = vector.begin();
    }

    template <typename T_FirstComponent, typename... T_Components>
    bool BasicScene::iterate(std::vector<T_FirstComponent>& firstVector,
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

    template <typename T_Component>
    bool BasicScene::iterate(std::vector<T_Component>& vector,
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
