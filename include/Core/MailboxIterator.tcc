
template <typename T_Event>
MailboxIterator<T_Event>::MailboxIterator(const std::vector<Event<T_Event>>* vec,
                                          EventPort const& port,
                                          MailboxSize_t first_index,
                                          MailboxSize_t last_index,
                                          MailboxSize_t start_index) :
    _vec(vec), _port(port), _first(first_index), _last(last_index), _index(start_index)
{}

template <typename T_Event>
MailboxIterator<T_Event>& MailboxIterator<T_Event>::operator++()
{
    if (_index == _last) {
        _index = _first;
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
    if (_index == _first) {
        _index = _last;
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
    return other._index == _index && other._port == _port;
}

template <typename T_Event>
bool MailboxIterator<T_Event>::operator!=(MailboxIterator const& other)
{
    return other._index != _index || other._port != _port;
}

template <typename T_Event>
Event<T_Event> const& MailboxIterator<T_Event>::operator*() const
{
    return (*_vec)[_index];
}

template <typename T_Event>
const Event<T_Event>* MailboxIterator<T_Event>::operator->() const
{
    return &(*_vec)[_index];
}

#ifdef FUG_DEBUG

#include "Utility.hpp"

template <typename T_Event>
std::ostream& operator<<(std::ostream& os, MailboxIterator<T_Event> const& it)
{
    os << util::str(it) << " (port " << it._port << ") with"
       << " index " << it._index
       << ", bounds [" << it._first << " " << it._last << "]";
    return os;
}
#endif
