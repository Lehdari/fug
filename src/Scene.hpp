#ifndef FUG_SCENE_HPP
#define FUG_SCENE_HPP


#include <vector>

#include "Types.hpp"
#include "Visitor.hpp"


namespace fug {


    //  Scene class defines a general interface for global scene data
    //  structure, implementations are introduced through CRTP classes
    template <typename T_Implementation>
    class SceneBase {
    public:
        static SceneBase<T_Implementation>& instance(void);

        template<typename... T_Components>
        NId addNode(T_Components&&... components);

        template<typename... T_Components>
        NId addChildNode(const NId& parent, T_Components&&... components);

        //template<typename T_Visitor, typename... T_Components>1
        //void accept(T_Visitor& visitor);
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


    //  List of implementation class forward declarations
    class BasicScene;

    //  Chosen implementation
    using SceneImplementation   = BasicScene;
    using Scene                 = SceneBase<SceneImplementation>;


}

//  Implementation header files
#include "BasicScene.hpp"


#endif // FUG_SCENE_HPP
