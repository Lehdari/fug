#ifndef FUG_BASIC_RESOURCE_MANAGER_HPP
#define FUG_BASIC_RESOURCE_MANAGER_HPP


#include "ResourceManager.hpp"


namespace fug {

    class BasicResourceManager : public ResourceManagerBase<BasicResourceManager> {
    public:
        friend class ResourceManagerBase<BasicResourceManager>;

        template <typename T_InitInfo>
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
    };


    #include "BasicResourceManager.tcc"

}


#endif // FUG_BASIC_RESOURCE_MANAGER_HPP

