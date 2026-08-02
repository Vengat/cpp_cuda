#ifndef ThreadPool_hpp
#define ThreadPool_hpp

#include <iostream>
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>

class ThreadPool {
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable cv;
    bool stop = false;
    
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();
    
    int heavyCalculation(int factor);
    
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<std::invoke_result_t<F, Args...>> {
        using return_type = std::invoke_result_t<F, Args...>;
        
        auto task = std::make_shared<std::packaged_task<std::invoke_result_t<F, Args...>>>(
                                                        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
                    );
        
        std::future<return_type> res = task -> get_future();
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            tasks.emplace([task](){*task();});
        }
        cv.notify_one();
        return res;
    }
    
    
};
#endif
