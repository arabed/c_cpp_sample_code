#include <stdio.h>
#include <stdbool.h>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>
#include "logging.hpp"

using namespace std;

class App
{
public:
    void operator()()
    {
        for( int idx = 0; idx < 1E6; idx++ )
        {
            const lock_guard<mutex> guard( mtx );
            count++;
        }
    }

    int getCount()
    {
        return count;
    }
private:
    int count = 0;
    mutex mtx;
};

int main( int argc, char* argv[] )
{
    LOG_D( "********************" );
    if( argc > 1 )
    {
        for( int idx = 0 ; idx < argc; idx++ )
        {
            LOG_D( "idx(%d):\'%s\'", idx, argv[idx] );
        }
    }

    LOG_D( "Setup threads" );
    App app;

    LOG_D( "Start threads" );
    thread t1( ref( app ) );
    thread t2( ref( app ) );

    LOG_D( "Wait on threads" );
    t1.join();
    t2.join();
    LOG_D( "Count:%d", app.getCount() );
    LOG_D( "Done." );
    LOG_D( "********************" );

    return 0;
}
