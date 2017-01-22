#ifndef FUG_EVENT_MANAGER_HPP
#define FUG_EVENT_MANAGER_HPP

#include <vector>

#include "Implementation.hpp"
#include "Mailbox.hpp"


namespace fug {

    template <typename T_Implementation>
    class EventManagerBase {


	public:
		template <typename T_Event>
		friend class Mailbox;
		
		// Returns the (singleton) instance of this class
		static EventManagerBase<T_Implementation>& instance(void);

		// Returns a specific mailbox handle for type & port combination
		template <typename T_Event>
		Mailbox<T_Event> getMailbox(EventPort const& = EventPort());

		// Adds a Event to its specific mailbox
		template <typename T_Event>
		void pushEvent(T_Event const&, EventPort const& = EventPort());

		// Flushes a specific mailbox
		template <typename T_Event>
		void flushEvents(EventPort const& = EventPort());


	protected:
		EventManagerBase(void) {}

	private:
		template <typename T_Event>
		void registerMailbox(Mailbox<T_Event>*);
		
		template <typename T_Event>
		void unRegisterMailbox(Mailbox<T_Event>*);
	};
	
	#include "EventManager.tcc"

    using EventManager = EventManagerBase<EventManagerImplementation>;
    
	template <typename T_Event>
    std::function<void(Mailbox<T_Event>*)>
        Mailbox<T_Event>::_registerMailbox
            = std::bind(&EventManager::registerMailbox<T_Event>,
                        &FUG_EVENT_MANAGER, std::placeholders::_1);

	template <typename T_Event>
    std::function<void(Mailbox<T_Event>*)>
        Mailbox<T_Event>::_unRegisterMailbox
            = std::bind(&EventManager::unRegisterMailbox<T_Event>,
                        &FUG_EVENT_MANAGER, std::placeholders::_1);

}

// include implementation headers here
#include "BasicEventManager.hpp"


#endif // FUG_EVENT_MANAGER_HPP
