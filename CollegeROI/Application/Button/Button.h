//
// Created by Neilf on 11/23/2023.
//

#ifndef COLLEGEROI__BUTTON_H
#define COLLEGEROI__BUTTON_H
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <vector>
#include "../InputField/InputField.h"


class Button : public InputField {
private:
    void (*funcPtr)(const std::string&, unsigned int, unsigned int){};
    std::vector<std::string> data;
public:
    #ifdef _WIN32
        void refresh(unsigned int checkVal, HANDLE hConsole) override;
    #endif
    #ifdef __APPLE__
        void refresh(unsigned int checkVal) override;
    #endif
    Button(InputTypes::Type type, int pos, const std::string &labelVal);

    void addFunction(void (*fPtr)(const std::string &, unsigned int, unsigned int));
    void runFunction(const std::vector<std::string>& data_) const;
};


#endif //COLLEGEROI__BUTTON_H
