//
// Created by Lehdari on 8.1.2019.
//

#ifndef ECSTESTGAME_EVENTTYPEID_HPP
#define ECSTESTGAME_EVENTTYPEID_HPP


#include <cstdint>


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
