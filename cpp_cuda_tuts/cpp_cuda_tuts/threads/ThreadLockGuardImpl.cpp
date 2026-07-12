#include "ThreadLockGuardImpl.hpp"

void ThreadLockGuardImpl::FillList() {
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < 500; ++i) {
        m_List.push_back(i);
    }
}

int ThreadLockGuardImpl::GetListSize() {
    std::lock_guard<std::mutex> lock(mtx);
    return static_cast<int>(m_List.size());
}

int main() {
    ThreadLockGuardImpl tLock{};
    
    std::thread t1(&ThreadLockGuardImpl::FillList, &tLock);
    
    std::thread t2(&ThreadLockGuardImpl::FillList, &tLock);
    
    t1.join();
    t2.join();
    
    int s = tLock.GetListSize();
    std::cout << "The size is " << s << std::endl;
    
    return EXIT_SUCCESS;
    
}

