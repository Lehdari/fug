
template <typename T_Event>
EventId Event<T_Event>::_id = EventId();

template <typename T_Event>
Event<T_Event>::Event(T_Event const& payload, EventPort port) : 
	data(payload), info({++_id, port, false})
{}

#ifdef FUG_DEBUG

template <typename T_Event>
std::ostream& operator<<(std::ostream& os, Event<T_Event> const& event)
{
	os << util::str(event) << " (port " << event.info.port << ")"
	   << " with ID " << event.info.id
	   << ", persistency " << event.info.persistent
	   << ", payload '";
	try {
		os << event.data;
	}
	catch (int e) {
		os << e << "( ??? )";
	}
	os << "'";

	return os;
}
#endif
