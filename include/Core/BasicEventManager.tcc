#ifdef FUG_DEBUG
#undef FUG_MAILBOX_SIZE
#define FUG_MAILBOX_SIZE 5
#endif

template <typename T_Event>
Mailbox<T_Event> BasicEventManager::getMailbox(EventPort const& port) 
{
	auto& infos = getMailboxInfos<T_Event>();
	auto& vec = getEventVector<T_Event>(port);
	MailboxIterator<T_Event> begin, end;
	
	if (infos.find(port) == infos.end()) {
		// new port, allocate space and set initial info
		vec.resize(vec.size() + FUG_MAILBOX_SIZE);
		infos[port] = {port,
					   MailboxSize_t(vec.size() - FUG_MAILBOX_SIZE), 
					   MailboxSize_t(vec.size() - 1),
					   MailboxSize_t(vec.size() - FUG_MAILBOX_SIZE),
					   MailboxSize_t(vec.size() - FUG_MAILBOX_SIZE)};
	}

	auto& info = infos[port];
	begin._vec = &vec;
	begin._info = info;
	begin._index = info.tail;
	end._vec = &vec;
	end._info = info;
	end._index = info.head;

	return Mailbox<T_Event>(begin, end);
}

template <typename T_Event>
void BasicEventManager::pushEvent(T_Event const& payload, EventPort const& port) 
{
	Event<T_Event> event(payload, port);

	#ifdef FUG_DEBUG
	std::cout << "* Pushing " << event << std::endl;
	#endif

	auto mailbox = getMailbox<T_Event>(port);
	auto begin = mailbox.begin();
	auto end = mailbox.end();

	getEventVector<T_Event>(port).at(end._index) = event;

	auto headIndex = (++end)._index;
	auto tailIndex = begin._index;
	
	auto& info = getMailboxInfos<T_Event>()[port];
	info.head = headIndex;

	// if ring buffer's head overlaps with the tail, pad the tail forward
	if (headIndex == tailIndex) {
		++begin;
		tailIndex = begin._index;
		info.tail = tailIndex;
	}

	#ifdef FUG_DEBUG
	std::cout << "* Mailbox head: " << getMailbox<T_Event>(port).end() << std::endl;
	#endif
}

template <typename T_Event>
void BasicEventManager::flushEvents(EventPort const& port)
{
	auto& infos = getMailboxInfos<T_Event>();
	if (infos.find(port) == infos.end()) {
		// Nonextistent mailbox cannot be flushed
		return;
	}
	auto& info = infos.at(port);
	info.head = info.start;
	info.tail = info.start;

	#ifdef FUG_DEBUG
	std::cout << "* Mailbox (" << util::str(Event<T_Event>()) << ", port " << port << ") flushed" << std::endl;
	#endif

}

template <typename T_Event>
std::vector<Event<T_Event>>& BasicEventManager::getEventVector(EventPort const& port)
{	
	static std::vector<Event<T_Event>> v;
	return v;	
}

template <typename T_Event>
std::unordered_map<EventPort, std::vector<Mailbox<T_Event>*>>& BasicEventManager::getMailboxPointers()
{
	static std::unordered_map<EventPort, std::vector<Mailbox<T_Event>*>> index;
	return index;
}

template <typename T_Event>
std::unordered_map<EventPort, MailboxInfo>& BasicEventManager::getMailboxInfos()
{
	static std::unordered_map<EventPort, MailboxInfo> infos;
	return infos;
}


template <typename T_Event>
void BasicEventManager::registerMailbox(Mailbox<T_Event>* mailbox)
{
	/* TODO
	#ifdef FUG_DEBUG
	std::cout << ">> " << util::str(*mailbox) << " registered" << std::endl;
	#endif
	*/
}


template <typename T_Event>
void BasicEventManager::unRegisterMailbox(Mailbox<T_Event>* mailbox)
{
	/* TODO
	#ifdef FUG_DEBUG
	//std::cout << "<< " << util::str(*mailbox) << " unregistered" << std::endl;
	#endif
	*/
}
