#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <thread>
#include <mutex>
#include <chrono>
#include <exception>

using namespace std;

void calculatePiTask( mutex& mtx, double& pi, int startTerm, int delta ) 
{
    double sum = 0.0;

    if( delta < 1 )
    {
        throw runtime_error( "ERROR: delta cannot be less than 1" );
    }

    for( int i = startTerm; i < startTerm + delta; i++ )
    {
        int sign = pow(-1, i);
        double term = 1.0/(i * 2 + 1);
        sum += sign * term;
    }

    mtx.lock();
    pi += (sum * 4);
    mtx.unlock();
}

double calculatePi( int threadCount ) 
{
    mutex mtx;
    double pi = 0;
    int endTerm = 1E8;
    int delta = endTerm / threadCount;
    
    vector<thread> threads;

    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for( int i = 0; i < threadCount; i++ )
    {
        threads.push_back( thread( calculatePiTask, ref( mtx ), ref( pi ), i * delta, delta ) );
    }
    auto originalthread = threads.begin();
    // do other stuff here.
    while( originalthread != threads.end() )
    {
        originalthread->join();
        originalthread++;
    }
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout << "thrs:" << threadCount << setprecision(15) << " pi:'" << pi << "' " <<  chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "(msecs)" << std::endl;

    return pi;
}

int main() 
{
    try 
    {
        for( int n = 1; n < 100; n += 10 )
        {
            calculatePi( n );
        }
    }
    catch( const std::exception &e )
    {
        cout << e.what() << endl;
    }

    return 0;
}