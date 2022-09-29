#pragma once  

#include <fstream>
#include <chrono>
#include <string>
class Logger{
public:
    static Logger& getInstance(){
        static Logger instance;
        return instance;
    }

    void write(const std::string& message){
        if(!flag_opened_file){
            auto t = std::chrono::system_clock::now();
            file.open("file");
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