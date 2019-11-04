add_subdirectory(glsprite)

add_library(stb_image
    STATIC
        glsprite/sdl-main/stb_image.c
)

target_include_directories(stb_image
    INTERFACE
        glsprite/sdl-main/stb
)
