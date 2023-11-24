//
// Created by Neilf on 11/23/2023.
//

#ifndef COLLEGEROI__BUTTON_H
#define COLLEGEROI__BUTTON_H
#include <string>
#include <windows.h>
#include <iostream>

class Button {
private:
    int val;
    std::string label;
    const int Color = 15;
    const int ColorHighlight = 67;
public:
    void refresh(unsigned int checkVal, HANDLE hConsole);
    Button(int pos, const std::string &labelVal);
};


#endif //COLLEGEROI__BUTTON_H
