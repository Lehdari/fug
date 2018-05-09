#   add sources

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SUB_SOURCES)

set(TEST_SOURCES
    ${TEST_SOURCES}
    ${SUB_SOURCES}
    PARENT_SCOPE)

#   add headers

file(GLOB SUB_HEADERS "*.hpp")

set(TEST_SOURCES
    ${TEST_SOURCES}
    ${SUB_SOURCES}
    PARENT_SCOPE)

set(TEST_HEADERS
    ${TEST_HEADERS}
    ${SUB_HEADERS}
    PARENT_SCOPE)