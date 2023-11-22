//
// Created by Neilf on 11/22/2023.
//

#ifndef COLLEGEROI__COLLEGE_H
#define COLLEGEROI__COLLEGE_H


class College {
    private:
        unsigned int cost;
        unsigned int expectedReturn;
    public:
        College(unsigned int, unsigned int);
        [[nodiscard]] int GetCost() const;
        [[nodiscard]] int GetReturn() const;
};


#endif //COLLEGEROI__COLLEGE_H
