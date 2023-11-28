//
// Created by Neilf on 11/24/2023.
//

#include "InputField.h"
InputTypes::Type InputField::getType() const {
    return type;
}

InputField::InputField(InputTypes::Type type_) {
    this->type = type_;
}

#ifdef _WIN32
void InputField::refresh(unsigned int checkVal, HANDLE hConsole) {

}
#endif
#ifdef __APPLE__
void InputField::refresh(unsigned int checkVal) {

}
#endif