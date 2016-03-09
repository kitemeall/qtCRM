#include "application.h"

void Application::showGroupWindow(){
    if(!groupFrom)
        Application::groupFrom = new GroupForm;
    groupFrom->show();
}
