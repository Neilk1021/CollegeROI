//
// Created by Neil Ketteringham on 11/22/23.
//

#ifndef COLLEGEROI__APPLICATION_H
#define COLLEGEROI__APPLICATION_H
#include "../ROI-Calculator/ROI.h"
#include "./Window/Window.h"
#include <string>
#include <algorithm>
#include <cmath>

class Application {
    private:
        ROI* roiInstance;
        std::vector<std::shared_ptr<Window>> windows;
        Application() {};

        const bool compact = false;
    protected:
        std::shared_ptr<Window> win;
        std::vector<std::shared_ptr<Window>> tempWindows;
        static Application* instance;
        static std::shared_ptr<Window> GenerateCollegeButton(const std::string&);
        static void GenerateCollegeButtons();
    public:
        static void LoadCollegeWindow(const std::string&, unsigned int, unsigned  int);
        Application(Application &other) = delete;
        static Application *GetInstance();

        static bool CompareFunction(const std::shared_ptr<College>&, const std::shared_ptr<College>&);
};

#endif //COLLEGEROI__APPLICATION_H
