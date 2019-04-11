# Add headers
file(GLOB SUB_HEADERS "*.hpp")

set(ENGINE_HEADERS
    ${ENGINE_HEADERS}
    ${SUB_HEADERS}
    PARENT_SCOPE)
