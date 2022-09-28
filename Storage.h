#pragma once
#include <string>
#include<vector>

class Storage{
private:
    std::vector<std::string> container_commands;
public:
    void add_command(const std::string& _command){
        container_commands.push_back(_command);
    }   

    void pull_commands(){
        
    } 
};