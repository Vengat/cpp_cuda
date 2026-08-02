#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

/*
 Here is how std::atomic_flag handles this:

 lock.test_and_set(): Atomically sets the flag to true and returns the previous value. If it returns true, it means another thread already held the lock, so we keep looping. If it returns false, we successfully acquired the lock!

 lock.clear(): Atomically resets the flag back to false, releasing the lock for other threads.
 */

//standard atomic flag used for lock free primitive synchronization
std::atomic_flag spinlock = ATOMIC_FLAG_INIT;

void spin_lock() {
    //Busy wait (spin) until test_and_set returns false (meaning we grabbed the lock)
    while (spinlock.test_and_set(std::memory_order_acquire)) {
        //Yield execution briefly so the cpu core isnt completely starved
        std::this_thread::yield();
    }
}

void spin_unlock() {
    //Atomically clear the flag to release the lock
    spinlock.clear(std::memory_order_release);
}

//shared non-thread safe source
std::vector<int> shared_vec;

void append_data(int thread_id) {
    for (int i = 0; i < 500; ++i) {
        spin_lock();    //Acquire custom spin lock
        
        shared_vec.push_back(thread_id * 1000 + i); // critical section protected from data races
        
        spin_unlock(); // Release custo spin lock
        
    }
}

int main() {
    //using std::jthread for automatic joining lifecycle
    std::jthread t1{append_data, 1};
    std::jthread t2{append_data, 2};
    
    std::cout << "Final vector size: " << shared_vec.size() << std::endl;
    
    return 0;
}


