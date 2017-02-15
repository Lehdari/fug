#include "Test/UnitTests.hpp"

#include <cstdio>

#include "Core/Scene.hpp"
#include "Test/TestVisitors.hpp"
#include "Test/TestComponents.hpp"

#include "Core/Binary.hpp"
#include "Core/Binary_Init_File.hpp"
#include "Core/ResourceManager.hpp"
#include "Core/ResourcePointer.hpp"
#include "Test/TestResources.hpp"
#include "Test/TestResources_Init.hpp"
#include "Test/TestEvents.hpp"
#include "Core/EventManager.hpp"
#include "Core/Utility.hpp"

// Graphics includes
#include "Graphics/Canvas_SFML.hpp"

#include "Graphics/ShaderObject.hpp"
#include "Graphics/ShaderObject_Init_Binary.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/ShaderProgram_Init_Default.hpp"

#include "Graphics/Texture.hpp"
#include "Graphics/Texture_Init_Binary.hpp"

fug::UnitTest::UnitTest(const std::string& testName,
                        fug::UnitTest::T_TestFunc testFunc) :
    _testFunc(testFunc),
    _testName(testName)
{
    FUG_TESTER.addTest(testName, *this);
}

void fug::UnitTest::operator()(void)
{
    _testFunc(*this);
}

void fug::UnitTest::fail(unsigned line, const std::string& msg) const
{
    fprintf(stderr, "Test: \"%s\" failed at: %u, with: \"%s\"\n",
            _testName.c_str(), line, msg.c_str());
    FUG_TESTER.fail();
}

void fug::Tester::addTest(const std::string& testName,
                          const fug::UnitTest& test)
{
    _testFuncs.insert(std::make_pair(testName, test));
}

void fug::Tester::run(std::pair<std::string, fug::UnitTest> test,
                      bool dieOnFail)
{
    /* TODO: Dont't print anything unless things fail */
    fprintf(stderr, "Running test: %s\n", test.first.c_str());
    _dieOnFail = dieOnFail;
    test.second();
}

void fug::Tester::run(bool dieOnFail)
{
    for (const auto& test: _testFuncs)
        run(test, dieOnFail);
}

void fug::Tester::run(const std::string& testName, bool dieOnFail)
{
    auto test = _testFuncs.find(testName);

    if (test == _testFuncs.end())
        fprintf(stderr, "Could not find test: \"%s\"\n", testName.c_str());
    else
        run(*test);
}

void fug::Tester::fail(void)
{
    if (_dieOnFail)
        throw;
}

FUG_UNIT_TEST(sceneTest) {
    using namespace fug;
    EId nid[10] = {0};
    uint64_t i = 0;

    TestComponent1 tc11; tc11.a = 3; tc11.b = 4;
    //TestComponent1 tc12; tc12.a = 5; tc12.b = 6;

    //nid[i++] = FUG_SCENE.addEntity();
    nid[i++] = FUG_SCENE.addEntity(TestComponent1(), TestComponent2(), TestComponent3());
    nid[i++] = FUG_SCENE.addEntity();
    nid[i++] = FUG_SCENE.addEntity(std::move(tc11), TestComponent2(), TestComponent3());
    nid[i++] = FUG_SCENE.addEntity(TestComponent1(), TestComponent3());
    nid[i++] = FUG_SCENE.addEntity(TestComponent1(), TestComponent2());

    FUG_SCENE.print();

    FUG_SCENE.removeEntity(nid[2]);

    FUG_SCENE.print();

    TestVisitor1 visitor1;
    TestVisitor2 visitor2;
    TestVisitor3 visitor3;

    printf("Visiting with TestVisitor1:\n");
    FUG_SCENE.accept(visitor1);
    printf("Visiting with TestVisitor2:\n");
    FUG_SCENE.accept(visitor2);
    printf("Visiting with TestVisitor3:\n");
    FUG_SCENE.accept(visitor3);


    FUG_SCENE.removeEntity(nid[2]);

    FUG_SCENE.print();
}

FUG_UNIT_TEST(resourceTest) {
    using namespace fug;
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (1, {1, 2}, {101, 102, 103});
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (2, {2, 3}, {111, 112, 113});
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (3, {3, 4}, {121, 122, 123});


    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource2, TestResource2_Init_TestResource1>
        (4, {4.5f, 5.5f}, {3});

    auto r1p1 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(3);

    //auto tr1Ptr2 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(1);
    //printf("get: %p\n", tr1Ptr2.get());

    //auto r2p1 = FUG_RESOURCE_MANAGER.getResource<TestResource2>(4);


/*
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (1, TestResource1_Init_Default());
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (2, TestResource1_Init_Default());
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (3, TestResource1_Init_Default());
    FUG_RESOURCE_MANAGER.addResourceInfo<TestResource1, TestResource1_Init_Default>
        (4, TestResource1_Init_Default());

    printf("Null initialization:\n");
    ResourcePointer<TestResource1>   resPtr1;
    ResourcePointer<TestResource1>   resPtr2;
    ResourcePointer<TestResource1>   resPtr3;
    ResourcePointer<TestResource1>   resPtr4;
    printf("More null initialization:\n");
    //ResourcePointer<TestResource1>   resPtr5;
    //ResourcePointer<TestResource1>   resPtr6;
    //ResourcePointer<TestResource1>   resPtr7;
    //ResourcePointer<TestResource1>   resPtr8;


    printf("Proper initialization:\n");
    auto resPtr9 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(1);
    auto resPtr10 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(2);
    auto resPtr11 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(3);
    auto resPtr12 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(4);
    printf("More proper initialization\n");
    auto resPtr13 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(1);
    auto resPtr14 = FUG_RESOURCE_MANAGER.getResource<TestResource1>(2);

    printf("Null to new:\n");
    auto resPtr17(resPtr1);
    auto resPtr18 = std::move(resPtr2);
    auto resPtr19 = resPtr3;
    auto resPtr20 = std::move(resPtr4);

    printf("Proper to new:\n");
    auto resPtr21(resPtr9);
    auto resPtr22(std::move(resPtr10));
    auto resPtr23 = resPtr11;
    auto resPtr24 = std::move(resPtr12);

    printf("Proper to proper:\n");
    resPtr21 = resPtr13;
    resPtr22 = resPtr14;
*/
}

FUG_UNIT_TEST(gfxResourceTest) {
    using namespace fug;
    // Assumes a test file
    fug::Canvas_SFML canvas;
    canvas.display();

    FUG_TEST_CASE("Binary");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
        (5, BinaryInitInfo_File{"../res/textures/test_purjo.glsl"});

#if 1
    auto srcResPtr = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
    //auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);

    printf("%s: get: %p\n", __func__, srcResPtr.get());
    printf("%s, resource pointer buffer: %p\n", __func__, srcResPtr->getBufferPtr());
    printf("%s\n", srcResPtr->getBufferPtr());
#endif

    FUG_TEST_CASE("ShaderObject");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderObject, ShaderObjectInitInfo_Binary>
        (6, ShaderObjectInitInfo_Binary{ShaderObjectInitInfo_Binary::SOURCE_GLSL,
                                        GL_FRAGMENT_SHADER}, {5}, {});
    auto srcResPtr1 = FUG_RESOURCE_MANAGER.getResource<Binary>(5);
    printf("%s: get: %p\n", __func__, srcResPtr1.get());

    FUG_TEST_CASE("ShaderProgram");
    FUG_RESOURCE_MANAGER.addResourceInfo<ShaderProgram, ShaderProgramInitInfo_Default>
        (7, ShaderProgramInitInfo_Default{}, {6}, {});

    FUG_TEST_CASE("Texture");
    FUG_RESOURCE_MANAGER.addResourceInfo<Binary, BinaryInitInfo_File>
        (8, BinaryInitInfo_File{"../res/textures/test_purjo.glsl"});
    FUG_RESOURCE_MANAGER.addResourceInfo<Texture, TextureInitInfo_Binary>
        (9, TextureInitInfo_Binary{TextureInitInfo_Binary::SOURCE_BINARY_PNG,
                                   0, 0, 0, 0}, {8}, {});
}


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

