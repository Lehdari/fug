#ifndef FUG_RESOURCE_MANAGER_HPP
#define FUG_RESOURCE_MANAGER_HPP


#include <vector>

#include "Implementation.hpp"
#include "ResourcePointer.hpp"


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
        void pointerOutOfReferences(ResourcePointer<T_Resource>& pointer);
        //void pointerOutOfReferences(void);
    };


    #include "ResourceManager.tcc"


    using ResourceManager = ResourceManagerBase<ResourceManagerImplementation>;

/*
    template <typename T_Resource>
    std::function<void(ResourcePointer<T_Resource>&)>
        ResourcePointer<T_Resource>::_outOfReferences(
            &ResourceManager::pointerOutOfReferences<T_Resource>);
*/
    template <typename T_Resource>
    std::function<void(ResourcePointer<T_Resource>&)>
        ResourcePointer<T_Resource>::_outOfReferences
            = std::bind(&ResourceManager::pointerOutOfReferences<T_Resource>,
                        &FUG_RESOURCE_MANAGER, std::placeholders::_1);

}

/// include implementation headers here
#include "BasicResourceManager.hpp"


#endif // FUG_RESOURCE_MANAGER_HPP
