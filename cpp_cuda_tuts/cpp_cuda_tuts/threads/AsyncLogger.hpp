//
//  AsyncLogger.hpp
//  cpp_cuda_tuts
//
//  Created by Vengat Ramanan on 12/07/26.
//
#ifndef AsyncLogger_hpp
#define AsyncLogger_hpp

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <vector>

class AsyncLogger {
private:
    std::vector<std::string> m_queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool m_shutDownRequested = false;
    std::thread m_consumerThread;
    void processLogs();
public:
    AsyncLogger();
    ~AsyncLogger();
    void log(std::string msg);
};
#endif
