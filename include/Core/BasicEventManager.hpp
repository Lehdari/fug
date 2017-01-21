#ifndef FUG_BASIC_EVENT_MANAGER_HPP
#define FUG_BASIC_EVENT_MANAGER_HPP

#include <unordered_map>

#include "EventManager.hpp"

namespace fug {

	// Basic EventManager CRTP implementation
    class BasicEventManager : public EventManagerBase<BasicEventManager> {

	friend class EventManagerBase<BasicEventManager>;	

	public:
		BasicEventManager() {}

		template <typename T_Event>
		Mailbox<T_Event> getMailbox(EventPort const& = EventPort());

		template <typename T_Event>
		void pushEvent(Event<T_Event> const&);

		template <typename T_Event>
		void flushEvents(EventPort const& = EventPort());

	private:

		template <typename T_Event>
		std::vector<Event<T_Event>>& getEventVector(EventPort const&);

		template <typename T_Event>
		std::unordered_map<EventPort, std::vector<Mailbox<T_Event>*>>& getMailboxPointers();
	
		template <typename T_Event>
		std::unordered_map<EventPort, MailboxInfo>& getMailboxInfos();

		template <typename T_Event>
		void registerMailbox(Mailbox<T_Event>*);

		template <typename T_Event>
		void unRegisterMailbox(Mailbox<T_Event>*);

	};

    #include "BasicEventManager.tcc"

}


#endif // FUG_BASIC_EVENT_MANAGER_HPP
