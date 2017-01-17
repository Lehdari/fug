#ifndef FUG_BASE_HPP
#define FUG_BASE_HPP


#include <vector>

#include "Implementation.hpp"
#include "Types.hpp"
#include "Visitor.hpp"


namespace fug {


    //  Scene class defines a general interface for global scene data
    //  structure, implementations are introduced through CRTP classes
    template <typename T_Implementation>
    class SceneBase {
    public:
        //  Get the singleton instance handle
        static SceneBase<T_Implementation>& instance(void);

        //  Add an entity to root
        template<typename... T_Components>
        EId addEntity(T_Components&&... components);

        //  Remove an entity
        void removeEntity(const EId& entity);

        //  Accept a visitor
        template<typename T_Visitor, typename... T_Components>
        void accept(Visitor<T_Visitor, T_Components...>& visitor);

        #ifdef FUG_DEBUG
        void print(void);
        #endif
    };


    #include "Scene.tcc"


    using Scene = SceneBase<SceneImplementation>;

}

/// include implementation headers here
#include "BasicScene.hpp"


#endif // FUG_BASE_HPP
