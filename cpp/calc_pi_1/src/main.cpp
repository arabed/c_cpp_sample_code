#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
#include <exception>

using namespace std;


double doCalculatePi( int term ) 
{
    double sum = 0.0;
    if( term < 1 )
    {
        throw runtime_error( "term should be greater than 0" );

    }

    for( int i = 0; i < term; i++ )
    {
        int sign = pow(-1, i);
        double term = 1.0/(i * 2 + 1);
        sum += sign * term;
    }

    return (sum * 4);
}

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

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
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
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "thrs:" << threadCount << setprecision(15) << " pi:'" << pi << "' " <<  chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "(msecs)" << endl;

    return pi;
}

int main() 
{
    packaged_task<double(int)> task1( doCalculatePi );
    future<double> future1 = task1.get_future();

    thread t1( move( task1 ), 1E6 );
    //thread t1( ref( task1 ), 1E6 );

    try 
    {
        double result = future1.get();
        cout << setprecision( 15 ) << result << endl;
    }
    catch( exception &e )
    {
        cout << "ERROR: " << e.what() << endl;
    }
    

    t1.join();

    return 0;
}