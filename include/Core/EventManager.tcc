
template <typename T_Implementation>
EventManagerBase<T_Implementation>& EventManagerBase<T_Implementation>::instance(void)
{
	static T_Implementation manager;
	return manager;
}

template <typename T_Implementation>
template <typename T_Event>
Mailbox<T_Event> EventManagerBase<T_Implementation>::getMailbox(EventPort const& port) 
{
	return static_cast<T_Implementation*>(this)-> template getMailbox<T_Event>(port);
}

template <typename T_Implementation>
template <typename T_Event>
void EventManagerBase<T_Implementation>::pushEvent(T_Event const& event, EventPort const& port) 
{
	static_cast<T_Implementation*>(this)->pushEvent(event, port);
}

template <typename T_Implementation>
template <typename T_Event>
void EventManagerBase<T_Implementation>::flushEvents(EventPort const& port)
{
	static_cast<T_Implementation*>(this)-> template flushEvents<T_Event>(port);
}

template <typename T_Implementation>
template <typename T_Event>
void EventManagerBase<T_Implementation>::registerMailbox(Mailbox<T_Event>* mailbox)
{
	static_cast<T_Implementation*>(this)->registerMailbox(mailbox);
}

template <typename T_Implementation>
template <typename T_Event>
void EventManagerBase<T_Implementation>::unRegisterMailbox(Mailbox<T_Event>* mailbox)
{
	static_cast<T_Implementation*>(this)->unRegisterMailbox(mailbox);
}


