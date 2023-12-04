//
// Created by Neilf on 11/23/2023.
//

#include "Window.h"

#include <utility>

#ifdef _WIN32
HANDLE Window::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Window::Print(const std::string &str, int Color) {
    SetConsoleTextAttribute(hConsole, Color);
    std::cout << str << std::endl;
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
#endif
#ifdef __APPLE__
void Window::Print(const std::string &str, int Color) {
    const std::string & concat = "\r\x1b[" + std::to_string(Color) +"m " + str + " \x1b[0m";
    std::cout << concat << std::endl;
}

void Window::Clear_screen(char fill) {
    system("clear");
}
#endif

std::shared_ptr<Window> Window::LoadWindow(const std::shared_ptr<Window>& window) {
    if(window == nullptr){
        throw std::invalid_argument("Trying to load nonexistent window");
    }
    if(window->isLoaded){
        throw std::invalid_argument("Window is already loaded.");
    }

    window->buttonVal = 1;
    window->isLoaded = true;

    generateWindow(window);
    InputTypes::Type _type;

    do{
        _type = handleWindowInput(window);
        if(_type != InputTypes::Type::WindowLoader){ Window::ClickWindow(window, window->buttonVal); }
    }while (window->isLoaded && _type != InputTypes::Type::WindowLoader);

    if(!window->isLoaded){
        return window->nextWin;
    }

    return Window::ClickWindow(window, window->buttonVal);

    //LoadWindow(Window::ClickWindow(window, window->buttonVal));
}

#ifdef _WIN32
InputTypes::Type Window::handleWindowInput(const std::shared_ptr<Window> &window) {
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
                if(window->buttonVal < window->inputs.size()) {window->buttonVal++;}
                RefreshWindow(window);
                break;
            case ENTER:
                clicked = true;
                break;
            case BACKSPACE:
                if(window->inputs[window->buttonVal - 1]->getType() == InputTypes::Type::Keyboard){
                    InputField * convert = window->inputs[window->buttonVal - 1];
                    auto text = dynamic_cast<TextInput*>(convert);
                    text->deleteChar();
                }
                RefreshWindow(window);
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            default:

                if(!std::isalnum(c) && c != 32){break;}

                if(window->inputs[window->buttonVal - 1]->getType() == InputTypes::Type::Keyboard){
                    InputField * convert = window->inputs[window->buttonVal - 1];
                    auto text = dynamic_cast<TextInput*>(convert);

                    if(text->isNumOnly() && !std::isdigit(c) || !text->isNumOnly() && (!std::isalpha(c) && c != 32)){
                        break;
                    }

                    text->addChar((char)c);
                }
                RefreshWindow(window);
                break;
        }
    }
    return window->inputs[window->buttonVal - 1]->getType();

}
#endif
#ifdef __APPLE__
InputTypes::Type Window::handleWindowInput(const std::shared_ptr<Window> &window) {
    bool clicked = false;
    int ch;

    /* Curses Initialisations */
    initscr();                  /* curses initialization */
    keypad(stdscr, TRUE);       /* enable KEY_UP/KEY_DOWN/KEY_RIGHT/KEY_LEFT */
    noecho();                   /* prevent displaying if other keys */

    while (!clicked) {
        switch (ch = getch()) {
            case KEY_UP:
                if(window->buttonVal > 1) {window->buttonVal--;}
                RefreshWindow(window);
                break;
            case KEY_DOWN:
                if(window->buttonVal < window->inputs.size()) {window->buttonVal++;}
                RefreshWindow(window);
                break;
            case KEY_RIGHT:
                break;
            case KEY_LEFT:
                break;
            case 10:
                clicked = true;
                break;
            case KEY_BACKSPACE:
            case 127:
            case 8:
                if(window->inputs[window->buttonVal - 1]->getType() == InputTypes::Type::Keyboard){
                    InputField * convert = window->inputs[window->buttonVal - 1];
                    auto text = dynamic_cast<TextInput*>(convert);
                    text->deleteChar();
                }
                RefreshWindow(window);
                break;
            default:
                if(!std::isalnum(ch) && ch != 32){break;}

                if(window->inputs[window->buttonVal - 1]->getType() == InputTypes::Type::Keyboard){
                    InputField * convert = window->inputs[window->buttonVal - 1];
                    auto text = dynamic_cast<TextInput*>(convert);

                    if(text->isNumOnly() && !std::isdigit(ch) || !text->isNumOnly() && (!std::isalpha(ch) && ch != 32)){
                        break;
                    }

                    text->addChar((char)ch);
                }
                RefreshWindow(window);
                break;
        }
    }
    return window->inputs[window->buttonVal - 1]->getType();

}
#endif

void Window::RefreshWindow(const std::shared_ptr<Window>& window) {
    if(window == nullptr){
        throw std::invalid_argument("Attempted to refresh Window. Trying to load nonexistent window");
    }
    if(!window->isLoaded){
        throw std::invalid_argument("Attempted to refresh Window. Window is not loaded");
    }

    Clear_screen();
    generateWindow(window);

}
#ifdef _WIN32
void Window::generateWindow(const std::shared_ptr<Window> &window) {
    Print(window->information, 15);

    for (int i = 0; i < window->additionalInfo.size(); i++) {
        Print(window->additionalInfo.at(i).Info, window->additionalInfo[i].Color);
    }

    std::cout << std::endl;

    for (int i = 0; i < window->inputs.size(); ++i) {
        InputField * convert = window->inputs[i];

        TextInput * textI;
        Button * button;

        InputTypes::Type type = convert->getType();
        switch (type) {
            case InputTypes::Keyboard:
                textI = dynamic_cast<TextInput*>(convert);
                textI->refresh(window->buttonVal, hConsole);
                break;
            default:
                button = dynamic_cast<Button*>(convert);
                button->refresh(window->buttonVal, hConsole);
                break;
        }
    }
}
#endif

#ifdef __APPLE__
void Window::generateWindow(const std::shared_ptr<Window> &window) {
    Print(window->information, 15);

    for (int i = 0; i < window->additionalInfo.size(); i++) {
        Print(window->additionalInfo.at(i).Info, window->additionalInfo[i].Color);
    }

    std::cout << std::endl;

    for (int i = 0; i < window->inputs.size(); ++i) {
        InputField * convert = window->inputs[i];

        TextInput * textI;
        Button * button;

        InputTypes::Type type = convert->getType();
        switch (type) {
            case InputTypes::Keyboard:
                textI = dynamic_cast<TextInput*>(convert);
                textI->refresh(window->buttonVal);
                break;
            default:
                button = dynamic_cast<Button*>(convert);
                button->refresh(window->buttonVal);
                break;
        }
    }
}
#endif

std::shared_ptr<Window> Window::ClickWindow(const std::shared_ptr<Window> &window, unsigned int pos) {

    switch ( window->inputs[pos - 1]->getType()) {
        case InputTypes::WindowLoader:
            Window::UnloadWindow(window);
            if(window->windowPtr[pos-1] == nullptr){
                throw std::invalid_argument("Tried to load non-window");
            }
            return window->windowPtr[pos-1];
        case InputTypes::Action:
            window->runFunction(pos);
            return nullptr;
        case InputTypes::Keyboard:
            break;
    }

    return nullptr;
}

void Window::UnloadWindow(const std::shared_ptr<Window>& window, const std::shared_ptr<Window>& newWindow) {
    if(window == nullptr){
        throw std::invalid_argument("Trying to unload nonexistent window");
    }

    if(!window->isLoaded){
        throw std::invalid_argument("Tried to unload unloaded window.");
    }

    window->nextWin = newWindow;
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
        auto tempButton = new Button(InputTypes::Action, i, labels.back());
        labels.pop_back();
        inputs.push_back(tempButton);
    }
}

Window::Window(const std::string& info, bool intake) {
    intakeInfo = intake;
    information = info;
}

void Window::addPtr(const std::shared_ptr<Window>& window, const std::string& label) {
    windowPtr.push_back(window);
    auto tempButton = new Button(InputTypes::WindowLoader, windowPtr.size(), label);
    inputs.push_back(tempButton);
}

void Window::addFunc(void (*fPtr)(const std::string &, unsigned int, unsigned int)) {
    windowPtr.push_back(nullptr);
    auto tempButton = new Button(InputTypes::Action, windowPtr.size(), "Submit");
    tempButton->addFunction(fPtr);
    inputs.push_back(tempButton);
}

void Window::addInfo(const std::string &info, int color) {
    additionalInfo.push_back({color, info});
}

void Window::addInput(const std::string &labelVal, bool numOnly) {
    windowPtr.push_back(nullptr);
    auto tempInput = new TextInput(InputTypes::Keyboard, windowPtr.size(), labelVal, numOnly);
    inputs.push_back(tempInput);
}

//Need to add variable params
void Window::runFunction(unsigned int pos) const {
    InputField * convert = inputs[pos - 1];
    auto button = dynamic_cast<Button*>(convert);

    std::vector<std::string> data(3);

    int i = 0;
    for (auto input : inputs) {
        if(input->getType() == InputTypes::Type::Keyboard){
            auto text = dynamic_cast<TextInput*>(input);
            data[i] = (text->getInfo());
            i++;
        }
    }
    if(data[1].empty()){
        data[1] = "0";
        data[2] = "0";
    }else if(data[2].empty()){
        data[2] = "0";
    }
    button->runFunction(data);
}

void Window::updatePtr(const std::shared_ptr<Window> &window, unsigned int Pos) {
    windowPtr[Pos] = window;
}

void Window::reserveInfoSpace(unsigned int size) {
    additionalInfo.reserve(size);
}


