#pragma once 

#include "Observer.h"
#include "Storage.h"
#include "Logger.h"
#include <iostream>
class CommandView:public Observer{
public: 
    CommandView(Storage* store):store(store){
        store->addObserver(this);
    }

    void update() override{

        decltype(store->container_commands) cotr = std::move(store->container_commands);

        if(cotr.size()>=1){
            std::cout<<"bulk: ";
            std::cout<<cotr[0]._cmd;
            Logger::getInstance().open_log(cotr[0]._cmd
             + std::to_string(cotr[0]._time));
            Logger::getInstance().write(cotr[0]._cmd); 
        
        for(size_t i=1;i<cotr.size();++i){
            std::cout<<", ";
            std::cout<<cotr[i]._cmd;
            Logger::getInstance().write(cotr[i]._cmd);
        }
            Logger::getInstance().close_log();
            std::cout<< '\n';
        }
    }
private:
    Storage* store;
};