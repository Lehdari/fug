
#ifdef FUG_DEBUG
#include "Utility.hpp"
#endif

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

	begin._vec = &vec;
	begin._info = infos[port];
	begin._index = begin._info.head;
	end._vec = &vec;
	end._info = infos[port];
	end._index = begin._info.tail;

	return Mailbox<T_Event>(begin, end);
}

template <typename T_Event>
void BasicEventManager::pushEvent(Event<T_Event> const& event) 
{
	// TODO
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
	std::cout << ">> " << util::str(*mailbox) << " registered" << std::endl;
	#endif
}


template <typename T_Event>
void BasicEventManager::unRegisterMailbox(Mailbox<T_Event>* mailbox)
{
	//TODO
	#ifdef FUG_DEBUG
	std::cout << "<< " << util::str(*mailbox) << " unregistered" << std::endl;
	#endif
}
