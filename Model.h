#pragma once 
#include<string>
#include<memory>
#include "Storage.h"
#include "Logger.h"
#include "CommandView.h"

class Application;

class ICommmandHandler{
public:
    virtual bool begin(Application* ) = 0;
    virtual bool end(Application*)=0;
    virtual bool add_command(Application*)=0;
    virtual bool end_of_f(Application*)=0;
};

using ICommmandHandlerPtr = std::unique_ptr<ICommmandHandler>;

class Application{
public:
    Application(int counter):counter(counter){}

    void set_current(ICommmandHandlerPtr hPtr){
        m_handler = std::move(hPtr);
    }
    bool begin(){
        return m_handler->begin(this);
    }
    bool end(){
        return m_handler->end(this);
    }
    bool end_of_f(){
        return m_handler->end_of_f(this);
    }
    bool add_command(){
        return m_handler->add_command(this);
    }

    int get_counter() const{
        return counter;
    }

private:
    ICommmandHandlerPtr m_handler;
    int counter;
};

class StaticState: public ICommmandHandler{
public:
    bool begin(Application* app) override;

    bool end(Application* ) override;

    bool add_command(Application* app) override;

    bool end_of_f(Application* ) override;


private:
    int counter = 0;
};

class DynamicState: public ICommmandHandler{
public:
    bool begin(Application*) override {
        ++counter;
        return true;
    }

    bool end(Application* app) override {
        --counter;
        if(counter==0){   
            app-> set_current(ICommmandHandlerPtr{new StaticState()});
            return false;
        }
        return true;
    }

    bool end_of_f(Application* app) override{
        return true;
    }

    bool add_command(Application*) override {
        return true;
    }

private:
    int counter = 1;
};

bool StaticState::begin(Application* app){
        app-> set_current(ICommmandHandlerPtr{new DynamicState()});
        return false;
    } 

bool StaticState::end(Application* ){ return true;}

bool StaticState::add_command(Application* app){
        ++counter;
        if(counter>app->get_counter()){
            counter = 0;
            return false;
        }
        return true;
    }

bool StaticState::end_of_f(Application*){
    return false;
}

class CommandModel{
private:
    std::string _command;
    
    Application* app;

    Storage* store;

    void begin(){
        if(!app->begin()){
            store->pull_commands();
        }
    }

    void end(){
        if(!app->end()){
            store->pull_commands();
        }
    }

    void add_command(const std::string& cur_command){
        if(app->add_command()){
            store->add_command(cur_command);
        }
        else{
            store->pull_commands();
            store->add_command(cur_command);
        }
    }

    void end_of_f(){
        if(!app->end_of_f()){
            store->pull_commands();
        }
    }
    
public:
    CommandModel(Application* app, Storage* store):app(app),store(store){
        app->set_current(ICommmandHandlerPtr{new StaticState()});
    }

    CommandModel(int block_size){
        app = new Application(block_size);
        store = new Storage();
        app->set_current(ICommmandHandlerPtr{new StaticState()});
    }

    Storage* get_ref_store(){
        return store;
    }

    int setCommand(const std::string& cur_command){

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


    std::string getCommand() const{
        return _command;
    }
};


int main(){

    CommandModel cm(3);

    CommandView cv(cm.get_ref_store());

    cm.setCommand("ddd");
    cm.setCommand("aaa");
    cm.setCommand("aaa");
    cm.setCommand("aaa");
    cm.setCommand("EOF");
    cm.setCommand("ytuyt");
    cm.setCommand("{");
    cm.setCommand("sqS");
    cm.setCommand("sqS");
    cm.setCommand("EOF");
    return 0;
}