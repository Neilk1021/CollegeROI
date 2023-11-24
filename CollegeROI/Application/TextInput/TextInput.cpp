//
// Created by Neilf on 11/24/2023.
//

#include "TextInput.h"

TextInput::TextInput(InputTypes::Type type, unsigned int pos, const std::string &labelVal, bool num) : InputField(type){
    this->val = pos;
    this->label = labelVal;
    numOnly = num;
}

void TextInput::refresh(unsigned int checkVal, HANDLE hConsole) {
    if(checkVal == val){
        SetConsoleTextAttribute(hConsole, ColorHighlight);
        std::cout << label << " " << info;
        SetConsoleTextAttribute(hConsole, Color);
        std::cout << std::endl;
        return;
    }

    SetConsoleTextAttribute(hConsole, Color);
    std::cout << label << " " << info << std::endl;
}

void TextInput::addChar(char c) {
    info += c;
}

void TextInput::deleteChar() {
    if(!info.empty()){
        info.erase(info.end()-1, info.end());
    }
}

bool TextInput::isNumOnly() const {
    return numOnly;
}

const std::string &TextInput::getInfo() const {
    return info;
}
