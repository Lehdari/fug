add_subdirectory(glsprite)
# This is needed to link from shared libs
set_target_properties(glsprite PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(glsprite-glutil PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(APPLE)
    # Static lib doesn't link on osx for some reason
    set(LIBGL3W_BUILD_SHARED ON CACHE BOOL "Build shared lib")
endif()
add_subdirectory(libgl3w)
if(NOT APPLE)
    set_target_properties(libgl3w PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()
