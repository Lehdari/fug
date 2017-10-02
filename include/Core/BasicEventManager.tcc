
template <typename T_Event>
Mailbox<T_Event> BasicEventManager::getMailbox(EventPort const& port) 
{
    auto& state = getMailboxState<T_Event>(port);
    if (port == _default_port && state.event_status != MailboxState<T_Event>::HandlerStatus::None &&
                                 state.event_status != MailboxState<T_Event>::HandlerStatus::Finished) {
        throw; // TODO_EXCEPTION, Can't get mailbox, handler not finished
    }
    return Mailbox<T_Event>(state.begin_iter, state.end_iter);
}

template <typename T_Event, typename T_Visitor, typename... T_Components>
Mailbox<T_Event> BasicEventManager::getHandlerMailbox(Visitor<T_Visitor, T_Components...> const& visitor)
{
    auto& domain = accessHandlerDomain<T_Visitor>();
    auto iter = std::find(domain.begin(), domain.end(), getEventTypeId<T_Event>());
    if (iter == domain.end()) {
        throw; // TODO_EXCEPTION, T_Event not registered, or belongs to someone else
    }
    auto& state = getMailboxState<T_Event>(_default_port);
    if (state.event_status != MailboxState<T_Event>::HandlerStatus::Waiting) {
       throw; // TODO_EXCEPTION, Events already handled, or Visitor not registered
    }
    state.event_status = MailboxState<T_Event>::HandlerStatus::Operating;
    auto mailbox = Mailbox<T_Event>(state.begin_iter, state.end_iter);
    mailbox._handlerFlag = true; // TODO assignment necessary?
    return mailbox;
}

template <typename T_Event>
void BasicEventManager::pushEvent(T_Event const& payload, EventPort const& port, bool persistent)
{
    Event<T_Event> event(payload, port, persistent);
    auto& state = getMailboxState<T_Event>(port);
    if (state.event_status != MailboxState<T_Event>::HandlerStatus::None &&
        state.event_status != MailboxState<T_Event>::HandlerStatus::Waiting) {
        FUG_LOG(LogLevel::Warn) << "Can't push " << event << "! Reason: Mailbox handler isn't waiting (status = " << int(state.event_status) << ")\n";
    }
    else {
        FUG_LOG(LogLevel::Info) << "* Pushing " << event << std::endl;

        getEventVector<T_Event>().at(state.end_iter++._index) = event;

        // if ring buffer's head overlaps with the tail, pad the tail forward
        if (state.begin_iter._index == state.end_iter._index) {
            state.begin_iter++;
        }
    }
}

template <typename T_Event>
void BasicEventManager::flushEvents(EventPort const& port)
{
    auto& state = getMailboxState<T_Event>(port);
    auto& vec = getEventVector<T_Event>();

    // loop through the events to check for persistent ones which won't be flushed
    auto old_begin = state.begin_iter;
    for (auto iter = old_begin; iter != state.end_iter; iter++) {
        if (iter->info.persistent) {
            vec.at(state.begin_iter++._index) = *iter;
        }
    }
    state.end_iter = state.begin_iter;
    state.begin_iter = old_begin;

    if (port == _default_port && state.event_status != MailboxState<T_Event>::HandlerStatus::None) {
        state.event_status = MailboxState<T_Event>::HandlerStatus::Waiting;
    }

    FUG_LOG(LogLevel::Info) << "* Mailbox (" << util::str(Event<T_Event>()) << ", port " << port << ") flushed" << std::endl;
}

template <typename... T_Events, typename T_Visitor, typename... T_Components>
void BasicEventManager::registerHandler(Visitor<T_Visitor, T_Components...> const& visitor)
{
    auto& domain = accessHandlerDomain<T_Visitor>();
    if (domain.size()) {
        throw; // TODO_EXCEPTION, can't register twice (for now)
    }
    domain = { registerHandlerEventType<T_Events>()... };

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
    auto& states = accessMailboxStates<T_Event>();
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
                                     MailboxIterator<T_Event>(&vec, port, first_index, last_index, first_index),
                                     MailboxState<T_Event>::HandlerStatus::None}}).first;
    }

    return iter->second;
}

template <typename T_Visitor>
std::vector<uint64_t>& BasicEventManager::accessHandlerDomain()
{
    static std::vector<uint64_t> v;
    return v;
}

template <typename T_Event>
uint16_t BasicEventManager::getEventTypeId()
{
    static uint16_t id = _event_type_id++;
    return id;
}

template <typename T_Event>
uint16_t BasicEventManager::registerHandlerEventType()
{
    // TODO compile-time checking, if possible
    static bool flag;
    if (flag) {
        throw; // TODO_EXCEPTION, type can be registered once, since it can belong to one handler only
    }
    flag = true;
    auto& state = getMailboxState<T_Event>(_default_port);
    state.event_status = MailboxState<T_Event>::HandlerStatus::Waiting;
    return getEventTypeId<T_Event>();
}

template <typename T_Event>
void BasicEventManager::registerMailbox(Mailbox<T_Event>* mailbox)
{
    // Not implemented
}


template <typename T_Event>
void BasicEventManager::unRegisterMailbox(Mailbox<T_Event>* mailbox)
{
    if (mailbox->_handlerFlag == true && mailbox->_port == _default_port) {
        auto& state = getMailboxState<T_Event>(_default_port);
        if (state.event_status == MailboxState<T_Event>::HandlerStatus::Operating) {
            state.event_status = MailboxState<T_Event>::HandlerStatus::Finished;
        }
    }
}
