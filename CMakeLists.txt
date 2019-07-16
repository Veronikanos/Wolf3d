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

#cmake_minimum_required(VERSION 3.12.1)
#project(Wolf3d C)
#
#find_library(libsdl SDL2)
#find_library(libsdl_img SDL2_image)
#find_library(libsdl_ttf SDL2_ttf)
#find_library(libsdl_mixer SDL2_mixer)
#
#set(CMAKE_C_STANDARD 99)
#
#set(LIB_PATH   ./)
#set(SRC_PATH   ./)
#set(INC_PATH   ./)
#set(LFT_PATH   libft)
#set(LFT_NAME   ft)
#set(LFT_LIB    ${LFT_PATH})
#
#aux_source_directory( ${LFT_LIB} LFT_SRC)
#aux_source_directory( ${SRC_PATH} PROJECT_SOURCE_FILES)
#add_library(   ${LFT_NAME} STATIC ${LFT_SRC})
#
##include_directories(./)
#add_executable(${PROJECT_NAME}
#        ${PROJECT_SOURCE_FILES})
#
#set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Werror")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#set(dir ${CMAKE_CURRENT_SOURCE_DIR})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${dir}/bin")
#target_link_libraries(${PROJECT_NAME} ${LFT_NAME}
#        ${libsdl} ${libsdl_img} ${libsdl_ttf} ${libsdl_mixer})