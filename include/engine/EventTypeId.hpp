//
// Project: fug
// File: EventTypeId.hpp
//
// Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
// You may use, distribute and modify this code under the terms
// of the licence specified in file LICENSE which is distributed
// with this source code package.
//

#ifndef FUG_ENGINE_EVENTTYPEID_HPP
#define FUG_ENGINE_EVENTTYPEID_HPP


#include <cstdint>


/// Use this in component header files
#define DECLARE_EVENT_TEMPLATES(EVENT_TYPE)\
    extern template int64_t EventTypeId::typeId<EVENT_TYPE>();

/// Use this in component source files
#define DEFINE_EVENT_TEMPLATES(EVENT_TYPE)\
    template int64_t EventTypeId::typeId<EVENT_TYPE>();


class EventTypeId {
public:
    template <typename T_EventType>
    static int64_t typeId(void);

private:
    static int64_t __typeIdCounter;
};


template<typename T_EventType>
int64_t EventTypeId::typeId(void)
{
    static int64_t typeId = __typeIdCounter++;
    return typeId;
}


#endif //FUG_ENGINE_EVENTTYPEID_HPP
