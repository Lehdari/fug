add_subdirectory(assets)
set(ASSETS_SOURCES ${ASSETS_SOURCES} PARENT_SCOPE)

add_subdirectory(ecs)
set(ECS_SOURCES ${ECS_SOURCES} PARENT_SCOPE)

add_subdirectory(engine)
set(ENGINE_SOURCES ${ENGINE_SOURCES} PARENT_SCOPE)
