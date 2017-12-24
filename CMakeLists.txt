cmake_minimum_required(VERSION 3.8)
project(OperatingSystem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp storage_manage.h lock.h schedule.h locktest.h)
add_executable(OperatingSystem ${SOURCE_FILES})