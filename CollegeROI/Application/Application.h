//
// Created by Neil Ketteringham on 11/22/23.
//

#ifndef COLLEGEROI__APPLICATION_H
#define COLLEGEROI__APPLICATION_H
#include "../ROI-Calculator/ROI.h"
#include "./Window/Window.h"
#include <string>
class Application {
    private:
        ROI* roiInstance;
        std::vector<std::shared_ptr<Window>> windows;
        Application() {};
    protected:
        static Application* instance;
    public:
        Application(Application &other) = delete;
        static Application *GetInstance();
        static void GenerateCollegeWindow(const std::string&, unsigned int, unsigned  int);
};

#endif //COLLEGEROI__APPLICATION_H
