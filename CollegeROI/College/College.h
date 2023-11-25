//
// Created by Neilf on 11/22/2023.
//

#ifndef COLLEGEROI__COLLEGE_H
#define COLLEGEROI__COLLEGE_H
#include <string>

class College {
    private:
        std::string Name;
        unsigned int cost;
        unsigned int expectedReturn;
    public:
        College(unsigned int, unsigned int, std::string);
        const std::string &GetName() const;
        [[nodiscard]] int GetCost() const;
        [[nodiscard]] int GetReturn() const;
};


#endif //COLLEGEROI__COLLEGE_H
