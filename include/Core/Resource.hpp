#ifndef FUG_RESOURCE_HPP
#define FUG_RESOURCE_HPP

#include <vector>

//  macro for correct CRTP usage
#define FUG_RESOURCE(RESOURCE_TYPE)\
    RESOURCE_TYPE : public fug::Resource<RESOURCE_TYPE>

//  macro for resource init/destroy member functions (identical to every resource)
#define FUG_RESOURCE_INIT_DESTROY_DECL\
    template<typename T_ResourceInitInfo>\
    void init(const T_ResourceInitInfo& initInfo,\
              const std::vector<RId>& initResources,\
              const std::vector<RId>& depResources);\
template<typename T_ResourceInitInfo>\
    void destroy(void);\

//  macros for init/destroy implementations in resource initialization files
#define FUG_RESOURCE_INIT(RESOURCE_TYPE, RESOURCE_INIT_INFO_TYPE)\
    template<>\
    inline void fug::RESOURCE_TYPE::init<RESOURCE_INIT_INFO_TYPE>\
        (const RESOURCE_INIT_INFO_TYPE& initInfo,\
         const std::vector<RId>& initResources,\
         const std::vector<RId>& depResources)
#define FUG_RESOURCE_DESTROY(RESOURCE_TYPE, RESOURCE_INIT_INFO_TYPE)\
    template<>\
    inline void fug::RESOURCE_TYPE::destroy<RESOURCE_INIT_INFO_TYPE>(void)


#include "Types.hpp"


namespace fug {

    template<typename T_Resource>
    class Resource {
    public:
        Resource(void)                  = default;
        Resource(Resource&&)            = default;
        Resource& operator=(Resource&&) = default;
        virtual ~Resource(void)         = default;

        /// ResourceBase is uncopyable (why would you want to copy a resource anyway)
        Resource(const Resource&)               = delete;
        Resource& operator=(const Resource&)    = delete;

        template<typename T_ResourceInitInfo>
        void init(T_ResourceInitInfo initInfo,
                  std::vector<RId> initResources, // dependency res. vectors are copyed as value for parallellization purposes
                  std::vector<RId> depResources);

        template<typename T_ResourceInitInfo>
        void destroy(void);
    };


    #include "Resource.tcc"

};


#endif // FUG_RESOURCE_HPP
