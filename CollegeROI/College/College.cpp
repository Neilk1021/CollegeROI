    //
// Created by Neilf on 11/22/2023.
//

#include "College.h"

College::College(unsigned int Cost, unsigned int Return, std::string Name)  {
    this->cost = Cost;
    this->expectedReturn = Return;
    this->Name = Name;
}

int College::GetCost() const {
    return cost;
}

int College::GetReturn() const {
    return expectedReturn;
}

const std::string &College::GetName() const {
    return Name;
}

