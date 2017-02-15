#include "Test/UnitTests.hpp"

#include "Test/TestEvents.hpp"
#include "Core/EventManager.hpp"
#include "Core/Utility.hpp"


FUG_UNIT_TEST(eventTest) {
    using namespace fug;

	std::cout << "Testing events\n\n";

	{
		FUG_TEST_CASE("flushing new mailbox")
		std::cout << "(should not be flushed)" << std::endl;
		FUG_EVENT_MANAGER.flushEvents<CustomEventType>();

		FUG_TEST_CASE("pushing to new mailbox")
		FUG_EVENT_MANAGER.pushEvent(CustomEventType());
	}

	{
		FUG_TEST_CASE("pushing to new specific port")
		FUG_EVENT_MANAGER.pushEvent(std::string("YAAAAAAAAAAAAAAAAARGH"), 123);

		FUG_TEST_CASE("getMailbox")
		auto mailbox = FUG_EVENT_MANAGER.getMailbox<std::string>(123);

		FUG_TEST_CASE("Mailbox")
		auto mailbox2(mailbox);
		auto mailbox3 = mailbox2;
		auto mailbox4 = std::move(mailbox2);
		auto mailbox5(std::move(mailbox4));


		FUG_TEST_CASE("begin, end");
		auto begin = mailbox.begin();
		auto end = mailbox.end();
		std::cout << " -> " << begin << std::endl
				  << " -> " << end << std::endl;

		FUG_TEST_CASE("iteration")
		for (; begin != end; ++begin) {
			std::cout << begin->data << "  ";
		}
		std::cout << std::endl;

		FUG_TEST_CASE("flush")
		FUG_EVENT_MANAGER.flushEvents<std::string>(123);
		mailbox = FUG_EVENT_MANAGER.getMailbox<std::string>(123);
		begin = mailbox.begin();
		end = mailbox.end();
		std::cout << "should be empty:" << std::endl;
		for (; begin != end; ++begin) {
			std::cout << begin->data << "  ";
		}
		std::cout << std::endl;
	}

	{
		FUG_TEST_CASE("filling a mailbox")
		for (uint64_t i = 1; i<11; i++) {
			FUG_EVENT_MANAGER.pushEvent(10*i, 123);
		}

		auto mailbox = FUG_EVENT_MANAGER.getMailbox<uint64_t>(123);

		auto begin = mailbox.begin();
		auto end = mailbox.end();
		std::cout << " -> " << begin << std::endl
				  << " -> " << end << std::endl;

		for (; begin != end; ++begin) {
			std::cout << begin->data << "  ";
		}
		std::cout << std::endl;

		FUG_TEST_CASE("flush")
		FUG_EVENT_MANAGER.flushEvents<uint64_t>(123);
		mailbox = FUG_EVENT_MANAGER.getMailbox<uint64_t>(123);
		begin = mailbox.begin();
		end = mailbox.end();
		std::cout << "should be empty:" << std::endl;
		for (; begin != end; ++begin) {
			std::cout << begin->data << "  ";
		}
		std::cout << std::endl;

		FUG_TEST_CASE("accessing")
		end->data = 123;
		FUG_TEST(end->data == 123UL);

		FUG_TEST_CASE("dereferencing")
		(*end).data = 321;
		FUG_TEST(end->data != 123UL);
    }

}

