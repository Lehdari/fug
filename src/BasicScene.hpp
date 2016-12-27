#ifndef FUG_BASIC_SCENE_HPP
#define FUG_BASIC_SCENE_HPP


#include <vector>
#include <cstdio>

#include "Scene.hpp"
#include "Macros.hpp"


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

        #if __cplusplus > 201402L
        #ifdef FUG_DEV
        #warning "C++17 supported, cleanup possible"
        #endif // FUG_DEV

        template<typename... T_Components>
        NId addNode(T_Components&&... components);
        #else
        template<typename T_FirstComponent, typename... T_Components>
        NId addNode(T_FirstComponent&& firstComponent,
                    T_Components&&... components);

        NId addNode(void);
        #endif

        template<typename... T_Components>
        NId addChildNode(const NId& parent, T_Components&&... components);

        template<typename T_Visitor, typename... T_Components>
        void accept(T_Visitor& visitor);

    private:
        static NId                  _nodeId;
        static std::vector<Node>    _nodes;

        using NodeIterator  = std::vector<Node>::iterator;
        //  Find node by id
        int findNode(const NId& nodeId, NodeIterator& it, const NodeIterator& endIt = _nodes.end());
        //  Increase size of a node and its parents
        void increaseNodeSize(NodeIterator& it);

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
        template <typename T_FirstComponent, typename T_SecondComponent, typename... T_Components>
        void addComponents(T_FirstComponent&& firstComponent,
                           T_SecondComponent&& secondComponent,
                           T_Components&&... components);

        template <typename T_Component>
        void addComponents(T_Component&& component);
        #endif
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

    template <typename... T_Components>
    NId BasicScene::addChildNode(const NId& parent, T_Components&&... components)
    {
        printf("%llu ", parent);
        for (auto& n : _nodes) {
            printf("[%llu, %llu] ", n.id, n.size);
        }
        printf("\n");

        auto parentIt = _nodes.begin();
        findNode(parent, parentIt, _nodes.end());
        if (parentIt == _nodes.end())
            return NId();

        increaseNodeSize(parentIt);
        auto it = parentIt + (parentIt->size-1);
        _nodes.emplace(it, ++_nodeId, parentIt->id);
        return _nodeId;
    }

    template <typename T_Visitor, typename... T_Components>
    void BasicScene::accept(T_Visitor& visitor)
    {

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

        if constexpr (sizeof...(T_Components))
            addComponents<T_Components...>(std::forward<T_Components>(components)...);
    }
    #else
    template <typename T_FirstComponent, typename T_SecondComponent, typename... T_Components>
    void BasicScene::addComponents(T_FirstComponent&& firstComponent,
                                   T_SecondComponent&& secondComponent,
                                   T_Components&&... components)
    {
        auto& v1 = accessComponents<T_FirstComponent>();
        v1.push_back(std::forward<T_FirstComponent>(firstComponent));
        v1.back()._nodeId = _nodeId;

        auto& v2 = accessComponents<T_SecondComponent>();
        v2.push_back(std::forward<T_SecondComponent>(secondComponent));
        v2.back()._nodeId = _nodeId;

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


}


#endif // FUG_BASIC_SCENE_HPP
