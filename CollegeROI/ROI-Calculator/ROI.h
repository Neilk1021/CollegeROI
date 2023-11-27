//
// Created by Neilf on 11/22/2023.
//

#ifndef COLLEGEROI__ROI_H
#define COLLEGEROI__ROI_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <stdexcept>
#include "../College/College.h"
#include "../CSV-Compiler/CSVCompiler.h"

class ROI {
    protected:
        std::unique_ptr<std::unordered_map<size_t , std::shared_ptr<College>>> hash;
        std::hash<std::string> hashAlg;
        static ROI* instance;
        ROI() {};
    public:
        ROI(ROI &other) = delete;
        void operator=(const ROI&) = delete;
        static ROI *GetInstance();
        //Adds college to hash via pointer
        static void AddCollege(const std::string&,  const std::shared_ptr<College>& college);
        //Adds college to hash via cost and ROI
        static void AddCollege(const std::string&, unsigned int, unsigned  int);
        //Loads college from the hash if one exists.
        [[nodiscard]] static std::shared_ptr<College> LoadCollege(const std::string&) ;

        [[nodiscard]] static std::vector<std::shared_ptr<College>> LoadAllColleges();

};


#endif //COLLEGEROI__ROI_H
