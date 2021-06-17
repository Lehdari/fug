add_subdirectory(ecs)
set(ECS_SOURCES ${ECS_SOURCES} PARENT_SCOPE)

add_subdirectory(engine)
set(ENGINE_SOURCES ${ENGINE_SOURCES} PARENT_SCOPE)

add_subdirectory(graphics)
set(GRAPHICS_SOURCES ${GRAPHICS_SOURCES} PARENT_SCOPE)
