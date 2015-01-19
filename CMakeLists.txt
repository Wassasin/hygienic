cmake_minimum_required(VERSION 2.8)

project(hygienic)

include_directories("${PROJECT_BINARY_DIR}")

file(GLOB_RECURSE HYGIENIC_SOURCES src/*.cpp)
file(GLOB_RECURSE HYGIENIC_HEADERS src/*.hpp)

add_executable(hygienic
	${HYGIENIC_SOURCES}
	${HYGIENIC_HEADERS}
)

add_definitions("-Wall -Wextra -Weffc++ -std=c++0x -pedantic -g -O3")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      "${PROJECT_SOURCE_DIR}/cmake/modules")

find_package(Boost COMPONENTS system program_options regex filesystem REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
                    
target_link_libraries(hygienic
                      ${Boost_SYSTEM_LIBRARY}
                      ${Boost_PROGRAM_OPTIONS_LIBRARY}
                      ${Boost_REGEX_LIBRARY}
                      ${Boost_FILESYSTEM_LIBRARY})
