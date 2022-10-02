#pragma once

#include "Model.h"

class Controller{
public:
    Controller(CommandModel* mdl):mdl(mdl){}

    void start(){
        std::string temp;
        while(temp!="EOF"){
            std::cin>>temp;
            mdl->setCommand(std::move(temp));
        }
    }

private:
    CommandModel* mdl;
};