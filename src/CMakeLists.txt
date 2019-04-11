add_subdirectory(engine)
add_subdirectory(game)

set(ENGINE_SOURCES
    ${ENGINE_SOURCES}
    PARENT_SCOPE)

set(GAME_SOURCES
    ${GAME_SOURCES}
    PARENT_SCOPE)
