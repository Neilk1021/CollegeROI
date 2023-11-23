project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
add_executable(Google_Tests_run test1.cpp
        ../CollegeROI/College/College.cpp
        ../CollegeROI/College/College.h
        ../CollegeROI/ROI-Calculator/ROI.cpp
        ../CollegeROI/ROI-Calculator/ROI.h
        ../CollegeROI/Application/Application.cpp
        ../CollegeROI/Application/Application.h)


target_link_libraries(Google_Tests_run gtest gtest_main)