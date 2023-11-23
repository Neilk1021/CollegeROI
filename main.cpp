#include <iostream>
#include "CollegeROI/ROI-Calculator/ROI.h"
int main() {

    ROI* roiInstance = ROI::GetInstance();

    roiInstance->AddCollege("Berkley", 15000, 15000);

    std::cout<< roiInstance->LoadCollege("Berkley")->GetCost() << std::endl;

    return 0;
}
