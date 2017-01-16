#ifndef FUG_BASIC_SCENE_HPP
#define FUG_BASIC_SCENE_HPP


#include <vector>
#include <tuple>
#include <unordered_map>
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
        int findNode(const NId& nodeId, NodeIterator& it,
                     const NodeIterator& endIt = _nodes.end());
        //  Increase/decrease size of a node and its ancestors
        void increaseNodeSize(NodeIterator& it);
        void decreaseNodeSize(NodeIterator& it);

        template <typename T_Component>
        static std::vector<T_Component>& accessComponents(void);

        static std::tuple<std::vector<T_SceneComponents>&...>   _components;


        template <typename T_Component>
        using CIter = typename std::vector<T_Component>::iterator;

        void addComponents(uint64_t pos);

        template <typename T_FirstComponent,
                  typename T_SecondComponent,
                  typename... T_Components>
        void addComponents(uint64_t pos);

        template <typename T_Component>
        void addComponents(uint64_t pos);

        template <typename T_FirstComponent, typename... T_Components>
        void setComponents(uint64_t pos,
                           T_FirstComponent&& firstComponent,
                           T_Components&&... components);

        template <typename T_Component>
        void setComponents(uint64_t pos, T_Component&& component);


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
                                   std::unordered_map<CId, uint64_t>& nIterations,
                                   uint64_t& maxIterations);

        template <typename T_Component>
        inline static bool iterate(std::vector<T_Component>& vector,
                                   CIter<T_Component>& iter,
                                   std::unordered_map<CId, uint64_t>& nIterations,
                                   uint64_t& maxIterations);
    };


    #include "BasicScene.tcc"


}   //  namespace fug


#endif // FUG_BASIC_SCENE_HPP
