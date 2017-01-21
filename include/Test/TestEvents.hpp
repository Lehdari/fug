#ifndef FUG_TEST_EVENTS_HPP
#define FUG_TEST_EVENTS_HPP

#include "Core/Event.hpp"

#include <string>

namespace fug {

	struct CustomEventType {
		std::string someMessage;
		unsigned someRevision;
	};

	#define TestEvent1 Event<uint64_t>
	#define TestEvent2 Event<std::string>
	#define TestEvent3 Event<CustomEventType>
	

} // namespace fug

#endif // FUG_TEST_EVENTS_HPP
