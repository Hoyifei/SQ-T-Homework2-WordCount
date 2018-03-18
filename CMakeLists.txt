cmake_minimum_required(VERSION 3.8)
project(WordCount)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES_COMMON CWordCount.cpp CWordCount.h)
set(SOURCE_FILES ${SOURCE_FILES_COMMON} main.cpp)
set(SOURCE_FILES_UNITTEST1 ${SOURCE_FILES_COMMON} UnitTest1__Base.cpp)
add_executable(WordCount ${SOURCE_FILES})
add_executable(UnitTest1 ${SOURCE_FILES_UNITTEST1})
target_link_libraries(UnitTest1 gtest)