#include "Controller.h"

Controller::Controller(CommandModel* mdl):mdl(mdl){}

void Controller::start(){
    std::string temp;
    while(temp!="EOF"){
        std::cin>>temp;
        mdl->setCommand(std::move(temp));
    }
}