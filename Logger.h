#pragma once  

#include <fstream>
#include <chrono>

class Logger{
public:
    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    void info(const std::string& message){
        if(!flag_opened_file){
            auto t = std::chrono::system_clock::now();
            file.open(static_cast<std::string>(std::chrono::system_clock::now()));
        }
        file << message << "\n";
    }

    void close_log(){
        if(flag_opened_file){
            file.close();
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