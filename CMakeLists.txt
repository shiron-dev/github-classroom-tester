cmake_minimum_required(VERSION 3.1)
project(github-classroom-tester VERSION 1.0)

include_directories(src/)
add_executable(gc-tester
  src/main.cpp
  src/terminal/terminal.cpp
  src/terminal/decoration.cpp
  src/tester/tester.cpp
  src/tester/test_io.cpp
)