cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(src_list_h extcom_def.h extcom.h)
set(src_list_cpp extcom.cpp main.cpp)

add_executable(abama_ss ${src_list_h} ${src_list_cpp})
