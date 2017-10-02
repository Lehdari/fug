#ifndef FUG_MAILBOX_HPP
#define FUG_MAILBOX_HPP


#include <functional>

#include "Implementation.hpp"
#include "MailboxIterator.hpp"

namespace fug {

    template <typename T_Event>
    class Mailbox {
    
    public:
        friend class FUG_IMPLEMENTATION_EVENT_MANAGER;

        ~Mailbox();

        Mailbox(Mailbox const&);
        Mailbox(Mailbox<T_Event>&&);
        Mailbox<T_Event>& operator=(Mailbox<T_Event> const&);
        Mailbox<T_Event>& operator=(Mailbox<T_Event>&&);

        MailboxIterator<T_Event> const& begin();
        MailboxIterator<T_Event> const& end();

    private:
        Mailbox() = delete;
        Mailbox(MailboxIterator<T_Event> const&, MailboxIterator<T_Event> const&);

        const MailboxIterator<T_Event>* _begin;
        const MailboxIterator<T_Event>* _end;

        EventPort _port;
        bool _handlerFlag;

        static std::function<void(Mailbox<T_Event>*)> _registerMailbox;
        static std::function<void(Mailbox<T_Event>*)> _unRegisterMailbox;
    };
    
    #include "Mailbox.tcc"

}


#endif // FUG_RESOURCE_POINTER_HPP
