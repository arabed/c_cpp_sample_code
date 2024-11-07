#define _USE_MATH_DEFINES

#include <iomanip>
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <cmath>

using namespace std;

mutex g_mtx;

double calculatePiTask( int id, int start, int delta ) 
{
    double pi = 0.0;

    if( delta < 1 )
    {
        throw runtime_error( "ERROR: delta cannot be less than 1" );
    }

    unique_lock<mutex> lock(g_mtx);
    cout << "starting: [" << id << "] s:" << start << " d:" << delta << endl;
    lock.unlock();

    for( int i = start; i < start + delta; i++ )
    {
        int sign = pow(-1, i);
        double term = 1.0/(i * 2 + 1);
        pi += sign * term;
    }

    return pi * 4;
}

int work(int id)
{
    unique_lock<mutex> lock(g_mtx);
    cout << "starting: " << id << endl;
    lock.unlock();
    for(int i = 0; i < 100; i++)
    {
        //cout << "running " << id << endl;
        int milliseconds = (int)((1000 * rand()/RAND_MAX ) + 10);
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }
    lock.lock();
    cout << "ending: " << id << endl;
    lock.unlock();

    return id;
}

int main()
{
    const int CONCURENCY = static_cast<int>( thread::hardware_concurrency() );

    cout << "hardware_concurrency: " << CONCURENCY << endl;

    vector<shared_future<double>> shared_futures;
    vector<future<double>> futures;

    double pi = 0.0;

    thread t([&]()
    {
        int delta = 1E7 / CONCURENCY;
        int start = 0;
        
        auto startTime = chrono::steady_clock::now();

        for( int id = 0; id < CONCURENCY; id++)
        {
            //futures.push_back( async(launch::async, work, id) );
            //shared_future<int> f = async(launch::async, work, id);
            shared_future<double> f = async(launch::async, calculatePiTask, id, start, delta);
            shared_futures.push_back(f);
            start += delta;
        }

        for(auto f: shared_futures)
        {
            cout << "returned: " << f.get() << endl;
            pi += f.get();
        }

        auto endTime = chrono::steady_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
        cout << "duration: " << duration << " (msecs)" << endl;
    });


    t.join();

    cout << setprecision(15) << "my pi:  " << pi << endl;
    cout << setprecision(15) << "sys pi: " << M_PI << endl;

    return 0;
}
