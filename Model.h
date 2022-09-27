#pragma once 
#include<string>
#include<memory>
class Application;

class ICommmandHandler{
public:
    virtual void begin_state(Application* ) = 0;
    virtual void end_state(Application*)=0;
    virtual void add_command_state(Application*)=0;
};

using ICommmandHandlerPtr = std::unique_ptr<ICommmandHandler>;

class Application{
public:
    Application();

    void set_current(ICommmandHandlerPtr hPtr){
        m_handler = std::move(hPtr);
    }
    void begin_state(){
        m_handler->begin_state(this);
    }
    void end_state(){
        m_handler->end_state(this);
    }
    void add_command_state(){
        m_handler->add_command_state(this);
    }

private:
    ICommmandHandlerPtr m_handler;
};

class DynamicState: public ICommmandHandler{
public:
    void begin_state(Application*) override {
        ++counter;
    }

    void end_state(Application){
        --counter;
    }

    void add_command_state(){

    }

private:
    int counter = 0;
};

class StaticState: public ICommmandHandler{
public:
    void begin_state(Application*) override {
        
    }

    void end_state(Application){

    }

    void add_command_state(){
        ++counter;
        if(counter)
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

        _command = cur_command;
        add_command(cur_command);

        return 0;
    }


    std::string getCommand() const{
        return _command;
    }
};

