#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t num) {
    for(int i = 0; i < num; ++i) {
        workers.emplace_back(
                            [this]() {
                                while(true) {
                                    std::function<void()> task;
                                    {
                                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                                        this->cv.wait(lock, [this]() {return this->stop || !this->tasks.empty();});
                                        
                                        if(this->stop && this->tasks.empty()) return;
                                        
                                        task = std::move(this->tasks.front());
                                    }
                                    task();
                                }
                            });
    }
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        stop = true;
    }
    
    cv.notify_all();
    
    for(std::thread &worker : workers){
        if (worker.joinable()) {
            worker.join();
        }
    }
}

int ThreadPool::heavyCalculation(int factor) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return factor * 2;
}

int main() {
    
    ThreadPool pool{4};
    
    std::future<int> result1 = pool.enqueue(&ThreadPool::heavyCalculation,&pool, 50);
//    int x = 50;
//    std::future<int> result1 = pool.enqueue([&pool]() {return pool.heavyCalculation(50);});
    
    std::future<double> result2 = pool.enqueue([&pool](){return 3.14159 * 2;});
    
    std::cout << "Result1: " << result1.get()<<std::endl;
    std::cout << "Result2: " << result2.get()<<std::endl;
    
    EXIT_SUCCESS;
}
