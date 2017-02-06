#include "Test/UnitTests.hpp"

#include "Core/EventManager.hpp"
#include "Core/Utility.hpp"

#include <sstream>

struct CustomEventType {
    std::string someMessage;
    unsigned someRevision;
};

FUG_UNIT_TEST(eventTest) {
    using namespace fug;
    std::stringstream ss("");

	{
		FUG_TEST_CASE("flushing new mailbox")
		FUG_EVENT_MANAGER.flushEvents<CustomEventType>();

		FUG_TEST_CASE("pushing to new mailbox")
		FUG_EVENT_MANAGER.pushEvent(CustomEventType());
	}

	{
        FUG_TEST_CASE("pushing to new specific port");
        std::string strs[] = {"Hello", " I'm ", "Mailbox"};
        for (auto s : strs) {
            FUG_EVENT_MANAGER.pushEvent(s, 123);
        }

		FUG_TEST_CASE("getMailbox")
		auto mailbox = FUG_EVENT_MANAGER.getMailbox<std::string>(123);

		FUG_TEST_CASE("Mailbox")
		auto mailbox2(mailbox);
		auto mailbox3 = mailbox2;
		auto mailbox4 = std::move(mailbox2);
		auto mailbox5(std::move(mailbox4));

        FUG_TEST_CASE("begin- and end-iterators");
        auto begin = mailbox.begin();
        auto end = mailbox.end();
        std::cout << " -> " << begin << std::endl
                  << " -> " << end << std::endl;

        FUG_TEST_CASE("forward iteration");
        while (begin != end) { ss << (begin++)->data; }
        FUG_TEST(ss.str() == "Hello I'm Mailbox");
        ss.str("");

        FUG_TEST_CASE("backward iteration");
        do { ss << (--end)->data; } while (begin != end);
        FUG_TEST(ss.str() == "Mailbox I'm Hello");
        ss.str("");

        FUG_TEST_CASE("flush");
        FUG_EVENT_MANAGER.flushEvents<std::string>(123);
        for (auto& ev : FUG_EVENT_MANAGER.getMailbox<std::string>(123)) {
            ss << ev.data;
        }
        FUG_TEST(ss.str() == "");
	}

	{    
        FUG_TEST_CASE("another port with same type - overflowing the mailbox");
        std::string strs[] =
            {"WRONG", "WRONG", "WRONG", "WRONG", "WRONG", "WRONG", "WRONG",
             "I'm", " The", " Second ", "Mailbox"};

        for (auto s : strs) {
            FUG_EVENT_MANAGER.pushEvent(s, 777);
        }

        FUG_TEST_CASE("begin- and end-iterators");
        auto mailbox = FUG_EVENT_MANAGER.getMailbox<std::string>(777);
        auto begin = mailbox.begin();
        auto end = mailbox.end();
        std::cout << " -> " << begin << std::endl
                  << " -> " << end << std::endl;

        for (auto& ev : FUG_EVENT_MANAGER.getMailbox<std::string>(777)) {
            ss << ev.data;
        }
        FUG_TEST(ss.str() == "I'm The Second Mailbox");
        ss.str("");

        FUG_TEST_CASE("flush");
        FUG_EVENT_MANAGER.flushEvents<std::string>(777);
        for (auto& ev : FUG_EVENT_MANAGER.getMailbox<std::string>(777)) {
            ss << ev.data;
        }
        FUG_TEST(ss.str() == "");

        auto iter = FUG_EVENT_MANAGER.getMailbox<std::string>(777).end();

        FUG_TEST_CASE("accessing");
        FUG_TEST(iter->data != "");

        FUG_TEST_CASE("dereferencing");
        FUG_TEST((*iter).data != "");
    }

}

