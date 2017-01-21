
template <typename T_Event>
Mailbox<T_Event>::Mailbox(MailboxIterator<T_Event> begin, MailboxIterator<T_Event> end) :
	_begin(begin), _end(end)
{
	_registerMailbox(this);
}

template <typename T_Event>
Mailbox<T_Event>::~Mailbox() {
	_unRegisterMailbox(this);
}

template <typename T_Event>
Mailbox<T_Event>::Mailbox(Mailbox<T_Event>&& other) :
	_begin(other._begin), _end(other._end)
{
	_registerMailbox(this);
}

template <typename T_Event>
MailboxIterator<T_Event> const& Mailbox<T_Event>::begin()
{
	return _begin;
}

template <typename T_Event>
MailboxIterator<T_Event> const& Mailbox<T_Event>::end()
{
	return _end;
}
