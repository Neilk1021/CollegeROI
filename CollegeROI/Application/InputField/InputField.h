//
// Created by Neilf on 11/24/2023.
//

#ifndef COLLEGEROI__INPUTFIELD_H
#define COLLEGEROI__INPUTFIELD_H
#include <string>
#include <windows.h>
struct InputTypes{
    enum Type {WindowLoader, Action, Keyboard};
};

class InputField {
    protected:
        int val{};
        std::string label;
        const int Color = 15;
        const int ColorHighlight = 79;
        InputTypes::Type type;
    public:
        explicit InputField(InputTypes::Type type_);
        virtual void refresh(unsigned int checkVal, HANDLE hConsole);
        virtual ~InputField() = default;
        [[nodiscard]] InputTypes::Type getType() const;
};


#endif //COLLEGEROI__INPUTFIELD_H
