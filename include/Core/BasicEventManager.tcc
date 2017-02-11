#ifdef FUG_DEBUG
#undef FUG_MAILBOX_SIZE
#define FUG_MAILBOX_SIZE 5
#endif

template <typename T_Event>
Mailbox<T_Event> BasicEventManager::getMailbox(EventPort const& port) 
{
	auto& state = getMailboxState<T_Event>(port);
    return Mailbox<T_Event>(state.begin_iter, state.end_iter);
}

template <typename T_Event>
void BasicEventManager::pushEvent(T_Event const& payload, EventPort const& port) 
{
	Event<T_Event> event(payload, port);

	#ifdef FUG_DEBUG
	std::cout << "* Pushing " << event << std::endl;
	#endif

	auto& state = getMailboxState<T_Event>(port);
	getEventVector<T_Event>().at(state.end_iter++._index) = event;

	// if ring buffer's head overlaps with the tail, pad the tail forward
	if (state.begin_iter._index == state.end_iter._index) {
		state.begin_iter++;
	}
}

template <typename T_Event>
void BasicEventManager::flushEvents(EventPort const& port)
{
	auto& state = getMailboxState<T_Event>(port);
	
    state.begin_iter._index = state.start;
    state.end_iter._index = state.start;

	#ifdef FUG_DEBUG
	std::cout << "* Mailbox (" << util::str(Event<T_Event>()) << ", port " << port << ") flushed" << std::endl;
	#endif

}

template <typename T_Event>
std::vector<Event<T_Event>>& BasicEventManager::getEventVector()
{	
	static std::vector<Event<T_Event>> v;
	return v;	
}

template <typename T_Event>
auto BasicEventManager::accessMailboxStates() -> std::unordered_map<EventPort, MailboxState<T_Event>>& 
{
	static std::unordered_map<EventPort, MailboxState<T_Event>> states;
	return states;
}

template <typename T_Event>
auto BasicEventManager::getMailboxState(EventPort const& port) -> MailboxState<T_Event>& 
{
    auto& states =  accessMailboxStates<T_Event>();
    auto iter = states.find(port);
    
    if (iter == states.end()) {
        
        // Here we can assume the port is new for T_Event
        // Port's buffer needs to be allocated and MailboxState needs to be initialized:

        auto& vec = getEventVector<T_Event>();
        vec.resize(vec.size() + FUG_MAILBOX_SIZE);
        
        MailboxSize_t first_index = vec.size() - FUG_MAILBOX_SIZE;
        MailboxSize_t last_index = vec.size() - 1;

        auto buckets = states.bucket_count();
        iter = states.insert({port, {port,
                                     first_index,
                                     last_index,
                                     MailboxIterator<T_Event>(&vec, port, first_index, last_index, first_index),
                                     MailboxIterator<T_Event>(&vec, port, first_index, last_index, first_index)}}).first;
    }

	return iter->second;
}

template <typename T_Event>
void BasicEventManager::registerMailbox(Mailbox<T_Event>* mailbox)
{
    // Not implemented
}


template <typename T_Event>
void BasicEventManager::unRegisterMailbox(Mailbox<T_Event>* mailbox)
{
    // Not implemented
}
