#ifndef FUG_MAILBOX_ITERATOR_HPP
#define FUG_MAILBOX_ITERATOR_HPP

#include "Event.hpp"
#include "Utility.hpp"

#include <iostream>

namespace fug {
	
	struct MailboxInfo {
		
		EventPort port;
		MailboxSize_t start;
		MailboxSize_t end;
		MailboxSize_t head;
		MailboxSize_t tail;
	};

	template <typename T_Event>
	class MailboxIterator {

		friend class FUG_IMPLEMENTATION_EVENT_MANAGER;
	
		template <typename U_Event>
		friend class Mailbox;

	public:
		// incrementation
		MailboxIterator operator++();

		// decrementation
		MailboxIterator operator--();

		// (in)equality
		bool operator==(MailboxIterator const&);
		bool operator!=(MailboxIterator const&);

		// dereferencing
		Event<T_Event> const& operator*(void) const;
		Event<T_Event>& operator*(void); 

		// member access
		const Event<T_Event>* operator->(void) const;
		Event<T_Event>* operator->(void);

	private:
		MailboxIterator();

		std::vector<Event<T_Event>>* _vec;

		MailboxInfo _info;
		MailboxSize_t _index;

		#ifdef FUG_DEBUG
		template <typename U_Event>
		friend std::ostream& operator<<(std::ostream&, MailboxIterator<U_Event> const&);
		#endif
	};

	#include "MailboxIterator.tcc"

}

#endif
