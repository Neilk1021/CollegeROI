//
// Created by Neilf on 11/24/2023.
//

#ifndef COLLEGEROI__TEXTINPUT_H
#define COLLEGEROI__TEXTINPUT_H
#include "../InputField/InputField.h"
#include <iostream>

class TextInput : public InputField{
    private:
        std::string info;
public:
    const std::string &getInfo() const;

private:
    bool numOnly = false;
public:
        TextInput(InputTypes::Type type, unsigned int pos, const std::string &labelVal, bool num = false);

    #ifdef _WIN32
        void refresh(unsigned int checkVal, HANDLE hConsole) override;
    #endif
    #ifdef __APPLE__
        void refresh(unsigned int checkVal) override;
    #endif
        void addChar(char c);
        void deleteChar();
        [[nodiscard]] bool isNumOnly() const;
};


#endif //COLLEGEROI__TEXTINPUT_H
