# 指定CMake最低版本要求
cmake_minimum_required(VERSION 3.10)

# 开启调试模式，生成调试符号（-g），方便 Valgrind 分析
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# 设置C++标准版本为C++11，并确保严格要求此标准，不使用扩展功能
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 设置所有库生成位置无关代码 (Position Independent Code) 对应GCC/Clang的-fPIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 设置输出路径：库文件、可执行文件和归档文件的生成目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build_output/lib) # 静态库 (.a/.lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build_output/bin) # 动态库 (.so/.dll)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/build_output/bin) # 可执行文件

# 设置位置无关代码 (PIC)，对于动态库来说是必须的
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(ValgrindLeakDemo LANGUAGES CXX VERSION 0.9.1)

add_executable(leak_demo src/leak_demo.cpp)
add_executable(normal_demo src/normal_demo.cpp)

