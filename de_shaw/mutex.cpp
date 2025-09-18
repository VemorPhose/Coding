#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

uint64_t counter = 0;
std::mutex mtx;

void inc() {
    mtx.lock();
    for (int i = 0; i < 1000000; ++i) {
        counter++;
    }
    mtx.unlock();
}

int32_t main() {
    std::cout << "Starting threads..." << std::endl;
    std::thread t1(inc);
    std::thread t2(inc);
    
    t1.join();
    t2.join();
    
    std::cout << "Threads have completed." << std::endl;
    std::cout << "Counter value: " << counter << std::endl;
    return 0;
}