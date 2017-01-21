
template <typename T_Event>
EventId Event<T_Event>::_id = EventId();

template <typename T_Event>
Event<T_Event>::Event(T_Event const& payload, EventPort port) : 
	data(payload), info({++_id, port, false})
{}

