#pragma once

#include "Model.h"

class Controller{
public:
    Controller(std::unique_ptr<CommandModel> mdl):mdl(std::move(mdl)){}

   void start(){
    std::string temp;
    while(std::getline(std::cin,temp)){
        mdl.get()->setCommand(std::move(temp));
    }
    mdl.get()->end_of_f();
}
private:
std::unique_ptr<CommandModel> mdl;
};