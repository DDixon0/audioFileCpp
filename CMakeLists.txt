cmake_minimum_required(VERSION 3.0.0)
project(soundTest VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_TOOLCHAIN_FILE "/home/dexter/src/vcpkg/scripts/buildsystems/vcpkg.cmake")

include(CTest)
enable_testing()

add_executable(soundTest main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#set(CMAKE_PREFIX_PATH "/home/dexter/src/vcpkg/installed/x64-linux/share")


find_package(AudioFile CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE AudioFile)
