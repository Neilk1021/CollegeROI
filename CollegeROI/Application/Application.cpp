//
// Created by Neil Ketteringham on 11/22/23.
//

#include "Application.h"

Application* Application::instance = nullptr;;
Application *Application::GetInstance() {
    if(instance == nullptr){
        instance = new Application();
        instance->roiInstance = ROI::GetInstance();

        Window::Print("College ROI Calculator", 15);
        Window::Print("-Neil Ketteringham CC-2023", 1);
        std::cin.get();
        Window::Clear_screen();

        std::shared_ptr<Window> mainMenu =  std::make_shared<Window>(Window("College ROI Calculator", false));
        std::shared_ptr<Window> LoadColleges =  std::make_shared<Window>(Window("Load Colleges", true));
        std::shared_ptr<Window> SearchColleges =  std::make_shared<Window>(Window("Search Colleges", true));
        std::shared_ptr<Window> AddColleges =  std::make_shared<Window>(Window("Add Colleges", true));

        instance->windows.push_back(mainMenu);
        instance->windows.push_back(LoadColleges);
        instance->windows.push_back(SearchColleges);
        instance->windows.push_back(AddColleges);

        mainMenu->addInfo("-Neil Ketteringham CC-2023", 1);
        mainMenu->addPtr(LoadColleges, "Load Colleges");
        mainMenu->addPtr(SearchColleges, "Search Colleges");
        mainMenu->addPtr(AddColleges, "Add Colleges");

        AddColleges->addInput("Name:", false);
        AddColleges->addInput("Price:", true);
        AddColleges->addInput("Average Salary:", true);

        SearchColleges->addInput("Name:", false);

        AddColleges->addFunc(ROI::AddCollege);
        SearchColleges->addFunc(Application::GenerateCollegeWindow);

        LoadColleges->addPtr(mainMenu, "Back");
        AddColleges->addPtr(mainMenu, "Back");
        SearchColleges->addPtr(mainMenu, "Back");

        Window::LoadWindow(mainMenu);
    }

    return instance;
}

void Application::GenerateCollegeWindow(const std::string & collegeName, unsigned int num1, unsigned int num2) {

    std::shared_ptr<College> col = ROI::LoadCollege(collegeName);

    if(col == nullptr){
        return;
    }

    std::shared_ptr<Window> CollegeWindow =  std::make_shared<Window>(Window(col->GetName(), false));
    CollegeWindow->addInfo("Cost: " + std::to_string(col->GetCost()), 1);
    CollegeWindow->addInfo("Return: " + std::to_string(col->GetReturn()), 1);
    CollegeWindow->addPtr( instance->windows[2], "Back");

    Window::UnloadWindow(instance->windows[2]);
    Window::LoadWindow(CollegeWindow);
}

