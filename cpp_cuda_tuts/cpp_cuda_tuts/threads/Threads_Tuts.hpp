#pragma once

#include <string>
#include <thread>
#include <functional>

class Thread_Tuts {
private:
    std::string m_name;
    std::thread m_thread;
    std::function<void()> m_task;
    bool m_running;
    
public:
    Thread_Tuts();
    Thread_Tuts(const std::string& name)
    ~ThreadTuts();
    
    //delete copy - threads cant be copied
    Thread_Tuts(const Thread_Tuts&) = delete;
    Thread_Tuts&
    
    
    
};
