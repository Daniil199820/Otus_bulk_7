#pragma once  

#include <fstream>
#include <string>

class Logger{
public:
    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    void open_log(const std::string& filename){
        close_log();
        file.open(filename);
        flag_opened_file = true;
    }

    void write(const std::string& message){
        if(flag_opened_file){
            file << message << "\n";
        }
    }

    void close_log(){
        if(flag_opened_file){
            file.close();
            flag_opened_file = false;
        }
    }

private:
    std::ofstream file;
    bool flag_opened_file = false;
    
    Logger() = default;
    Logger(const Logger& root) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&& root) = delete;
    Logger& operator=(Logger&&) = delete;

    ~Logger() = default;


};