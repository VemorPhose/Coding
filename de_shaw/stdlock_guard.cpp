// TOPIC: lock_guard In C++ (std::lock_guard<mutex> lock(m1))

// NOTES:
// 1. It is very lightweight wrapper for owning mutex on scoped basis.
// 2. It acquires mutex lock the moment you create the object of lock_guard.
// 3. It automatically removes the lock when it goes out of scope.
// 4. You cannot explicitly unlock the lock_guard.
// 5. You cannot copy lock_guard.

#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex m1;
int buffer = 0;

void task(const char* threadNumber, int loopFor) {
    std::lock_guard<mutex> lock(m1);  // acquires lock and auto-releases on scope exit
    for (int i = 0; i < loopFor; ++i) {
        buffer++;
        cout << threadNumber << buffer << endl;
    }
}

int main() {
    thread t1(task, "T0 ", 10);
    thread t2(task, "T1 ", 10);

    t1.join();
    t2.join();

    return 0;
}
