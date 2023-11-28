//
// Created by Neilf on 11/24/2023.
//

#ifndef COLLEGEROI__INPUTFIELD_H
#define COLLEGEROI__INPUTFIELD_H
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif
struct InputTypes{
    enum Type {WindowLoader, Action, Keyboard};
};

class InputField {
    protected:
        int val{};
        std::string label;

    #ifdef _WIN32
        const int Color = 15;
        const int ColorHighlight = 79;
    #endif

    #ifdef __APPLE__
        const int Color = 15;
        const int ColorHighlight = 41;
    #endif

        InputTypes::Type type;
    public:
        explicit InputField(InputTypes::Type type_);

    #ifdef _WIN32
        virtual void refresh(unsigned int checkVal, HANDLE hConsole);
    #endif
    #ifdef __APPLE__
        virtual void refresh(unsigned int checkVal);
    #endif
        virtual ~InputField() = default;
        [[nodiscard]] InputTypes::Type getType() const;
};


#endif //COLLEGEROI__INPUTFIELD_H
