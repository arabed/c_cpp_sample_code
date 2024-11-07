#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define BUF_SIZE  100
char buffer[BUF_SIZE];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

unsigned int write_idx = 0;
unsigned int read_idx = 0;
unsigned int data_size = 0;
bool stopThread = false;

// write function
void* func1(void* arg) 
{ 
    // detach the current thread 
    // from the calling thread 
    pthread_detach( pthread_self() );
  
    printf( "inside the thread #1\n"); 

    while( !stopThread )
    {
        if( data_size == ( BUF_SIZE - 1 ) )
        {
            printf( "inside the thread #1 - buffer is full\n"); 
            usleep( 100000l ); // 100 ms
        }
        else
        {
            pthread_mutex_lock( &mutex );
            data_size++;
            buffer[write_idx] = write_idx;
            printf( "inside the thread #1 - write to buffer:[%u](%u) {%d}\n", data_size, write_idx, buffer[write_idx] ); 
            write_idx++;
            write_idx = write_idx % BUF_SIZE;
            pthread_mutex_unlock( &mutex );
            usleep( 2000l ); // 2 ms
        }
    }
  
    // exit the current thread 
    pthread_exit(NULL); 
}

void* func2(void* arg) 
{ 
    // detach the current thread 
    // from the calling thread 
    pthread_detach( pthread_self() ); 
  
    printf( "Inside the thread #2\n" ); 

    while( !stopThread )
    {
        if( data_size == 0 )
        {
            printf( "inside the thread #2 - nothing to read\n"); 
            usleep( 100000l ); // 100 ms
        }
        else
        {
            pthread_mutex_lock( &mutex );
            data_size--;
            printf( "inside the thread #2 - read from buffer:[%u](%u) {%d}\n", data_size, read_idx, buffer[read_idx] );
            read_idx++;
            read_idx = read_idx % BUF_SIZE;
            pthread_mutex_unlock( &mutex );
            usleep( 1000l ); // 1 ms
        }
    }

    // exit the current thread 
    pthread_exit(NULL); 
}

int main() 
{ 
    pthread_t ptid1;
    pthread_t ptid2;

    // Creating a new thread 
    printf( "creating threads...\n" );
    pthread_create(&ptid1, NULL, &func1, NULL); 
    pthread_create(&ptid2, NULL, &func2, NULL); 

    // Waiting for the created thread to terminate 
    printf( "waiting for threads to complete...\n" );
    pthread_join(ptid2, NULL); 
    pthread_join(ptid1, NULL); 

    return 0; 
} 
