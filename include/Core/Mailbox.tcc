
template <typename T_Event>
Mailbox<T_Event>::Mailbox(MailboxIterator<T_Event> const& begin, MailboxIterator<T_Event> const& end) :
    _begin(&begin), _end(&end), _port(_begin->_port)
{
    _registerMailbox(this);
}

template <typename T_Event>
Mailbox<T_Event>::~Mailbox()
{
    _unRegisterMailbox(this);
}

template <typename T_Event>
Mailbox<T_Event>::Mailbox(Mailbox const& other) :
    _begin(other._begin), _end(other._end), _port(other._port)
{
    _registerMailbox(this);
}


template <typename T_Event>
Mailbox<T_Event>::Mailbox(Mailbox<T_Event>&& other) :
    _begin(other._begin), _end(other._end), _port(other._port)
{
    other._begin = nullptr;
    other._end = nullptr;
    _registerMailbox(this);
}

template <typename T_Event>
Mailbox<T_Event>& Mailbox<T_Event>::operator=(Mailbox<T_Event> const& other)
{
    _unRegisterMailbox(this);
    _begin = other._begin;
    _end = other._end;
    _registerMailbox(this);

    return *this;
}

template <typename T_Event>
Mailbox<T_Event>& Mailbox<T_Event>::operator=(Mailbox<T_Event>&& other)
{
    _unRegisterMailbox(this);
    _begin = other._begin;
    _end = other._end;
    _registerMailbox(this);
    other._begin = nullptr;
    other._end = nullptr;

    return *this;
}

template <typename T_Event>
MailboxIterator<T_Event> const& Mailbox<T_Event>::begin()
{
    return *_begin;
}

template <typename T_Event>
MailboxIterator<T_Event> const& Mailbox<T_Event>::end()
{
    return *_end;
}
