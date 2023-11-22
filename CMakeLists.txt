cmake_minimum_required(VERSION 3.26)
project(CollegeROI_)

set(CMAKE_CXX_STANDARD 17)

add_executable(CollegeROI_ main.cpp
        College/College.cpp
        College/College.h
        ROI-Calculator/ROI.cpp
        ROI-Calculator/ROI.h)
