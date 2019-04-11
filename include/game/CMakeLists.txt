# Add headers
file(GLOB SUB_HEADERS "*.hpp")

set(GAME_HEADERS
    ${GAME_HEADERS}
    ${SUB_HEADERS}
    PARENT_SCOPE)
