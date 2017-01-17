#ifndef FUG_RESOURCE_MANAGER_HPP
#define FUG_RESOURCE_MANAGER_HPP


#include "Implementation.hpp"


namespace fug {

    template <typename T_ResourceManagerImplementation>
    class ResourceManagerBase {
    };


    #include "ResourceManager.tcc"


    using ResourceManager = ResourceManagerBase<ResourceManagerImplementation>;

}

/// include implementation headers here
#include "BasicResourceManager.hpp"


#endif // FUG_RESOURCE_MANAGER_HPP
