//
//  AsyncLogger.cpp
//  cpp_cuda_tuts
//
//  Created by Vengat Ramanan on 12/07/26.
//
#include "AsyncLogger.hpp"

void AsyncLogger::processLogs() {
    while(true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        cv.wait(lock, [this](){
            return !m_queue.empty() || m_shutDownRequested;
        });
        
        if (!m_queue.empty()) {
            for(const std::string& msg : m_queue) {
                std::cout << "[LOG]: " << msg << std::endl;
            }
            m_queue.clear();
        }
        
        if (m_queue.empty() && m_shutDownRequested) {
            break;
        }
    }
}

AsyncLogger::AsyncLogger() {
    m_consumerThread = std::thread(&AsyncLogger::processLogs, this);
}

AsyncLogger::~AsyncLogger() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        m_shutDownRequested = true;
    }
    cv.notify_one();
    if (m_consumerThread.joinable()) {
        m_consumerThread.join();
    }
    
}

void AsyncLogger::log(std::string msg) {
    std::lock_guard<std::mutex> lock(mtx);
    m_queue.push_back(msg);
    cv.notify_one();
}

int main() {
    AsyncLogger logger;
    
    std::thread t1(&AsyncLogger::log, &logger, "Thread~1 starting calculation...");
    std::thread t2(&AsyncLogger::log, &logger, "Thread~2 starting calculation...");
    std::thread t3(&AsyncLogger::log, &logger, "Thread~3 starting calculation...");
    
    t1.join();
    t2.join();
    t3.join();
    
    return EXIT_SUCCESS;
}
