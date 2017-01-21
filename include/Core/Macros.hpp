#ifndef FUG_MACROS_HPP
#define FUG_MACROS_HPP


//  Development macros
#define FUG_DEV
#define FUG_DEBUG

//  Unit test to use, 0 for no unit test
#define FUG_UNIT_TEST 0


//  Convenience macros
#define FUG_SCENE               fug::Scene::instance()
#define FUG_EVENT_MANAGER       fug::EventManager::instance()
#define FUG_RESOURCE_MANAGER    fug::ResourceManager::instance()


#endif // FUG_MACROS_HPP
