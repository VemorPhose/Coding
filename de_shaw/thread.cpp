#include <iostream>
#include <thread>
#include <chrono>

void fun() {
    std::cout << "Thread is running..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Thread finished." << std::endl;
}

void daemon() {
    std::cout << "Daemon thread is running..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
    // This will not be printed if the main thread exits before this one
    std::cout << "Daemon thread finished." << std::endl;
}

int main() {
    std::cout << "Starting thread..." << std::endl;
    std::thread t(fun);
    t.join();
    std::thread d(daemon);
    d.detach();
    std::cout << "Thread has completed." << std::endl;
    return 0;
}