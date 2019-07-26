//
// Project: fug
// File: TypeId.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_UTILS_TYPEID_HPP
#define FUG_UTILS_TYPEID_HPP

#include <cstdint>
#include <type_traits>


FUG_COMPONENT_FORWARD_DECLARATIONS


namespace fug {

    class TypeId {
    private:
        template<typename T_Component>
        struct IdRegistered {
            static constexpr bool value = false;
        };

        template<typename... T_Components>
        struct TypeRegister {
        };

        template<typename T_Component>
        static constexpr int64_t typeIdPrivate(TypeRegister<>)
        {
            static_assert(IdRegistered<T_Component>::value, FUG_COMPONENT_TYPE_ERROR_MESSAGE);
            return -1;
        }

        template<typename T_Component, typename T_FirstComponent, typename... T_RestComponents>
        static constexpr int64_t typeIdPrivate(TypeRegister<T_FirstComponent, T_RestComponents...>)
        {
            if constexpr (std::is_same<T_FirstComponent, T_Component>::value)
                return 0;
            else
                return 1+typeIdPrivate<T_Component>(TypeRegister<T_RestComponents...>());
        }

        static constexpr TypeRegister<FUG_COMPONENT_TYPES> typeRegister = TypeRegister<FUG_COMPONENT_TYPES>();

    public:
        template<typename T_Component>
        static constexpr int64_t typeId()
        {
            return typeIdPrivate<T_Component>(TypeId::typeRegister);
        }
    };

} //namespace fug


#endif //FUG_UTILS_TYPEID_HPP
