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

