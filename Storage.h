#pragma once
#include <string>
#include<deque>

class Storage{
private:
    std::deque<std::string> container_commands;
public:
    void add_command(const std::string& _command){
        container_commands.push_back(_command);
    }   

    void pull_commands(){
        
    } 
};