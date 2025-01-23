cmake_minimum_required(VERSION 3.23)
project(ChessGame)

# NOTE: Folders here contain both SDL2 and SDL2_image files.
set(SDL2_LIB_DIR C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/lib)
set(SDL2_INCLUDE_DIR C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/include)
set(SDL2_LIBRARY C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/bin)


set(SDL2IMAGE_LIB_DIR C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2_image-2.6.2/x86_64-w64-mingw32/lib)
set(SDL2IMAGE_INCLUDE_DIR C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2_image-2.6.2/x86_64-w64-mingw32/include)
set(SDL2IMAGE_LIBRARY C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2_image-2.6.2/x86_64-w64-mingw32/bin)

# SETUP INCLUDE AND LINK DIRS:
include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2IMAGE_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)
# message(STATUS "SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
# message(STATUS "SDL2_LIB_DIR: ${SDL2_LIB_DIR}")
    
link_directories( ${SDL2_LIB_DIR} ${SDL2IMAGE_LIB_DIR})

# INCLUDE FILES THAT SHOULD BE COMPILED:
file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h")

message(STATUS "Add source files:")
foreach(SRC_FILE IN LISTS SRC)
    message(STATUS "${SRC_FILE}")
endforeach()
message(STATUS "")

add_executable(${PROJECT_NAME} ${SRC})

# LINK PROGRAM
target_link_libraries( ${PROJECT_NAME} mingw32 SDL2main SDL2 SDL2_image)

# #FIND SDL2 Package
# find_package(SDL2 REQUIRED)
#
# # --- SDL2 SETUP ---
###
# set(CMAKE_PREFIX_PATH "C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/cmake")
# find_package(SDL2 REQUIRED CONFIG)
# include_directories("C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/include/")
# # link_directories("C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/lib")
# #LINK SDL2 to ChessGame
# target_link_libraries(ChessGame PRIVATE  "C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/lib/libSDL2.a" "C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/lib/libSDL2main.a")
# #"C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/lib/libSDL2main.a"
# # "C:/Users/LENOVO/projects/cpp/SDL2-MinGw/SDL2-2.30.8/x86_64-w64-mingw32/lib/libSDL2.a"
# # target_link_libraries(ChessGame PRIVATE SDL2main SDL2)
#
