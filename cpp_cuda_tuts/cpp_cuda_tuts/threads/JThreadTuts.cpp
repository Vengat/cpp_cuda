#include "JThreadTuts.hpp"

JThreadTuts::JThreadTuts() = default;
JThreadTuts::~JThreadTuts() = default;

void JThreadTuts::printSequence(std::stop_token st) {
    int i = 0;
    while(!st.stop_requested()) {
        std::cout << "Worker processing data..."<< i <<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Worker thread shutting down..."<< std::endl;
}

int main() {
    JThreadTuts tuts{};

    std::jthread jt(&JThreadTuts::printSequence, &tuts);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    std::cout << "Press Enter to stop the thread " <<std::endl;
    
    std::cin.get();
    
    std::cout << "Main thread received Enter, Exiting main";
    
    return 0;
    
    // Destructor of jt runs here where main exits
    // Automatically executes jt.request_stop(), signals printSequence to exit loop
    // Automatically executes jt.join() -> waits for worker thread to finish printing Worker thread shuttting down message
}
