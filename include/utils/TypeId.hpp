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
FUG_SINGLETON_FORWARD_DECLARATIONS


namespace fug {

    /// TypeId is class for generating integer IDs for given types.
    class TypeId {
    public:

        /// Component type IDs
        template<typename T_Type>
        static constexpr int64_t component()
        {
            return typeIdPrivate<T_Type>(TypeId::componentTypeRegister);
        }

        /// Singleton type IDs
        template<typename T_Type>
        static constexpr int64_t singleton()
        {
            return typeIdPrivate<T_Type>(TypeId::singletonTypeRegister);
        }

    private:
        template<typename T_Types>
        struct IdRegistered {
            static constexpr bool value = false;
        };

        template<typename... T_Types>
        struct TypeRegister {
        };

        template<typename T_Type>
        static constexpr int64_t typeIdPrivate(TypeRegister<>)
        {
            static_assert(IdRegistered<T_Type>::value, FUG_TYPE_ID_ERROR_MESSAGE);
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

        static constexpr TypeRegister<FUG_COMPONENT_TYPES>
            componentTypeRegister = TypeRegister<FUG_COMPONENT_TYPES>();
        static constexpr TypeRegister<FUG_SINGLETON_TYPES>
            singletonTypeRegister = TypeRegister<FUG_SINGLETON_TYPES>();
    };

} //namespace fug


#endif //FUG_UTILS_TYPEID_HPP
