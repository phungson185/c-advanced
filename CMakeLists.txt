cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(dict)

set(CMAKE_C_STANDARD 99)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)
add_subdirectory(libfdr)
add_subdirectory(DebugPrintf)
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/libfdr)

include_directories({PROJECT_SOURCE_DIR}/cmake-btree/inc)
link_directories(${PROJECT_SOURCE_DIR}/cmake-btree/lib)

option(GPROF_FLAG "Bổ xung khóa để sử dụng với gprof" OFF)
option(USE_IGRAPH "Sử dụng igraph (xem hướng dẫn trong igraph.cmd)" ON)

if (GPROF_FLAG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
endif (GPROF_FLAG)
if (USE_IGRAPH)
  add_library(igraph STATIC IMPORTED)
  set_target_properties(igraph PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/binaries/libigraph.a)
  set(IGRAPH_LIBS igraph m)
endif (USE_IGRAPH)

add_executable(qlykhang ex/quan_ly_kho_hang/qlykhang.c)
target_link_libraries(qlykhang ${IGRAPH_LIBS} fdr debug_printf)

add_executable(cuoiki2015 ex/cuoiki2015.c)
target_link_libraries(cuoiki2015 ${IGRAPH_LIBS} fdr debug_printf)

