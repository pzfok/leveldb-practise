cmake_minimum_required(VERSION 3.1)
project(leveldb_practise)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIBARAY_ROOT ../lib)
set(GTEST_ROOT ${LIBARAY_ROOT}/Gtest)
set(LEVELDB_ROOT ${LIBARAY_ROOT}/Leveldb)

aux_source_directory(./src SOURCE_FILES)

include_directories(${GTEST_ROOT}/include ${LEVELDB_ROOT}/include)
link_directories(${GTEST_ROOT}/dynamic_lib ${LEVELDB_ROOT}/dynamic_lib)

add_executable(leveldb_practise ${SOURCE_FILES})
target_link_libraries(leveldb_practise -lgtest pthread -lleveldb)
