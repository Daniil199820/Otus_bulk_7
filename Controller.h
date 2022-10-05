#pragma once

#include "Model.h"

class Controller{
public:
    Controller(CommandModel* mdl):mdl(mdl){}

   void start(){
    std::string temp;
    while(std::getline(std::cin,temp)){
        mdl->setCommand(std::move(temp));
    }
    mdl->end_of_f();
}
private:
    CommandModel* mdl;
};