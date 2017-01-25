#ifndef FUG_BASIC_SCENE_HPP
#define FUG_BASIC_SCENE_HPP


#include <algorithm>
#include <vector>
#include <tuple>
#include <unordered_map>

#include "Scene.hpp"
#include "Core/Macros.hpp"

#ifdef FUG_DEBUG
#include <iostream>
#endif

namespace fug {


    //Basic Scene CRTP implementation, see Scene.hpp
    class BasicScene : public SceneBase<SceneImplementation> {
    public:
        struct Entity {
            EId id;
            std::vector<void(BasicScene::*)(const EId&)> removePtrs;   //function pointers for component removal

            Entity(const EId& id) :
                id(id) {}

            Entity(const EId& id, std::vector<void(BasicScene::*)(const EId&)>&& removePtrs) :
                id(id), removePtrs(removePtrs) {}
        };

        using EntityIterator  = typename std::vector<Entity>::iterator;


        template<typename... T_Components>
        EId addEntity(T_Components&&... components);

        EId addEntity(void);

        void removeEntity(const EId& entityId);

        template<typename T_Visitor, typename... T_Components>
        void accept(Visitor<T_Visitor, T_Components...>& visitor);

        #ifdef FUG_DEBUG
        void print(void);
        #endif

    private:
        static EId                  _entityId;    //  running entity id, should last to end of the known universe
        static std::vector<Entity>  _entities;     //  vector for entitys

        //  Find entity by id
        int findEntity(const EId& entityId, EntityIterator& it,
                       const EntityIterator& endIt = _entities.end());

        //  Component wrapper for including entity id into components stored in vectors
        template <typename T_Component>
        struct ComponentWrapper {
            EId         entityId;
            T_Component component;
        };


        template <typename T_Component>
        using ComponentVector = std::vector<ComponentWrapper<T_Component>>;

        template <typename T_Component>
        using ComponentIter = typename ComponentVector<T_Component>::iterator;

        template <typename... T_Components>
        using ComponentCollection = std::tuple<ComponentVector<T_Components>&...>;


        template <typename T_Component>
        static ComponentVector<T_Component>& accessComponents(void);

        template <typename... T_Components>
        ComponentCollection<T_Components...> accessCollection(void);


        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        void addComponents(T_FirstComponent&& firstComponent,
                           T_SecondComponent&& secondComponent,
                           T_Components&&... restComponents);

        template <typename T_Component>
        void addComponents(T_Component&& component);

        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        void removeComponents(const EId& entityId);

        template <typename T_Component>
        void removeComponents(const EId& entityId);


        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        inline static void initIterators(ComponentVector<T_FirstComponent>& firstVector,
                                         ComponentVector<T_SecondComponent>& secondVector,
                                         ComponentVector<T_Components>&... restVectors,
                                         ComponentIter<T_FirstComponent>& firstIter,
                                         ComponentIter<T_SecondComponent>& secondIter,
                                         ComponentIter<T_Components>&... restIters);

        template <typename T_Component>
        inline static void initIterators(ComponentVector<T_Component>& vector,
                                         ComponentIter<T_Component>& iter);

        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        inline static bool iterate(ComponentVector<T_FirstComponent>& firstVector,
                                   ComponentVector<T_SecondComponent>& secondVector,
                                   ComponentVector<T_Components>&... restVectors,
                                   ComponentIter<T_FirstComponent>& firstIter,
                                   ComponentIter<T_SecondComponent>& secondIter,
                                   ComponentIter<T_Components>&... restIters,
                                   EId& maxId);

        template <typename T_Component>
        inline static bool iterate(ComponentVector<T_Component>& vector,
                                   ComponentIter<T_Component>& iter,
                                   EId& maxId);
    };


    #include "BasicScene.tcc"


}   //  namespace fug


#endif // FUG_BASIC_SCENE_HPP
