#ifndef FUG_BASE_HPP
#define FUG_BASE_HPP


#include <vector>

#include "Types.hpp"
#include "Macros.hpp"
#include "Visitor.hpp"
#include "SceneImplementation.hpp"


namespace fug {


    //  Scene class defines a general interface for global scene data
    //  structure, implementations are introduced through CRTP classes
    template <typename T_Implementation>
    class SceneBase {
    public:
        //  Get the singleton instance handle
        static SceneBase<T_Implementation>& instance(void);

        //  Add a node to root
        template<typename... T_Components>
        NId addNode(T_Components&&... components);

        //  Add a node as child of another node
        template<typename... T_Components>
        NId addChildNode(const NId& parent, T_Components&&... components);

        //  Remove a node and its children alongside with all the
        //  contained components
        void removeNode(const NId& node);

        //  Accept a visitor
        template<typename T_Visitor, typename... T_Components>
        void accept(Visitor<T_Visitor, T_Components...>& visitor);

        #ifdef FUG_DEBUG
        void print(void);
        #endif
    };


    template <typename T_Implementation>
    SceneBase<T_Implementation>& SceneBase<T_Implementation>::instance(void)
    {
        static SceneBase<T_Implementation> scene;
        return scene;
    }

    template <typename T_Implementation>
    template <typename... T_Components>
    NId SceneBase<T_Implementation>::addNode(T_Components&&... components) {
        return static_cast<T_Implementation*>(this)->
               addNode(std::forward<T_Components>(components)...);
    }

    template <typename T_Implementation>
    template <typename... T_Components>
    NId SceneBase<T_Implementation>::addChildNode(const NId& parent, T_Components&&... components) {
        return static_cast<T_Implementation*>(this)->
               addChildNode(parent, std::forward<T_Components>(components)...);
    }

    template <typename T_Implementation>
    void SceneBase<T_Implementation>::removeNode(const NId& node) {
        return static_cast<T_Implementation*>(this)->removeNode(node);
    }

    template <typename T_Implementation>
    template<typename T_Visitor, typename... T_Components>
    void SceneBase<T_Implementation>::accept(Visitor<T_Visitor, T_Components...>& visitor) {
        return static_cast<T_Implementation*>(this)->accept(visitor);
    }

    #ifdef FUG_DEBUG
    template <typename T_Implementation>
    void SceneBase<T_Implementation>::print(void) {
        return static_cast<T_Implementation*>(this)->print();
    }
    #endif


    using Scene                 = SceneBase<SceneImplementation>;

}
    #include "BasicScene.hpp"


#endif // FUG_BASE_HPP
