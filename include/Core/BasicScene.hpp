#ifndef FUG_BASIC_SCENE_HPP
#define FUG_BASIC_SCENE_HPP


#include <vector>
#include <tuple>
#include <unordered_map>
#ifdef FUG_DEBUG
#include <iostream>
#endif

#include "Scene.hpp"
#include "Core/Macros.hpp"
#include "Core/Component.hpp"


namespace fug {


    //Basic Scene CRTP implementation, see Scene.hpp
    class BasicScene : public SceneBase<SceneImplementation> {
    public:
        struct Entity {
            EId id;
            Entity(const EId& id) :
                id(id) {}
        };

        using EntityIterator  = typename std::vector<Entity>::iterator;


        template<typename... T_Components>
        EId addEntity(T_Components&&... components);

        EId addEntity(void);

        void removeEntity(const EntityId& id);

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

        template <typename T_Component>
        static std::vector<T_Component>& accessComponents(void);


        template <typename T_Component>
        using CIter = typename std::vector<T_Component>::iterator;

        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        void addComponents(T_FirstComponent&& firstComponent,
                           T_SecondComponent&& secondComponent,
                           T_Components&&... restComponents);

        template <typename T_Component>
        void addComponents(T_Component&& component);

        void removeComponents(uint64_t pos);

        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        void removeComponents(uint64_t pos);

        template <typename T_Component>
        void removeComponents(uint64_t pos);


        template <typename... T_Components>
        std::tuple<std::vector<T_Components>&...> accessCollection(void);


        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        inline static void initIterators(std::vector<T_FirstComponent>& firstVector,
                                         std::vector<T_SecondComponent>& secondVector,
                                         std::vector<T_Components>&... restVectors,
                                         CIter<T_FirstComponent>& firstIter,
                                         CIter<T_SecondComponent>& secondIter,
                                         CIter<T_Components>&... restIters);

        template <typename T_Component>
        inline static void initIterators(std::vector<T_Component>& vector,
                                         CIter<T_Component>& iter);

        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        inline static bool iterate(std::vector<T_FirstComponent>& firstVector,
                                   std::vector<T_SecondComponent>& secondVector,
                                   std::vector<T_Components>&... restVectors,
                                   CIter<T_FirstComponent>& firstIter,
                                   CIter<T_SecondComponent>& secondIter,
                                   CIter<T_Components>&... restIters,
                                   EId& maxId);

        template <typename T_Component>
        inline static bool iterate(std::vector<T_Component>& vector,
                                   CIter<T_Component>& iter,
                                   EId& maxId);
    };


    #include "BasicScene.tcc"


}   //  namespace fug


#endif // FUG_BASIC_SCENE_HPP
