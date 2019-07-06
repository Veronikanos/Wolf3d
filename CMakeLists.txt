cmake_minimum_required(VERSION 3.12.1)
project(Wolf3d C)
file(GLOB SOURCES
        libft/*.h
        libft/*.c
        *.h
        *.c)
set(CMAKE_C_STANDARD 99)
set(SDL2_INCLUDE_DIR ~/.brew/include/SDL2/
        ~/.brew/include/SDL2_mixer/
        ~/.brew/include/SDL2_image/
        ~/.brew/include/SDL2_ttf/)
set(SDL2_LIBRARY ~/.brew/lib/)

include_directories(libft/)
include_directories(frameworks/SDL2.framework/Headers/)
include_directories(frameworks/SDL2_image.framework/Headers/)
include_directories(frameworks/SDL2_ttf.framework/Headers/)
include_directories(frameworks/SDL2_mixer.framework/Headers/)

link_directories(${SDL2_LIBRARY})
add_executable(Wolf3d
        ${SOURCES})
target_link_libraries(Wolf3d -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf)