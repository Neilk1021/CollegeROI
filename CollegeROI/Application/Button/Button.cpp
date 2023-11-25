//
// Created by Neilf on 11/23/2023.
//

#include "Button.h"

void Button::refresh(unsigned int checkVal, HANDLE hConsole) {
    if(checkVal == val){
        SetConsoleTextAttribute(hConsole, ColorHighlight);
        std::cout << label;
        SetConsoleTextAttribute(hConsole, Color);
        std::cout << std::endl;
        return;
    }

    SetConsoleTextAttribute(hConsole, Color);
    std::cout << label << std::endl;
}


void Button::runFunction(const std::vector<std::string>& data_) const {
    if(type != InputTypes::Action){
        throw std::invalid_argument("Function ran on non-action");
    }

    std::vector<std::string> TextInfo;
    std::vector<unsigned int> NumInfo;
    for (const auto & i : data_) {
        if(std::isalpha(i[0])){
            TextInfo.push_back(i);
            continue;
        }

        NumInfo.push_back(std::stoi(i));
    }

    try{
        funcPtr(TextInfo[0], NumInfo[0], NumInfo[1]);
    }catch(std::invalid_argument &e){
        std::cout << e.what() << std::endl;
    }
}

void Button::addFunction(void (*fPtr)(const std::string &, unsigned int, unsigned int)) {
    funcPtr = fPtr;
}

Button::Button(InputTypes::Type type, int pos, const std::string &labelVal) : InputField(type) {
    this->val = pos;
    this->label = labelVal;
}
