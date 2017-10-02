#ifndef FUG_EVENT_INFO
#define FUG_EVENT_INFO

#include "Types.hpp"

namespace fug {

    // Metadata container for Event
    struct EventInfo {

        EventId id;
        EventPort port;

        bool persistent;
    };

} // namespace fug


#endif // FUG_EVENT_INFO
