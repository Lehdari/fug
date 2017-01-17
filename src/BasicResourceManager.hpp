#ifndef FUG_BASIC_RESOURCE_MANAGER_HPP
#define FUG_BASIC_RESOURCE_MANAGER_HPP


#include "ResourceManager.hpp"


namespace fug {

    class BasicResourceManager : public EventManagerBase<BasicResourceManager> {
    };


    #include "BasicResourceManager.tcc"

}


#endif // FUG_BASIC_RESOURCE_MANAGER_HPP

