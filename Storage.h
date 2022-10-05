#pragma once

#include<iostream>
#include <string>
#include <deque>
#include "Observer.h"
#include "Logger.h"
#include <chrono>

struct Element{
std::string _cmd;
int64_t _time;
};

class Storage:public Observable{
public:
    void add_command(const std::string& _command){
        const auto now = std::chrono::system_clock::now();
        const auto now_ns = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        container_commands.push_back({_command,now_ns.count()});
    }   

    void pull_commands(){
        notifyUpdate();
        container_commands.clear();   
    }
    
    std::deque<Element> container_commands; 
};