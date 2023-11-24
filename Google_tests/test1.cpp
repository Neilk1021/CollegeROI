//
// Created by Neil Ketteringham on 11/22/23.
//
#include "gtest/gtest.h"
#include "../CollegeROI/ROI-Calculator/ROI.h"

TEST(CollegeCheckSuit, ExampleCollege){
    ROI* roiInstance = ROI::GetInstance();

    ROI::AddCollege("Berkley", 15000, 15000);

    EXPECT_EQ(roiInstance->LoadCollege("Berkley")->GetCost(), 15000);
}

TEST(CollegeCheckSuit, CollegeDuplicate){
    ROI* roiInstance = ROI::GetInstance();

    ROI::AddCollege("Harvard", 15000, 15000);
    ROI::AddCollege("Harvard", 65, 65);

    EXPECT_EQ(roiInstance->LoadCollege("Berkley")->GetCost(), 15000);
}