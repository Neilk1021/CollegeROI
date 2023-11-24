//
// Created by Neil Ketteringham on 11/22/23.
//

#include "Application.h"

Application::Application() {

    roiInstance = ROI::GetInstance();

    /*Window::Print("College ROI Calculator", 15);
    Window::Print("-Neil Ketteringham CC-2023", 1);
    std::cin.get();
    Window::Clear_screen();

    Window::Print("What would you like to do?", 15);*/

    std::shared_ptr<Window> mainMenu =  std::make_shared<Window>(Window("Main Menu", false));
    std::shared_ptr<Window> LoadColleges =  std::make_shared<Window>(Window("Load Colleges", true));
    std::shared_ptr<Window> AddColleges =  std::make_shared<Window>(Window("Add Colleges", true));

    mainMenu->addPtr(LoadColleges, "Load Colleges");
    mainMenu->addPtr(AddColleges, "Add Colleges");

    LoadColleges->addPtr(mainMenu, "Back");
    AddColleges->addPtr(mainMenu, "Back");
    Window::LoadWindow(mainMenu);


}

