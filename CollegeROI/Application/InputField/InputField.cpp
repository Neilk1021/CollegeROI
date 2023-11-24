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

void InputField::refresh(unsigned int checkVal, HANDLE hConsole) {

}
