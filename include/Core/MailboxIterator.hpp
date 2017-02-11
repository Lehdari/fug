#ifndef FUG_MAILBOX_ITERATOR_HPP
#define FUG_MAILBOX_ITERATOR_HPP

#include "Event.hpp"

#include <iostream>

namespace fug {
	
	template <typename T_Event>
	class MailboxIterator {

		friend class FUG_IMPLEMENTATION_EVENT_MANAGER;
	
		template <typename U_Event>
		friend class Mailbox;

	public:
		// incrementation
		MailboxIterator& operator++();
		MailboxIterator operator++(int);

		// decrementation
		MailboxIterator& operator--();
		MailboxIterator operator--(int);

		// (in)equality
		bool operator==(MailboxIterator const&);
		bool operator!=(MailboxIterator const&);

		// dereferencing
		Event<T_Event> const& operator*(void) const;

		// member access
		const Event<T_Event>* operator->(void) const;

	private:
		MailboxIterator() = delete;
        MailboxIterator(const std::vector<Event<T_Event>>*, EventPort const&, MailboxSize_t, MailboxSize_t, MailboxSize_t);
		
		const std::vector<Event<T_Event>>* _vec;
		EventPort _port;

		MailboxSize_t _first;
		MailboxSize_t _last;
		MailboxSize_t _index;

		#ifdef FUG_DEBUG
		template <typename U_Event>
		friend std::ostream& operator<<(std::ostream&, MailboxIterator<U_Event> const&);
		#endif
	};

	#include "MailboxIterator.tcc"

}

#endif
