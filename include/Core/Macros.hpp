#ifndef FUG_MACROS_HPP
#define FUG_MACROS_HPP


//  Development macros
#define FUG_DEV
#define FUG_DEBUG

//  Convenience macros
#define FUG_SCENE               fug::Scene::instance()
#define FUG_EVENT_MANAGER       fug::EventManager::instance()
#define FUG_RESOURCE_MANAGER    fug::ResourceManager::instance()

//  Undef some idiotic windows-specific macros so they can be used as variables
#undef near
#undef far


#endif // FUG_MACROS_HPP
