//
// Created by Neilf on 11/22/2023.
//

#include "ROI.h"
ROI* ROI::instance = nullptr;;
ROI *ROI::GetInstance() {
    if(instance == nullptr){
        instance = new ROI();
        if(CSVCompiler::LoadFromCSV() != nullptr){
            instance->hash = std::move(CSVCompiler::LoadFromCSV());
        }else{
            instance->hash = std::make_unique<std::unordered_map<size_t , std::shared_ptr<College>>>();
        }
    }

    return instance;
}

void ROI::AddCollege(const std::string& CollegeName, const std::shared_ptr<College>& college) {
    try{
        size_t hashVal = instance->hashAlg(CollegeName);
        if (instance->hash->find(hashVal) == instance->hash->end()){
            instance->hash->emplace(hashVal, college);

            CSVCompiler::SaveToCSV(hashVal, college);

            return;
        }

        throw std::invalid_argument("College already exists in map");
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
    }
}

void ROI::AddCollege(const std::string& CollegeName, unsigned int cost, unsigned int ROI) {
    try{
        size_t hashVal = instance->hashAlg(CollegeName);
        if (instance->hash->find(hashVal) == instance->hash->end()){
            instance->hash->emplace(hashVal, std::make_shared<College>( College(cost, ROI, CollegeName)));
            std::cout << "Added " << CollegeName << ": Cost - " << cost << " Average Salary - " << ROI << std::endl;
            CSVCompiler::SaveToCSV(hashVal, instance->hash->at(hashVal));
            return;
        }

        throw std::invalid_argument("College already exists in map");
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
    }
}

std::shared_ptr<College> ROI::LoadCollege(const std::string& CollegeName) {
    try{
        size_t hashVal = instance->hashAlg(CollegeName);
        if (instance->hash->find(hashVal) == instance->hash->end()){
            throw std::invalid_argument("College doesn't exist.");
        }
        return instance->hash->at(hashVal);
    }
    catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
}

std::vector<std::shared_ptr<College>> ROI::LoadAllColleges() {

    std::vector<std::shared_ptr<College>> vals;
    vals.reserve(ROI::instance->hash->size());

    for(auto kv : *ROI::instance->hash) {
        vals.push_back(kv.second);
    }

   return  vals;
}

std::array<unsigned int, 9> ROI::CalculateROIs(const std::shared_ptr<College> &college) {
    unsigned int debt = college->GetCost() * 4;
    unsigned int yearlyReturn = college->GetReturn();
    std::array<unsigned int,9> projections{};

    projections[0] = ROI::yearsToPayBack(debt, yearlyReturn, (double)LowInterest/100, (double)LowPay/100, 1);
    projections[1] = ROI::yearsToPayBack(debt, yearlyReturn, (double)LowInterest/100, (double)MediumPay/100, 1);
    projections[2] = ROI::yearsToPayBack(debt, yearlyReturn, (double)LowInterest/100, (double)HighPay/100, 1);
    projections[3] = ROI::yearsToPayBack(debt, yearlyReturn, (double)MediumInterest/100, (double)LowPay/100, 1);
    projections[4] = ROI::yearsToPayBack(debt, yearlyReturn, (double)MediumInterest/100, (double)MediumPay/100, 1);
    projections[5] = ROI::yearsToPayBack(debt, yearlyReturn, (double)MediumInterest/100, (double)HighPay/100, 1);
    projections[6] = ROI::yearsToPayBack(debt, yearlyReturn, (double)HighInterest/100, (double)LowPay/100, 1);
    projections[7] = ROI::yearsToPayBack(debt, yearlyReturn, (double)HighInterest/100, (double)MediumPay/100, 1);
    projections[8] = ROI::yearsToPayBack(debt, yearlyReturn, (double)HighInterest/100, (double)HighPay/100, 1);

    return projections;
}

unsigned int ROI::yearsToPayBack(double currentCost, double yearlyPay, double interest, double payRate, unsigned int length) {

    if(length >= 75) return 75;

    double nextCost = (currentCost - (yearlyPay*payRate))*std::pow(e,interest);
    if(nextCost <= 0 ) {return length;}

    return yearsToPayBack(nextCost,  yearlyPay,  interest,  payRate, length +1);
}

