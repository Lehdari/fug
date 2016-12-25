#ifndef FUG_SCENE_HPP
#define FUG_SCENE_HPP


#include <vector>
#include <tuple>

#include "Macros.hpp"
#include "Types.hpp"
#include "Visitor.hpp"


namespace fug {


    class Scene {
    public:
        static Scene& instance(void);

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

        //template<typename... T_Components>
        //NId addNode(const NId& parent, T_Components&&... components);

        template<typename T_Visitor, typename... T_Components>
        void accept(T_Visitor& visitor);

    private:
        Scene(void);

        struct Node {
            NId                 id;
            std::vector<NId>    children;
            Node(const NId& id) : id(id) {}
        };

        static NId                  _nodeId;
        static std::vector<Node>    _nodes;

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


        template <typename... T_Components>
        using Collection    = std::tuple<std::vector<T_Components>&...>;

        template <typename... T_Components>
        std::tuple<std::vector<T_Components>&...> accessCollection(void);
    };


    #if __cplusplus > 201402L   //  TODO_CPP_VERSION
    #ifdef FUG_DEV
    #warning "C++17 supported, cleanup possible"
    #endif // FUG_DEV

    template<typename... T_Components>
    NId Scene::addNode(T_Components&&... components)
    {
        _nodes.emplace_back(++_nodeId);
        if constexpr (sizeof...(T_Components)>0)
            addComponents<T_Components...>(std::forward<T_Components>(components)...);

        return _nodeId;
    }
    #else
    template<typename T_FirstComponent, typename... T_Components>
    NId Scene::addNode(T_FirstComponent&& firstComponent,
                       T_Components&&... components)
    {
        _nodes.emplace_back(++_nodeId);
        addComponents<T_FirstComponent, T_Components...>(std::forward<T_FirstComponent>(firstComponent),
                                                         std::forward<T_Components>(components)...);
        return _nodeId;
    }
    #endif

    template <typename T_Visitor, typename... T_Components>
    void Scene::accept(T_Visitor& visitor)
    {

    }

    template <typename T_Component>
    std::vector<T_Component>& Scene::accessComponents(void)
    {
        static std::vector<T_Component> v;
        return v;
    }

    #if __cplusplus > 201402L
    #ifdef FUG_DEV
    #warning "C++17 supported, cleanup possible"
    #endif // FUG_DEV

    template <typename T_FirstComponent, typename... T_Components>
    void Scene::addComponents(T_FirstComponent&& firstComponent,
                              T_Components&&... components)
    {
        accessComponents<T_FirstComponent>().push_back(firstComponent);

        if constexpr (sizeof...(T_Components))
            addComponents<T_Components...>(std::forward<T_Components>(components)...);
    }
    #else
    template <typename T_FirstComponent, typename T_SecondComponent, typename... T_Components>
    void Scene::addComponents(T_FirstComponent&& firstComponent,
                              T_SecondComponent&& secondComponent,
                              T_Components&&... components)
    {
        accessComponents<T_FirstComponent>().push_back(firstComponent);
        accessComponents<T_SecondComponent>().push_back(secondComponent);
        addComponents<T_Components...>(std::forward<T_Components>(components)...);
    }

    template <typename T_Component>
    void Scene::addComponents(T_Component&& component)
    {
        accessComponents<T_Component>().push_back(component);
    }
    #endif

    template <typename... T_Components>
    std::tuple<std::vector<T_Components>&...> Scene::accessCollection(void)
    {
        return std::tie(accessComponents<T_Components>()...);
    }


}

#endif // FUG_SCENE_HPP
