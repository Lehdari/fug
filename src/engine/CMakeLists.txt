# Add sources
file(GLOB SUB_SOURCES "*.cpp")

set(ENGINE_SOURCES
    ${ENGINE_SOURCES}
    ${SUB_SOURCES}
    PARENT_SCOPE)
