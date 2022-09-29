#pragma once 
#include<string>
#include<memory>
#include "Storage.h"
#include "Logger.h"

class Application;

class ICommmandHandler{
public:
    virtual void begin(Application* ) = 0;
    virtual void end(Application*)=0;
    virtual void add_command(Application*)=0;
};

using ICommmandHandlerPtr = std::unique_ptr<ICommmandHandler>;

class Application{
public:
    Application(int counter,Storage* store):counter(counter),store(store){}

    void set_current(ICommmandHandlerPtr hPtr){
        m_handler = std::move(hPtr);
    }
    void begin(){
        m_handler->begin(this);
    }
    void end(){
        m_handler->end(this);
    }
    void add_command(){
        m_handler->add_command(this);
    }

    int get_counter() const{
        return counter;
    }

private:
    ICommmandHandlerPtr m_handler;
    int counter;
    Storage* store;
};

class DynamicState: public ICommmandHandler{
public:
    void begin(Application*) override {
        ++counter;
    }

    void end(Application* app) override {
        --counter;
        if(counter==0){
        app-> set_current(ICommmandHandlerPtr{new StaticState()});
        }
    }

    void add_command(Application*) override {

    }

private:
    int counter = 0;
};

class StaticState: public ICommmandHandler{
public:
    void begin(Application* app) override {
        app-> set_current(ICommmandHandlerPtr{new DynamicState()});
    }

    void end(Application* ) override {

    }

    void add_command(Application* app) override {
        ++counter;
        if(counter == app->get_counter()){
            //app->store->add_command
        }
        
    }


private:
    int counter = 0;
};

class CommandModel{
private:
    std::string _command;

    void start(){

    }

    void end(){

    }

    void add_command(const std::string& _command){

    }    

public:
    int setCommand(const std::string& cur_command){

        if(cur_command == std::string("{" )){
            start();
            return 0;
        }

        if(cur_command == std::string("}")){
            end();
            return 0;
        }

        Logger::getInstance().write(cur_command);
        

        return 0;
    }


    std::string getCommand() const{
        return _command;
    }
};

