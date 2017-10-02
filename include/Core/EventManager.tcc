
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
template <typename T_Event, typename T_Visitor, typename... T_Components>
Mailbox<T_Event> EventManagerBase<T_Implementation>::getHandlerMailbox(Visitor<T_Visitor, T_Components...> const& visitor)
{
    return static_cast<T_Implementation*>(this)-> template getHandlerMailbox<T_Event>(visitor);
}

template <typename T_Implementation>
template <typename T_Event>
void EventManagerBase<T_Implementation>::pushEvent(T_Event const& event, EventPort const& port, bool persistent) 
{
    static_cast<T_Implementation*>(this)->pushEvent(event, port, persistent);
}

template <typename T_Implementation>
template <typename T_Event>
void EventManagerBase<T_Implementation>::flushEvents(EventPort const& port)
{
    static_cast<T_Implementation*>(this)-> template flushEvents<T_Event>(port);
}

template <typename T_Implementation>
template <typename... T_Events, typename T_Visitor, typename... T_Components>
void EventManagerBase<T_Implementation>::registerHandler(Visitor<T_Visitor, T_Components...> const& visitor)
{
    static_cast<T_Implementation*>(this)-> template registerHandler<T_Events...>(visitor);
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


