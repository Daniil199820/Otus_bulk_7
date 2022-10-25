#include <iostream>
#include <sstream>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Model.h"
#include "CommandView.h"


class Context
{
public:
  Context(std::size_t _BlockSize,
    std::ostream& _osLoggerOut, 
    std::ostream& _osMainMetricsOut, 
    std::ostream& _osLogMetricsOut, 
    std::ostream& _oFileMetricsOut)
    :m_bDone{false},m_thread{&Context::ParceBuffer,this}{
        
    }
    

  ~Context(){
      m_bDone = true;
      m_streamCheck.notify_all();
      if (m_thread.joinable()){
        m_thread.join();
      }
  }

  void SetBuffer(const char* a_Buffer, std::size_t a_szSize){
    {std::unique_lock<std::mutex> lock(m_streamLock);
      _ssInputStream.write(a_Buffer, a_szSize);
    }

    m_bNotified = true;
    m_streamCheck.notify_one();
    
  }

  void ParceBuffer(){
    while(!m_bDone){
      std::unique_lock<std::mutex> locker(m_streamLock);
      m_streamCheck.wait(locker,[&](){return m_bNotified || m_bDone;});
      std::string tempLine;
      while( std::getline(_ssInputStream,tempLine)){
        m_pCommander->setCommand(std::move(tempLine));
      }
      m_pCommander->end_of_f();
      _ssInputStream.clear();
      m_bNotified = false;
    }
  }

private:
  std::shared_ptr<CommandModel> m_pCommander;
  std::shared_ptr<CommandView> m_pExecuter;
  std::shared_ptr<Logger> m_pLogger;

  std::stringstream _ssInputStream;

  std::atomic<bool> m_bDone;
  std::atomic<bool> m_bNotified;
  std::thread m_thread;
  std::mutex m_streamLock;
  std::condition_variable m_streamCheck;
};