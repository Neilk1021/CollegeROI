//
// Created by Neil Ketteringham on 11/22/23.
//
#include "gtest/gtest.h"
#include "../CollegeROI/ROI-Calculator/ROI.h"

TEST(CollegeCheckSuit, ExampleCollege){
    ROI* roiInstance = ROI::GetInstance();

    roiInstance->AddCollege("Berkley", 15000, 15000);

    EXPECT_EQ(roiInstance->LoadCollege("Berkley")->GetCost(), 15000);
}