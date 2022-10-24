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
    std::ostream& _oFileMetricsOut){

    }

  ~Context(){}

  void ProccessBuffer(const char* a_Buffer, std::size_t a_szSize){
    
  }

private:
  void Procces();
  void JoinThred();
  
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