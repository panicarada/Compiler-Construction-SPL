cmake_minimum_required(VERSION 3.19)
project(SPL_PROJECT)
set(CMAKE_CXX_STANDARD 17)

# 设置文件夹名称
set(SOURCE_DIR source)
set(BUILD_DIR build)
set(INCLUDE_DIR include)
set(TARGET_DIR bin)
set(LEX_YACC lex_yacc)

# 设置所用的lex / yacc
set(LEX flex)
set(YACC bison)

# bison and flex
find_package(BISON)
find_package(FLEX)

include_directories(${LEX_YACC})


# 设置lex和yacc的输出文件名
set(LEX_FILE lex)
set(YACC_FILE yacc)
# lex编译.l文件
execute_process(COMMAND ${LEX} -o ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/${LEX_FILE}.yy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${LEX_YACC}/${LEX_FILE}.l)
# yacc编译.y文件
execute_process(COMMAND ${YACC} -o ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/${YACC_FILE}.tab.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${LEX_YACC}/${YACC_FILE}.y -d)
# 把生成的yacc.tab.hpp转移到include路径
execute_process(COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_DIR}/${YACC_FILE}.tab.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_DIR}/)

# llvm
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")


# Set your project compile flags.
# E.g. if using the C++ header files
# you will need to enable C++11 support
# for your compiler.

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(include)
add_definitions(${LLVM_DEFINITIONS})

# Now build our tools
aux_source_directory(${SOURCE_DIR} SRC_LIST)


# 可执行文件输出到bin
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_DIR}")
add_executable(main ${SRC_LIST})

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
# 连接llvm
target_link_libraries(main ${llvm_libs})
