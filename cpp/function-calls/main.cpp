#include <iostream>

using namespace std;

int func( char* val )
{
    cout << "func:'" << val << "'" << endl;
    return 0;
}

int main()
{
    int (funcPtr*)( char* );

    funcPtr = func;

    cout << "start.." << endl;

    funcPtr( "this is it!" );

    return 0;
}