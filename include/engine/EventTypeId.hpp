//
// Created by Lehdari on 8.1.2019.
//

#ifndef ECSTESTGAME_EVENTTYPEID_HPP
#define ECSTESTGAME_EVENTTYPEID_HPP


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


#endif //ECSTESTGAME_EVENTTYPEID_HPP
