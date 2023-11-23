//
// Created by Neilf on 11/22/2023.
//

#include "ROI.h"
ROI* ROI::instance = nullptr;;
ROI *ROI::GetInstance() {
    if(instance == nullptr){
        instance = new ROI();
    }

    return instance;
}

void ROI::AddCollege(const std::string& CollegeName, College* college) {
    try{
        size_t hashVal = hashAlg(CollegeName);
        if (hash.find(hashVal) == hash.end()){
            hash[hashVal] = college;
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
        size_t hashVal = hashAlg(CollegeName);
        if (hash.find(hashVal) == hash.end()){
            hash[hashVal] = new College(cost, ROI);
            return;
        }

        throw std::invalid_argument("College already exists in map");
    }
    catch (std::invalid_argument &e){
        std::cout << e.what() << std::endl;
    }
}

College * ROI::LoadCollege(const std::string& CollegeName) const {
    try{
        size_t hashVal = hashAlg(CollegeName);
        if (hash.find(hashVal) == hash.end()){
            throw std::invalid_argument("College doesn't exist.");
        }
        return hash.at(hashVal);
    }
    catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return nullptr;
    }
}

