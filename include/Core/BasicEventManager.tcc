

template <typename T_Event>
Mailbox<T_Event> BasicEventManager::getMailbox(EventPort const& port) 
{
	auto& infos = getMailboxInfos<T_Event>();
	auto& vec = getEventVector<T_Event>(port);
	MailboxIterator<T_Event> begin, end;
	
	if (infos.find(port) == infos.end()) {
		// new port, allocate space
		vec.resize(vec.size() + FUG_MAILBOX_SIZE);
		infos[port] = {port,
					   MailboxSize_t(vec.size() - FUG_MAILBOX_SIZE), 
					   MailboxSize_t(vec.size() - 1),
					   MailboxSize_t(vec.size() - FUG_MAILBOX_SIZE),
					   MailboxSize_t(vec.size() - FUG_MAILBOX_SIZE)};
	}

	auto info = infos[port];
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

	++end;
	auto headIndex = end._index;
	auto tailIndex = begin._index;

	getEventVector<T_Event>(port).at(headIndex) = event;

	auto& info = getMailboxInfos<T_Event>().at(port);
	info.head = headIndex;

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
	// TODO
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
	// TODO
	#ifdef FUG_DEBUG
	//std::cout << ">> " << util::str(*mailbox) << " registered" << std::endl;
	#endif
}


template <typename T_Event>
void BasicEventManager::unRegisterMailbox(Mailbox<T_Event>* mailbox)
{
	//TODO
	#ifdef FUG_DEBUG
	//std::cout << "<< " << util::str(*mailbox) << " unregistered" << std::endl;
	#endif
}
