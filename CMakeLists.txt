project(Bytecode)

cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CXXFLAGS "{CXXFLAGS} -Wall -Werror -Wpedantic")

enable_testing()


add_library(core
    lib/io.cpp
    lib/lex.cpp
    lib/parse.cpp
    lib/parse_node.cpp
    lib/parse_stack.cpp
    lib/parse_strategies.cpp
    lib/token.cpp
)

target_include_directories(core
    PRIVATE include
)


add_executable(main
    main.cpp
)

target_include_directories(main
    PRIVATE include
)

target_link_libraries(main
    PRIVATE core
)


add_executable(unittest
    unittest/main.cpp
    unittest/lex.cpp
    unittest/parse.cpp
    unittest/parse_strategies.cpp
)

add_test(NAME unittest COMMAND unittest)

target_include_directories(unittest
    PRIVATE include
)

target_link_libraries(unittest
    PRIVATE core
    PRIVATE gtest
)
