cmake_minimum_required(VERSION 3.26)
project(CollegeROI_)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#set(CMAKE_CXX_FLAGS "-lcurses -ltermcap")

#find_package(Curses REQUIRED)
add_subdirectory(Google_tests)
#include_directories(${CURSES_INCLUDE_DIR})

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

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
        CollegeROI/CSV-Compiler/CSVCompiler.cpp
        CollegeROI/CSV-Compiler/CSVCompiler.h
)

#target_link_libraries(CollegeROI_ ${CURSES_LIBRARIES})