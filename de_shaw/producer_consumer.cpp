// TOPIC: Producer/Consumer OR Bounded Buffer Problem In C++11 Threading

// THE PROBLEM STATEMENT:
// 1. Producer will produce and consumer will consume with synchronisation of a common buffer.
// 2. Until producer thread produces any data consumer thread can't consume.
// 3. Threads will use condition_variable to notify each other.
// 4. We need mutex if we use condition_variable because CV waits on mutex.
// 5. This is one of the example of producer consumer there are many.

// PRODUCER thread steps:
// 1. lock mutex, if success then go ahead otherwise wait for mutex to get free.
// 2. check if buffer is full and if it is full then unlock mutex and sleep, if not then go ahead and produce.
// 3. insert item in buffer.
// 4. unlock mutex. 
// 5. notify consumer.

// CONSUMER thread steps:
// 1. lock mutex, if success then go ahead and consume otherwise wait for mutex to get free.
// 2. check if buffer is empty and if it is, then unlock the mutex and sleep, if not then go ahead and consume.
// 3. consume item from buffer.
// 4. unlock mutex.
// 5. notify producer.

// IMP:
// If you are talking about producer consumer then they have to notify each other.

#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <atomic>
using namespace std;

std::mutex mu;
std::condition_variable cond;
std::atomic<bool> done(false);
deque<int> buffer;
const unsigned int maxBufferSize = 50;

void producer(int val) {
     while (val) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() < maxBufferSize;});
        buffer.push_back(val);
        cout << "Produced: " << val << endl;
        val--;
        locker.unlock();
        cond.notify_one();
    }
    done = true;
    std::cout << "Producer finished." << std::endl;
}

void consumer(){
    while (true) {
        std::unique_lock<std::mutex> locker(mu);
        cond.wait(locker, [](){return buffer.size() > 0;});
        int val = buffer.back();
        buffer.pop_back();
        cout << "Consumed: " << val << endl;
        locker.unlock();
        if (done && buffer.empty()) {
            break; // Exit if done and buffer is empty
        }
        cond.notify_one();
    }
    std::cout << "Consumer finished." << std::endl;
}

int main() {

    std::thread t1(producer, 10);
    std::thread t2(consumer);
    t1.join();
    t2.join();

    return 0;
}