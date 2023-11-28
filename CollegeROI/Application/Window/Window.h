//
// Created by Neilf on 11/23/2023.
//

#ifndef COLLEGEROI__WINDOW_H
#define COLLEGEROI__WINDOW_H
#include <memory>
#include <list>
#include <string>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

#include <iostream>
#include <stdexcept>
#include <iostream>
#include <stdio.h>
#include <termios.h>
#include "../Button/Button.h"
#include <vector>
#include "../InputField/InputField.h"
#include "../TextInput/TextInput.h"
#include <algorithm>

#ifdef _WIN32
    #define KEY_UP 72
    #define KEY_DOWN 80
    #define KEY_LEFT 75
    #define KEY_RIGHT 77
    #define ENTER 13
    #define BACKSPACE 8
#endif

#ifdef __APPLE__
    #define KEY_UP 65
    #define KEY_DOWN  66
    #define KEY_LEFT  67
    #define KEY_RIGHT  68
    #define ENTER 13
    #define BACKSPACE 8
#endif

struct subHeading{
    int Color;
    std::string Info;
};

class Window {
    private:

    #ifdef _WIN32
            static HANDLE hConsole;
    #endif
        std::vector<std::shared_ptr<Window>> windowPtr;
        std::vector<InputField*> inputs;
        std::vector<subHeading> additionalInfo;

        std::string information;

        unsigned int buttonVal = 1;
        bool isLoaded = false;
        bool intakeInfo;

        const bool macVersion  = false;

    public:
        std::shared_ptr<Window> nextWin = nullptr;
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
        void updatePtr(const std::shared_ptr<Window>& window, unsigned int Pos);
        void reserveInfoSpace(unsigned int size);
        static std::shared_ptr<Window> ClickWindow(const std::shared_ptr<Window>& window, unsigned int pos);
        static void RefreshWindow(const std::shared_ptr<Window>& window);
        static std::shared_ptr<Window> LoadWindow(const std::shared_ptr<Window>& window);
        static void UnloadWindow(const std::shared_ptr<Window>& window, const std::shared_ptr<Window>& newWindow = nullptr);
        static void Print(const std::string& str, int Color);
        static void Clear_screen(char fill = ' ');
        static InputTypes::Type handleWindowInput(const std::shared_ptr<Window> &window);

        static void generateWindow(const std::shared_ptr<Window> &window);
};
#endif //COLLEGEROI__WINDOW_H
