#ifndef FUG_EVENT_HPP
#define FUG_EVENT_HPP

#include "EventInfo.hpp"
#include "Utility.hpp"
#include <iostream>

namespace fug {

	template <typename T_Event>	
	class Event {
	
	public:
		Event(T_Event const& = T_Event(), EventPort const& = EventPort());

		T_Event data;
		EventInfo info;

	private:
		static EventId _id;

		#ifdef FUG_DEBUG
		template <typename U_Event>
		friend std::ostream& operator<<(std::ostream&, Event<U_Event> const&);
		#endif

	};
	#include "Event.tcc"

} // namespace fug

#endif // FUG_EVENT_HPP 
