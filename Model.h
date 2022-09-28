#pragma once 
#include<string>
#include<memory>
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
    Application(int counter):counter(counter){}

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
};

class DynamicState: public ICommmandHandler{
public:
    void begin(Application*) override {
        ++counter;
    }

    void end(Application* app) override {
        --counter;
        if(counter==0){
        app-> set_current(ICommmandHandlerPtr{new DynamicState()});
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
        if(counter == app->get_counter());
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

/*
  class LoginHandler : public ICommandHandler {
    public:
        void login(Application *) override {
            std::cout << "already login" << std::endl;
        }
        void do_it(Application *m) override {
            std::cout << "success" << std::endl;
            /*std::cout << "start work" << std::endl;
            m->set_current(ICommandHandlerPtr{new InProgressHandler()});*/
        }
        void logout(Application *m) override;
    };

    class AnonymousHandler : public ICommandHandler {
    public:
        void login(Application *m) override {
            std::cout << "login success" << std::endl;
            m->set_current(ICommandHandlerPtr{new LoginHandler()});  // Чтобы переключить состояние, нужно подать другой объект-состояние в контекст.
        }
        void do_it(Application *) override {
            std::cout << "anonymous error" << std::endl;
        }
        void logout(Application *m) override {
            std::cout << "already logout" << std::endl;
        }
    };

    /*class InProgressHandler : public ICommandHandler {
    public:
        void login(Application *) override {
            std::cout << "already login" << std::endl;
        }
        void do_it(Application *m) override {
            std::cout << "stop work" << std::endl;
            m->set_current(ICommandHandlerPtr{new LoginHandler()});
        }
        void logout(Application *) override {
            std::cout << "error: stop working first" << std::endl;
        }
    };*/

    void LoginHandler::logout(Application *m) {
        /*
        Состояние получает указатель на объект контекста. 
        Через него не только можно получать из контекста нужную информацию, но и осуществлять смену его состояния.
        */
        std::cout << "work as anonymous" << std::endl;
        m->set_current(ICommandHandlerPtr{new AnonymousHandler()});
    }

    Application::Application() {
        m_handler = ICommandHandlerPtr{new AnonymousHandler()};
        std::cout << std::endl;
    }

    // Переходы сложно отследить!

    void example() {
        std::cout << "pattern::example" << std::endl;

        Application app;

        app.do_it();
        app.logout();
        app.login();
        app.do_it();
        app.login();
        app.logout();

        std::cout << std::endl << std::endl;
    }
}

*/