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

class ROI {
    protected:
        std::unordered_map<size_t ,College*> hash;
        std::hash<std::string> hashAlg;
        static ROI* instance;
        ROI() {};
    public:
        ROI(ROI &other) = delete;
        void operator=(const ROI&) = delete;
        static ROI *GetInstance();
        //Adds college to hash via pointer
        void AddCollege(const std::string&, College*);
        //Adds college to hash via cost and ROI
        void AddCollege(const std::string&, unsigned int, unsigned  int);
        //Loads college from the hash if one exists.
        [[nodiscard]] College * LoadCollege(const std::string&) const;
};


#endif //COLLEGEROI__ROI_H
