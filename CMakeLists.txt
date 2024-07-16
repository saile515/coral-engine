cmake_minimum_required(VERSION 3.28)

project("coral-engine" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_SOURCES # cmake-format: sort
                    src/coral-engine.cpp src/window.cpp)
set(PROJECT_HEADERS
    # cmake-format: sort
    include/coral-engine.hpp
    include/coral.hpp
    include/log.hpp
    include/node.hpp
    include/resource.hpp
    include/scene.hpp
    include/vector3.hpp
    include/window.hpp)
list(APPEND PROJECT_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/include
     /usr/include)
list(APPEND PROJECT_LIBRARIES glfw)

find_package(glfw3 REQUIRED)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS})
target_include_directories(${PROJECT_NAME}
                           PUBLIC ${PROJECT_INCLUDE_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LIBRARIES})
