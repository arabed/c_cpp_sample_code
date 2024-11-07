#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

using namespace std;

int main()
{
    condition_variable condition;
    mutex mtx;
    bool ready = false;

    cout << "running..." << endl;

    thread t1([&](){
        this_thread::sleep_for( chrono::milliseconds( 2000 ));
        cout << "t1 acquiring lock" << endl;
        unique_lock<mutex> lock( mtx );
        cout << "t1 acquired lock" << endl;
        ready = true;
        lock.unlock();
        cout << "t1 released lock; notifying" << endl;
        condition.notify_one();
    });

    cout << "main acquiring lock" << endl;
    unique_lock<mutex> lock( mtx );
    
    cout << "main acquired lock; waiting" << endl;
    condition.wait( lock, [&]() {
        return ready;
    } );
    cout << "main finished waiting" << endl;

    cout << "ready: " << ready << endl;

    t1.join();
    return 0;
}