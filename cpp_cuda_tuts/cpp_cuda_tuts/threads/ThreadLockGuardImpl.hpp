#ifndef ThreadLockGuardImpl_hpp
#define ThreadLockGuardImpl_hpp

#include <vector>
#include <iostream>
#include <thread>
#include <string>
#include <functional>


class ThreadLockGuardImpl {
private:
    std::vector<int> m_List{};
    std::mutex mtx{};
public:
    void FillList();
    int GetListSize();
};
#endif
