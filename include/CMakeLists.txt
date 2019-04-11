add_subdirectory(engine)
add_subdirectory(game)

set(ENGINE_HEADERS
    ${ENGINE_HEADERS}
    PARENT_SCOPE)

set(GAME_HEADERS
    ${GAME_HEADERS}
    PARENT_SCOPE)
