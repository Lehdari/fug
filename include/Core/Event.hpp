#ifndef FUG_EVENT_HPP
#define FUG_EVENT_HPP

#include "EventInfo.hpp"

namespace fug {

	template <typename T_Event>	
	class Event {
	
	public:
		Event(T_Event const& = T_Event(), EventPort = EventPort());

		T_Event data;
		EventInfo info;

	private:
		static EventId _id;

	};
	#include "Event.tcc"

} // namespace fug

#endif // FUG_EVENT_HPP 
