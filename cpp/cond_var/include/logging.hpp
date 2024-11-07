#include <stdio.h>

#if !defined(__LOGGING_HPP)
#define __LOGGING_HPP

#if defined(DEBUG_BUILD)
    #define LOG_D(...) fprintf( stdout, "%s:%s():%d ", __FILE__, __FUNCTION__, __LINE__); fprintf( stdout, ##__VA_ARGS__ ); fprintf( stdout, "\n" );
    #define LOG_E(...) fprintf( stdout, "ERROR: %s:%s():%d ", __FILE__, __FUNCTION__, __LINE__); fprintf( stdout, ##__VA_ARGS__ ); fprintf( stdout, "\n" );
#else
    #define LOG_D(...)
    #define LOG_E(...)
#endif

#endif // __LOGGING_HPP
