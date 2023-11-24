cmake_minimum_required(VERSION 3.26)
project(CollegeROI_)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Google_tests)
add_executable(CollegeROI_ main.cpp
        CollegeROI/College/College.cpp
        CollegeROI/College/College.h
        CollegeROI/ROI-Calculator/ROI.cpp
        CollegeROI/ROI-Calculator/ROI.h
        CollegeROI/Application/Application.cpp
        CollegeROI/Application/Application.h
        CollegeROI/Application/Window/Window.cpp
        CollegeROI/Application/Window/Window.h
        CollegeROI/Application/Button/Button.cpp
        CollegeROI/Application/Button/Button.h
        CollegeROI/Application/InputField/InputField.cpp
        CollegeROI/Application/InputField/InputField.h
        CollegeROI/Application/TextInput/TextInput.cpp
        CollegeROI/Application/TextInput/TextInput.h
)
