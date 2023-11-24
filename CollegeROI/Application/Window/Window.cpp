//
// Created by Neilf on 11/23/2023.
//

#include "Window.h"

#include <utility>

HANDLE Window::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Window::Print(const std::string &str, int Color) {
    SetConsoleTextAttribute(hConsole, Color);
    std::cout << str << std::endl;
    SetConsoleTextAttribute(hConsole, 15);
}

void Window::Clear_screen(char fill) {
    COORD tl = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(console, fill, cells, tl, &written);
    FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(console, tl);
}

void Window::LoadWindow(const std::shared_ptr<Window>& window) {
    if(window == nullptr){
        throw std::invalid_argument("Trying to load nonexistent window");
    }

    if(window->isLoaded){
        throw std::invalid_argument("Window is already loaded.");
    }

    Print(window->information, 15);
    std::cout << std::endl;

    std::list<Button>::iterator it;
    window->buttonVal = 1;

    for (it = window->buttons.begin(); it != window->buttons.end(); ++it){
        it->refresh(window->buttonVal, Window::hConsole);
    }

    window->isLoaded = true;

    int c = 0;
    bool clicked = false;

    while(!clicked)
    {
        c = 0;

        switch((c= getch())) {
            case KEY_UP:
                if(window->buttonVal > 1) {window->buttonVal--;}
                RefreshWindow(window);
                break;
            case KEY_DOWN:
                if(window->buttonVal < window->buttons.size()) {window->buttonVal++;}
                RefreshWindow(window);
                break;
            case ENTER:
                clicked = true;
                break;
            default:
                break;
        }
    }

    LoadWindow(Window::ClickWindow(window, window->buttonVal));
}

void Window::RefreshWindow(const std::shared_ptr<Window>& window) {
    if(window == nullptr){
        throw std::invalid_argument("Trying to load nonexistent window");
    }

    if(!window->isLoaded){
        throw std::invalid_argument("Window is not loaded");
    }

    Clear_screen();

    Print(window->information, 15);

    std::list<Button>::iterator it;
    for (it = window->buttons.begin(); it != window->buttons.end(); ++it){
        it->refresh(window->buttonVal, Window::hConsole);
    }
}

void Window::UnloadWindow(const std::shared_ptr<Window>& window) {
    if(window == nullptr){
        throw std::invalid_argument("Trying to unload nonexistent window");
    }

    if(!window->isLoaded){
        throw std::invalid_argument("Window is not loaded");
    }

    /*unsigned int length =window->buttons.size();
    for (int i = 0; i < length; ++i) {
        window->buttons.pop_front();
    }*/
    window->isLoaded = false;
    Window::Clear_screen();
}

Window::Window
(std::vector<std::shared_ptr<Window>> window,
 std::list<std::string> labels,
 std::string info, bool intake)
{
    if(labels.size() != window.size()){
        throw std::invalid_argument("Label and WindowPtr lengths not equal.");
    }

    this->windowPtr = std::move(window);
    this->information = std::move(info);
    this->intakeInfo = intake;

    for (int i = 0; i < windowPtr.size(); ++i) {
        auto tempButton = new Button(i, labels.back());
        labels.pop_back();
        buttons.push_back(*tempButton);
    }
}

void Window::addPtr(const std::shared_ptr<Window>& window, const std::string& label) {
    windowPtr.push_back(window);
    auto tempButton = new Button(windowPtr.size(), label);
    buttons.push_back(*tempButton);
}

Window::Window(const std::string& info, bool intake) {
    intakeInfo = intake;
    information = info;
}

std::shared_ptr<Window> Window::ClickWindow(const std::shared_ptr<Window> &window, unsigned int pos) {
    Window::UnloadWindow(window);
    return window->windowPtr[pos-1];
}

