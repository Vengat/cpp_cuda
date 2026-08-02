#ifndef JThreadTuts_hpp
#define JThreadTuts_hpp

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <future>
#include <chrono>

class JThreadTuts {
private:
    std::mutex mtx;
    bool signalSent = false;
public:
    JThreadTuts();
    ~JThreadTuts();
    void printSequence(std::stop_token st);
};
#endif
