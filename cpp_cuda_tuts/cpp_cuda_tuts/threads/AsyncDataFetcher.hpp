#ifndef AsyncDataFetcher_hpp
#define AsyncDataFetcher_hpp

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <stdexcept>

class AsyncDataFetcher {
private:
    std::promise<int> p;
}
