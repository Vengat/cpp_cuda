#ifndef ThreadCV_hpp
#define ThreadCV_hpp

#include <string>
#include <thread>
#include <iostream>
#include <functional>
#include <mutex>
#include <condition_variable>

class ThreadCV {
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool threadAWork = false;
    
public:
    void ThreadPrintApple();
    void ThreadPrintOrange();
    
};
#endif

