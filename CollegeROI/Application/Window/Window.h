//
// Created by Neilf on 11/23/2023.
//

#ifndef COLLEGEROI__WINDOW_H
#define COLLEGEROI__WINDOW_H
#include <memory>
#include <list>
#include <string>
#include <windows.h>
#include <iostream>
#include <stdexcept>
#include "../Button/Button.h"
#include <conio.h>
#include <vector>
#include "../InputField/InputField.h"
#include "../TextInput/TextInput.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13
#define BACKSPACE 8

struct subHeading{
    int Color;
    std::string Info;
};

class Window {
    private:
        static HANDLE hConsole;
        std::vector<std::shared_ptr<Window>> windowPtr;
        std::vector<InputField*> inputs;
        std::vector<subHeading> additionalInfo;

        std::string information;

        unsigned int buttonVal = 1;
        bool isLoaded = false;
        bool intakeInfo;

    public:
        Window(std::vector<std::shared_ptr<Window>> window,
               std::list<std::string> labels,
               std::string info,
               bool intake = true);

        explicit Window(const std::string& info, bool intake = true);

        void addPtr(const std::shared_ptr<Window>& window, const std::string& label);
        void addFunc(void (*fPtr)(const std::string&, unsigned int, unsigned int));
        void addInfo(const std::string& info, int color);
        void addInput(const std::string &labelVal, bool numOnly = false);
        void runFunction(unsigned int Pos) const;

        static std::shared_ptr<Window> ClickWindow(const std::shared_ptr<Window>& window, unsigned int pos);
        static void RefreshWindow(const std::shared_ptr<Window>& window);
        static void LoadWindow(const std::shared_ptr<Window>& window);
        static void UnloadWindow(const std::shared_ptr<Window>& window);
        static void Print(const std::string& str, int Color);
        static void Clear_screen(char fill = ' ');
        static InputTypes::Type handleWindowInput(const std::shared_ptr<Window> &window);

        static void generateWindow(const std::shared_ptr<Window> &window);
};
#endif //COLLEGEROI__WINDOW_H
