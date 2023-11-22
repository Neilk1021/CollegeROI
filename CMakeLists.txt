cmake_minimum_required(VERSION 3.26)
project(CollegeROI_)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Google_tests)
add_executable(CollegeROI_ main.cpp
        CollegeROI/College/College.cpp
        CollegeROI/College/College.h
        CollegeROI/ROI-Calculator/ROI.cpp
        CollegeROI/ROI-Calculator/ROI.h)
