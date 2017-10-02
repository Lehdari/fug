#ifndef FUG_BASIC_EVENT_MANAGER_HPP
#define FUG_BASIC_EVENT_MANAGER_HPP

#ifdef FUG_DEBUG
#include "Utility.hpp"
#define FUG_MAILBOX_SIZE 11
#else
#define FUG_MAILBOX_SIZE 1024
#endif

#include <unordered_map>

#include "Core/Log.hpp"
#include "Core/Visitor.hpp"
#include "EventManager.hpp"


namespace fug {

    // Basic EventManager CRTP implementation
    class BasicEventManager : public EventManagerBase<BasicEventManager> {

    friend class EventManagerBase<BasicEventManager>;

    template <typename T_Event>
    struct MailboxState {
        
        EventPort port;
        MailboxSize_t start;
        MailboxSize_t end;

        MailboxIterator<T_Event> begin_iter;
        MailboxIterator<T_Event> end_iter;

        enum class HandlerStatus {
            None,
            Waiting,
            Operating,
            Finished,
        } event_status;
    };

    public:
        BasicEventManager() : _event_type_id(0), _default_port() {}

        template <typename T_Event>
        Mailbox<T_Event> getMailbox(EventPort const&);

        template <typename T_Event, typename T_Visitor, typename... T_Components>
        Mailbox<T_Event> getHandlerMailbox(Visitor<T_Visitor, T_Components...> const&);

        template <typename T_Event>
        void pushEvent(T_Event const&, EventPort const&, bool);

        template <typename T_Event>
        void flushEvents(EventPort const&);

        template <typename... T_Events, typename T_Visitor, typename... T_Components>
        void registerHandler(Visitor<T_Visitor, T_Components...> const&);

    private:

        template <typename T_Event>
        std::vector<Event<T_Event>>& getEventVector();

        template <typename T_Event>
        std::unordered_map<EventPort, MailboxState<T_Event>>& accessMailboxStates();

        template <typename T_Event>
        MailboxState<T_Event>& getMailboxState(EventPort const&);

        template <typename T_Visitor>
        std::vector<uint64_t>& accessHandlerDomain();

        template <typename T_Event>
        uint16_t getEventTypeId();

        template <typename T_Event>
        uint16_t registerHandlerEventType();

        template <typename T_Event>
        void registerMailbox(Mailbox<T_Event>*);

        template <typename T_Event>
        void unRegisterMailbox(Mailbox<T_Event>*);

        uint16_t _event_type_id;
        EventPort _default_port;
    };

    #include "BasicEventManager.tcc"

}


#endif // FUG_BASIC_EVENT_MANAGER_HPP
