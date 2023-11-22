//
// Created by Neilf on 11/22/2023.
//

#include "College.h"

College::College(unsigned int Cost, unsigned int Return)  {
    this->cost = Cost;
    this->expectedReturn = Return;
}

int College::GetCost() const {
    return cost;
}

int College::GetReturn() const {
    return expectedReturn;
}

