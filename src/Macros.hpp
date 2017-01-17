#ifndef FUG_MACROS_HPP
#define FUG_MACROS_HPP


//  Development macros
#define FUG_DEV
#define FUG_DEBUG

//  Undefin
#define FUG_UNIT_TEST 2


//  Convenience macros
#define FUG_SCENE               fug::Scene::instance()
#define FUG_EVENT_MANAGER       fug::EventManager::instance()
#define FUG_RESOURCE_MANAGER    fug::ResourceManager::instance()


#endif // FUG_MACROS_HPP
