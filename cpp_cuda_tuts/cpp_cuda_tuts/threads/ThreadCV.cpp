#include "ThreadCV.hpp"

void ThreadCV::ThreadPrintApple() {
    std::lock_guard<std::mutex> lck(mtx);
    {
        std::cout << "Apple" << std::endl;
        threadAWork = true;
    }
    cv.notify_one();
}

void ThreadCV::ThreadPrintOrange() {
    std::unique_lock<std::mutex> lock(mtx);
    
    cv.wait(lock, [this](){return threadAWork;});
    
    std::cout << "Orange" << std::endl;
}

int main() {
    ThreadCV tcv{};
    std::thread t1(&ThreadCV::ThreadPrintApple, &tcv);
    std::thread t2(&ThreadCV::ThreadPrintOrange, &tcv);
    
    t1.join();
    t2.join();
    
    EXIT_SUCCESS;
}
