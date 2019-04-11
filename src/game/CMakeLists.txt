# Add sources
file(GLOB SUB_SOURCES "*.cpp")

set(GAME_SOURCES
    ${GAME_SOURCES}
    ${SUB_SOURCES}
    PARENT_SCOPE)
