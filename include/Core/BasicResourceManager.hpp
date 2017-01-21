#ifndef FUG_BASIC_RESOURCE_MANAGER_HPP
#define FUG_BASIC_RESOURCE_MANAGER_HPP


#include <memory>
#include <unordered_map>
#include <algorithm>

#include "Core/ResourceManager.hpp"


namespace fug {

    class BasicResourceManager : public ResourceManagerBase<BasicResourceManager> {
    public:
        friend class ResourceManagerBase<BasicResourceManager>;

        template <typename T_Resource, typename T_InitInfo>
        void addResourceInfo(const RId& resourceId,
                             const T_InitInfo& initInfo,
                             const std::vector<RId>& initResources = std::vector<RId>(),
                             const std::vector<RId>& depResources = std::vector<RId>(),
                             bool isGraphicsResource = false);

        //  Blocking command for getting given resource. Loads, if the resource doesn't exist
        template<typename T_Resource>
        ResourcePointer<T_Resource> getResource(const RId& resourceId);

        //  Asynchronous resource loading
        void loadResource(const RId& resourceId, bool waitForFinish = false);

    private:
        BasicResourceManager(void) {}

        struct ResourceInfo {
            uint64_t            typeId;

            void*               initInfo;
            uint64_t            initInfoLoc;        // index in the initInfos buffer, used initInfo vector gets reallocated

            void*               resource;
            uint64_t            resourceLoc;        // same thing as with the initInfoLoc

            std::vector<RId>    initResources;      // resources required when initializing
            std::vector<RId>    depResources;       // resources required for the whole lifetime

            void(BasicResourceManager::*init)(const RId&, ResourceInfo&);   //call to initResource member function, allows loadResource to be untemplated.
        };
        std::unordered_map<ResourceId, ResourceInfo>    _resourceInfos;


        template <typename T_Resource>
        void registerPointer(ResourcePointer<T_Resource>* pointer);

        template <typename T_Resource>
        void unRegisterPointer(ResourcePointer<T_Resource>* pointer);


        template <typename T_Resource, typename T_InitInfo>
        void initResource(const RId& resourceId, ResourceInfo& resourceInfo);


        template <typename T_InitInfo>
        std::vector<T_InitInfo>& accessInitInfos(void);

        template <typename T_Resource>  //  TODO replace with ObjectPool once implemented
        std::vector<T_Resource>& accessResources(void);


        template <typename T_Resource>
        std::vector<ResourcePointer<T_Resource>*>&
            accessResourcePointerPointers(const RId& resourceId);

        template <typename T_Resource>
        std::unordered_map<RId, std::vector<ResourcePointer<T_Resource>*>>&
            accessResourcePointerPointers(void);


        static uint64_t _resourceTypeId;

        template <typename T_Resource>
        static uint64_t getResourceTypeId(void);
    };


    #include "BasicResourceManager.tcc"

}


#endif // FUG_BASIC_RESOURCE_MANAGER_HPP

