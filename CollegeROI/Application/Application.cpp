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
        mainMenu->addPtr(instance->windows[1], "Load Colleges");
        mainMenu->addPtr(instance->windows[2], "Search Colleges");
        mainMenu->addPtr(instance->windows[3], "Add Colleges");

        AddColleges->addInput("Name:", false);
        AddColleges->addInput("Price:", true);
        AddColleges->addInput("Average Salary:", true);

        SearchColleges->addInput("Name:", false);

        AddColleges->addFunc(ROI::AddCollege);
        SearchColleges->addFunc(Application::LoadCollegeWindow);

        LoadColleges->addPtr(mainMenu, "Back");
        AddColleges->addPtr(mainMenu, "Back");
        SearchColleges->addPtr(mainMenu, "Back");

        GenerateCollegeButtons();

        Application::instance->win = Window::LoadWindow(mainMenu);
        while(Application::instance->win != nullptr){

            if(instance->win == instance->windows[0]){
                GenerateCollegeButtons();
            }


            Application::instance->win = Window::LoadWindow(Application::instance->win);
        }
    }

    return instance;
}

void Application::LoadCollegeWindow(const std::string & collegeName, unsigned int num1, unsigned int num2) {

    std::shared_ptr<College> col = ROI::LoadCollege(collegeName);

    if(col == nullptr){
        return;
    }
    std::array<unsigned int, 9> projections = ROI::GetInstance()->CalculateROIs(col);

    std::shared_ptr<Window> CollegeWindow =  std::make_shared<Window>(Window(col->GetName(), false));


    CollegeWindow->addInfo("Cost: " + std::to_string(col->GetCost()), 1);
    CollegeWindow->addInfo("Return: " + std::to_string(col->GetReturn()), 1);

    CollegeWindow->addInfo("", 15);

    CollegeWindow->addInfo("Projections:", 15);
    CollegeWindow->addInfo("Low interest rate and Low pay: " + std::to_string(projections[0]), 10);
    CollegeWindow->addInfo("Low interest rate and Medium pay: " + std::to_string(projections[1]), 14);
    CollegeWindow->addInfo("Low interest rate and High pay: " + std::to_string(projections[2]), 4);
    CollegeWindow->addInfo("Medium interest rate and Low pay: " + std::to_string(projections[3]), 10);
    CollegeWindow->addInfo("Medium interest rate and Medium pay: " + std::to_string(projections[4]), 14);
    CollegeWindow->addInfo("Medium interest rate and High pay: " + std::to_string(projections[5]), 4);
    CollegeWindow->addInfo("High interest rate and Low pay: " + std::to_string(projections[6]), 10);
    CollegeWindow->addInfo("High interest rate and Medium pay: " + std::to_string(projections[7]), 14);
    CollegeWindow->addInfo("High interest rate and High pay: " + std::to_string(projections[8]), 4);


    CollegeWindow->addPtr( instance->windows[2], "Back");

    Window::UnloadWindow(instance->windows[2], CollegeWindow);
    //Application::instance->win = CollegeWindow;
}

std::shared_ptr<Window> Application::GenerateCollegeButton(const std::string & collegeName) {
    std::shared_ptr<College> col = ROI::LoadCollege(collegeName);

    if(col == nullptr){
        return nullptr;
    }

    std::array<unsigned int, 9> projections = ROI::GetInstance()->CalculateROIs(col);

    std::shared_ptr<Window> CollegeWindow =  std::make_shared<Window>(Window(col->GetName(), false));

    CollegeWindow->reserveInfoSpace(14);
    CollegeWindow->addInfo("Cost: " + std::to_string(col->GetCost()), 1);
    CollegeWindow->addInfo("Return: " + std::to_string(col->GetReturn()), 1);

    CollegeWindow->addInfo("", 15);

    CollegeWindow->addInfo("Projections:", 15);

    if(!Application::instance->compact){
        CollegeWindow->addInfo("Low interest rate and Low pay: " + std::to_string(projections[0]), 10);
        CollegeWindow->addInfo("Low interest rate and Medium pay: " + std::to_string(projections[1]), 14);
        CollegeWindow->addInfo("Low interest rate and High pay: " + std::to_string(projections[2]), 4);
        CollegeWindow->addInfo("Medium interest rate and Low pay: " + std::to_string(projections[3]), 10);
        CollegeWindow->addInfo("Medium interest rate and Medium pay: " + std::to_string(projections[4]), 14);
        CollegeWindow->addInfo("Medium interest rate and High pay: " + std::to_string(projections[5]), 4);
        CollegeWindow->addInfo("High interest rate and Low pay: " + std::to_string(projections[6]), 10);
        CollegeWindow->addInfo("High interest rate and Medium pay: " + std::to_string(projections[7]), 14);
        CollegeWindow->addInfo("High interest rate and High pay: " + std::to_string(projections[8]), 4);
    }else{
        CollegeWindow->addInfo("Medium interest rate and Medium pay: " + std::to_string(projections[4]), 14);
    }
    CollegeWindow->addInfo("", 15);

    CollegeWindow->addInfo("Value: " +  std::to_string((int)std::floor(std::pow(90/projections[4],2))), 15);

    CollegeWindow->addPtr( instance->windows[1], "Back");
    return CollegeWindow;
}

bool Application::CompareFunction (const std::shared_ptr<College>& a, const std::shared_ptr<College>& b) {
    return a->GetName() < b->GetName();
}

void Application::GenerateCollegeButtons() {

    //might be a memory leak here check later with how shared pointer works

    Application::instance->windows[1] = nullptr;

    Application::instance->windows[1] = std::make_shared<Window>(Window("Load Colleges", true));
    Application::instance->windows[0]->updatePtr(Application::instance->windows[1], 0);

    std::vector<std::shared_ptr<College>> list = ROI::LoadAllColleges();

    std::sort(list.begin(),list.end(),Application::CompareFunction);
    for (const auto & i : list) {
        Application::instance->windows[1]->addPtr(Application::instance->GenerateCollegeButton(i->GetName()), i->GetName());
    }

    Application::instance->windows[1]->addPtr(Application::instance->windows[0], "Back");
}

