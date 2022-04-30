cmake_minimum_required(VERSION 3.1)
project(github-classroom-tester CXX)

include_directories(src/)
add_executable(main
  src/main.cpp
  src/terminal/terminal.cpp
)