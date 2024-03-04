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

    EXPECT_EQ(roiInstance->LoadCollege("Harvard")->GetCost(), 15000);
}

TEST(CSVCheckSuit, DuplicateCollege){
    ROI* roiInstance = ROI::GetInstance();

    ROI::AddCollege("Harvard", 15000, 15000);
    ROI::AddCollege("Harvard", 65, 65);

    std::unique_ptr<std::unordered_map<size_t , std::shared_ptr<College>>> hash;
    if(CSVCompiler::LoadFromCSV() != nullptr){
        hash = std::move(CSVCompiler::LoadFromCSV());
    }else{
        hash = std::make_unique<std::unordered_map<size_t , std::shared_ptr<College>>>();
    }

    EXPECT_EQ(hash->at(17281574884099900986)->GetCost(), 15000);
}

TEST(CSVCheckSuit, CollegeWithSpaces){
    ROI* roiInstance = ROI::GetInstance();

    ROI::AddCollege("University of Utah", 15000, 15000);
    std::unique_ptr<std::unordered_map<size_t , std::shared_ptr<College>>> hash;
    if(CSVCompiler::LoadFromCSV() != nullptr){
        hash = std::move(CSVCompiler::LoadFromCSV());
    }else{
        hash = std::make_unique<std::unordered_map<size_t , std::shared_ptr<College>>>();
    }

    EXPECT_EQ(hash->at(10145603584388529810)->GetCost(), 15000);
}

TEST(ROITestSuit, CalculateValue){
    ROI* roiInstance = ROI::GetInstance();
    int val = roiInstance->GetMaxCostToAttend(100000, 36);
    EXPECT_EQ(26562, val);
}