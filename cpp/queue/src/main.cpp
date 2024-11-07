#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <queue>

using namespace std;

template<typename E>
class blocking_queue
{
public:
    blocking_queue(int max_size):
        _max_size( max_size )
    {
    }

    void push(E e)
    {
        unique_lock<mutex> lock(_mtx);
        _cond.wait(lock, [&](){ return _queue.size() < _max_size;});
        
        _queue.push(e);

        lock.unlock();
        _cond.notify_one();
    }

    E pop()
    {
        unique_lock<mutex> lock(_mtx);
        _cond.wait(lock, [&](){ return !_queue.empty();});

        E item = _queue.front();
        _queue.pop();

        lock.unlock();
        _cond.notify_one();

        return item;
    }

    int size()
    {
        lock_guard<mutex> lock(_mtx);
        return _queue.size();
    }

private:
    mutex _mtx;
    condition_variable _cond;
    int _max_size;
    queue<E> _queue;
};

int main()
{
    blocking_queue<int> qu(3);

    thread t1([&]() {
        for(int i=0; i<10; i++)
        {
            qu.push(i);
            cout << "produce: " << i << " size: " << qu.size() << endl;
        }
    });
    thread t2([&]() {
        for(int i=0; i<10; i++)
        {
            int item = qu.pop();
            cout << "consumed: " << item << " size: " << qu.size() << endl;
        }
    });

    t1.join();    
    t2.join();    

    return 0;
}
