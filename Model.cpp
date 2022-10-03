#include "Model.h"

void CommandModel::begin(){
    if(!app->begin()){
            store->pull_commands();
    }
}

void CommandModel::end(){
    if(!app->end()){
        store->pull_commands();
    }
}

void CommandModel::add_command(const std::string& cur_command){
        if(app->add_command()){
            store->add_command(cur_command);
        }
        else{
            store->pull_commands();
            store->add_command(cur_command);
        }
}

void CommandModel::end_of_f(){
    if(!app->end_of_f()){
        store->pull_commands();
    }
}

CommandModel::CommandModel(Application* app, Storage* store):app(app),store(store){
        app->set_current(ICommmandHandlerPtr{new StaticState()});
}

CommandModel::CommandModel(int block_size){
        app = new Application(block_size);
        store = new Storage();
        app->set_current(ICommmandHandlerPtr{new StaticState()});
}

Storage* CommandModel::get_ref_store(){
    return store;
}

int CommandModel::setCommand(const std::string& cur_command){

        if(cur_command == std::string("{" )){
            begin();
            return 0;
        }

        if(cur_command == std::string("}")){
            end();
            return 0;
        }

        if(cur_command == std::string("EOF")){
            end_of_f();
            return 0;
        }

        add_command(cur_command);
                
        return 0;
}

std::string CommandModel::getCommand() const{
        return _command;
}