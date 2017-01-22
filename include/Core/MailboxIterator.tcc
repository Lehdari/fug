
template <typename T_Event>
MailboxIterator<T_Event>::MailboxIterator() :
	_vec(nullptr), _info({EventPort(),0,0,0,0}), _index(0)
{}

template <typename T_Event>
MailboxIterator<T_Event>& MailboxIterator<T_Event>::operator++()
{
	if (_index == _info.end) {
		_index = _info.start;
	}
	else {
		_index++;
	}
	return *this;
}

template <typename T_Event>
MailboxIterator<T_Event> MailboxIterator<T_Event>::operator++(int)
{
	auto ret = *this;
	++*this;
	return ret;
}

template <typename T_Event>
MailboxIterator<T_Event>& MailboxIterator<T_Event>::operator--()
{
	if (_index == _info.start) {
		_index = _info.end;
	}
	else {
		_index--;
	}
	return *this;
}

template <typename T_Event>
MailboxIterator<T_Event> MailboxIterator<T_Event>::operator--(int)
{
	auto ret = *this;
	--*this;
	return ret;
}

template <typename T_Event>
bool MailboxIterator<T_Event>::operator==(MailboxIterator const& other)
{
	return other._index == _index && other._info.port == _info.port;
}

template <typename T_Event>
bool MailboxIterator<T_Event>::operator!=(MailboxIterator const& other)
{
	return other._index != _index || other._info.port != _info.port;
}

template <typename T_Event>
Event<T_Event> const& MailboxIterator<T_Event>::operator*() const
{
	return (*_vec)[_index];
}

template <typename T_Event>
Event<T_Event>& MailboxIterator<T_Event>::operator*()
{
	return (*_vec)[_index];
}

template <typename T_Event>
const Event<T_Event>* MailboxIterator<T_Event>::operator->() const
{
	return &(*_vec)[_index];
}

template <typename T_Event>
Event<T_Event>* MailboxIterator<T_Event>::operator->() 
{
	return &(*_vec)[_index];
}

#ifdef FUG_DEBUG

#include "Utility.hpp"

template <typename T_Event>
std::ostream& operator<<(std::ostream& os, MailboxIterator<T_Event> const& it)
{
	os << util::str(it) << " (port " << it._info.port << ") with"
	   << " index " << it._index
	   << ", start " << it._info.start
	   << ", end " << it._info.end
	   << ", head " << it._info.head
	   << ", tail " << it._info.tail;
	return os;
}
#endif
