#ifndef FUG_BASIC_SCENE_HPP
#define FUG_BASIC_SCENE_HPP


#include <vector>
#include <tuple>

#include "Scene.hpp"
#include "Macros.hpp"
#include "TemplateUtils.hpp"


namespace fug {


    //Basic Scene CRTP implementation, see Scene.hpp
    class BasicScene : public SceneBase<BasicScene> {
    public:
        struct Node {
            NId                 id;
            NId                 parent;
            uint64_t            size;
            std::vector<NId>    children;

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
                           T_Components&&... components);

        template <typename T_Component>
        void addComponents(T_Component&& component);
        #endif

        //  utilities for accepting visitors
        template <typename... T_Components>
        std::tuple<std::vector<T_Components>&...> accessCollection(void);

        template <typename T_Component>
        using CIter = typename std::vector<T_Component>::iterator;

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
                                                         std::forward<T_Components>(components)...);
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

        if (sizeof...(T_Components) > 0)
        addComponents<T_Components...>(std::forward<T_Components>(components)...);
        return _nodeId;
    }
    #endif

    template <typename T_Visitor, typename... T_Components>
    void BasicScene::accept(Visitor<T_Visitor, T_Components...>& visitor)
    {
        //constexpr uint64_t nComponents = sizeof...(T_Components);
        //printf("nComponents: %llu\n", nComponents);
        //static auto sequence = typename GenSequence<nComponents>::type();

        static auto collection = accessCollection<T_Components...>();

        std::tuple<CIter<T_Components>...> iters;

        initIterators<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                       std::get<typename std::vector<T_Components>::iterator>(iters)...);

        auto maxNodeId = NId();
        ++maxNodeId;
        if (!iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                      std::get<typename std::vector<T_Components>::iterator>(iters)...,
                                      maxNodeId))
            return;

        //printf("nodeId: %llu\n", maxNodeId);
        visitor(*std::get<typename std::vector<T_Components>::iterator>(iters)...);

        while(iterate<T_Components...>(std::get<std::vector<T_Components>&>(collection)...,
                                       ++std::get<typename std::vector<T_Components>::iterator>(iters)...,
                                       maxNodeId)) {
            //printf("nodeId: %llu\n", maxNodeId);
            visitor(*std::get<typename std::vector<T_Components>::iterator>(iters)...);
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
    void BasicScene::addComponents(T_FirstComponent&& firstComponent, T_Components&&... components)
    {
        auto& v1 = accessComponents<T_FirstComponent>();
        v1.push_back(std::forward<T_FirstComponent>(firstComponent));
        v1.back()._nodeId = _nodeId;

        addComponents<T_Components...>(std::forward<T_Components>(components)...);
    }

    template <typename T_Component>
    void BasicScene::addComponents(T_Component&& component)
    {
        auto& v = accessComponents<T_Component>();
        v.push_back(std::forward<T_Component>(component));
        v.back()._nodeId = _nodeId;
    }
    #endif

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

        //for (;maxId > firstIter->_nodeId && firstIter != firstVector.end();) {
        for (;maxId > firstIter->_nodeId && firstIter != firstVector.end(); ++firstIter);
        maxId = firstIter->_nodeId;

        if (!iterate<T_Components...>(restVectors..., restIters..., maxId))
            return false;
        //}

        for (;maxId > firstIter->_nodeId && firstIter != firstVector.end(); ++firstIter);
        maxId = firstIter->_nodeId;
        return true;
    }

    template <typename T_Component>
    bool BasicScene::iterate(std::vector<T_Component>& vector,
                             CIter<T_Component>& iter,
                             NId& maxId)
    {
        for (;maxId > iter->_nodeId && iter != vector.end(); ++iter);
        maxId = iter->_nodeId;
        if (iter == vector.end())
            return false;
        return true;
    }


}   //  namespace fug


#endif // FUG_BASIC_SCENE_HPP
