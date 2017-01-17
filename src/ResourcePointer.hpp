#ifndef FUG_RESOURCE_POINTER_HPP
#define FUG_RESOURCE_POINTER_HPP


#include <functional>

#include "Types.hpp"
#include "Implementation.hpp"


namespace fug {

    template <typename T_Resource>
    class ResourcePointer {
        public:
        ResourcePointer(void);
        ResourcePointer(T_Resource* resource,
                        const RId& resourceId,
                        int* referenceCount);
        ResourcePointer(const ResourcePointer<T_Resource>& resourcePointer);
        ResourcePointer(ResourcePointer<T_Resource>&& resourcePointer);
        ~ResourcePointer(void);

        ResourcePointer<T_Resource>& operator=(const ResourcePointer<T_Resource>& resourcePointer);
        ResourcePointer<T_Resource>& operator=(ResourcePointer<T_Resource>&& resourcePointer);

        T_Resource& operator*(void);
        const T_Resource& operator*(void) const;
        T_Resource* operator->(void);
        const T_Resource* operator->(void) const;

        //  get resource pointer
        T_Resource* get(void);
        //  get resource id
        const RId& getId(void);

    private:
        T_Resource* _resource;
        RId         _resourceId;
        int*        _referenceCount;

        static std::function<void(ResourcePointer<T_Resource>&)>    _outOfReferences;
    };


    #include "ResourcePointer.tcc"

}


#endif // FUG_RESOURCE_POINTER_HPP
