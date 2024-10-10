cmake_minimum_required(VERSION 3.5)
project(Enigma VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

file(GLOB TARGET_SRC "./src/*.cpp" )

add_executable(main ${TARGET_SRC})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
