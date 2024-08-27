cmake_minimum_required(VERSION 3.16)
project(monitor)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(monitor ${SOURCES})

set_property(TARGET monitor PROPERTY CXX_STANDARD 17)
target_link_libraries(monitor ${CURSES_LIBRARIES})
if(MSVC)
  target_compile_options(monitor PRIVATE /W4 /WX)
else()
  target_compile_options(monitor PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
