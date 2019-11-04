add_subdirectory(ecs)
set(ECS_HEADERS ${ECS_HEADERS} PARENT_SCOPE)

add_subdirectory(engine)
set(ENGINE_HEADERS ${ENGINE_HEADERS} PARENT_SCOPE)

add_subdirectory(graphics)
set(GRAPHICS_HEADERS ${GRAPHICS_HEADERS} PARENT_SCOPE)

add_subdirectory(utils)
set(UTILS_HEADERS ${UTILS_HEADERS} PARENT_SCOPE)
