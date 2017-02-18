
template <typename T_Event>
EventId Event<T_Event>::_id = EventId();

template <typename T_Event>
Event<T_Event>::Event(T_Event const& payload, EventPort const& port, bool persistency) :
	data(payload), info({++_id, port, persistency})
{}

#ifdef FUG_DEBUG

template <typename T_Event>
std::ostream& operator<<(std::ostream& os, Event<T_Event> const& event)
{
	os << util::str(event) << " (port " << event.info.port << ")"
	   << " with ID " << event.info.id
	   << ", persistency " << event.info.persistent;
	
	return os;
}
#endif
