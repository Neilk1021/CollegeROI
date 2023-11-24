//
// Created by Neilf on 11/23/2023.
//

#include "Button.h"

void Button::refresh(unsigned int checkVal, HANDLE hConsole) {
    if(checkVal == val){
        SetConsoleTextAttribute(hConsole, ColorHighlight);
        std::cout << label << std::endl;
        return;
    }

    SetConsoleTextAttribute(hConsole, Color);
    std::cout << label << std::endl;
}

Button::Button(int pos, const std::string &labelVal) {
    this->val = pos;
    this->label = labelVal;
}
