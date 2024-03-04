//
// Created by Neilf on 11/22/2023.
//

#ifndef COLLEGEROI__ROI_H
#define COLLEGEROI__ROI_H

#include <unordered_map>
#include <string>
#include <iostream>
#include <stdexcept>
#include <array>
#include "../College/College.h"
#include "../CSV-Compiler/CSVCompiler.h"
#include <cmath>

enum PayRate{ LowPay = 8, MediumPay = 12, HighPay = 16};
enum PrivateInterestRate{ LowInterest = 6, MediumInterest = 8, HighInterest = 11};

class ROI {
    protected:
        const double e = 2.718281828459045;
        std::unique_ptr<std::unordered_map<size_t , std::shared_ptr<College>>> hash;
        std::hash<std::string> hashAlg;
        static ROI* instance;
        unsigned int yearsToPayBack(double currentCost, double yearlyPay, double interest, double payRate, unsigned int length);
        ROI() {};
    public:
        ROI(ROI &other) = delete;
        void operator=(const ROI&) = delete;
        static ROI *GetInstance();
        //Adds college to hash via pointer
        static void AddCollege(const std::string&,  const std::shared_ptr<College>& college);
        //Adds college to hash via cost and ROI
        static void AddCollege(const std::string&, unsigned int, unsigned  int);

        unsigned int GetMaxCostToAttend(double yearlyPay, int minimumValue);

        [[nodiscard]]  std::array<unsigned int, 9> CalculateROIs(const std::shared_ptr<College>& college);

        //Loads college from the hash if one exists.
        [[nodiscard]] static std::shared_ptr<College> LoadCollege(const std::string&) ;

        [[nodiscard]] static std::vector<std::shared_ptr<College>> LoadAllColleges();

};


#endif //COLLEGEROI__ROI_H
