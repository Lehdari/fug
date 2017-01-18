#ifndef FUG_RESOURCE_MANAGER_HPP
#define FUG_RESOURCE_MANAGER_HPP


#include <cstdio>
#include <vector>

#include "Implementation.hpp"
#include "Core/ResourcePointer.hpp"


namespace fug {

    template <typename T_Implementation>
    class ResourceManagerBase {
    public:
        template <typename T_Resource>
        friend class ResourcePointer;

        //  Get the singleton instance handle
        static ResourceManagerBase<T_Implementation>& instance(void);

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
        template <typename T_Resource>
        void registerPointer(ResourcePointer<T_Resource>* pointer);

        template <typename T_Resource>
        void unRegisterPointer(ResourcePointer<T_Resource>* pointer);
    };


    #include "ResourceManager.tcc"


    using ResourceManager = ResourceManagerBase<ResourceManagerImplementation>;


    template <typename T_Resource>
    std::function<void(ResourcePointer<T_Resource>*)>
        ResourcePointer<T_Resource>::_registerPointer
            = std::bind(&ResourceManager::registerPointer<T_Resource>,
                        &FUG_RESOURCE_MANAGER, std::placeholders::_1);

    template <typename T_Resource>
    std::function<void(ResourcePointer<T_Resource>*)>
        ResourcePointer<T_Resource>::_unRegisterPointer
            = std::bind(&ResourceManager::unRegisterPointer<T_Resource>,
                        &FUG_RESOURCE_MANAGER, std::placeholders::_1);

}

/// include implementation headers here
#include "Core/BasicResourceManager.hpp"


#endif // FUG_RESOURCE_MANAGER_HPP
