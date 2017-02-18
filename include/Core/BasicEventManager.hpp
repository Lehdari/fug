#ifndef FUG_BASIC_EVENT_MANAGER_HPP
#define FUG_BASIC_EVENT_MANAGER_HPP

#ifdef FUG_DEBUG
#include "Utility.hpp"
#define FUG_MAILBOX_SIZE 5
#else
#define FUG_MAILBOX_SIZE 1024
#endif

#include <unordered_map>
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
	};


	public:
		BasicEventManager() {}

		template <typename T_Event>
		Mailbox<T_Event> getMailbox(EventPort const& = EventPort());

		template <typename T_Event>
		void pushEvent(T_Event const&, EventPort const& = EventPort(), bool = false);

		template <typename T_Event>
		void flushEvents(EventPort const& = EventPort());

	private:

		template <typename T_Event>
		std::vector<Event<T_Event>>& getEventVector();

		template <typename T_Event>
		std::unordered_map<EventPort, MailboxState<T_Event>>& accessMailboxStates();

		template <typename T_Event>
		MailboxState<T_Event>& getMailboxState(EventPort const&);

		template <typename T_Event>
		void registerMailbox(Mailbox<T_Event>*);

		template <typename T_Event>
		void unRegisterMailbox(Mailbox<T_Event>*);

	};

    #include "BasicEventManager.tcc"

}


#endif // FUG_BASIC_EVENT_MANAGER_HPP
