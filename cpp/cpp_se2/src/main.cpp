#define _USE_MATH_DEFINES

#include <iostream>

using namespace std;

int bad_func(int id)
{
    bool bError1 = false;
    bool bError2 = false;
    bool bError3 = true;

    if( bError1 )
    {
        throw "Some error";
    }
    if( bError2 )
    {
        throw string("Some else error");
    }
    if( bError3 )
    {
        throw exception();
    }

    return id;
}

int main()
{
    int ret = -1;

    try
    {
        ret = bad_func(0);
    }
    catch(int e)
    {
        std::cerr << "ERROR: code:(" << e << ")" << endl;
    }
    catch(const char* e)
    {
        std::cerr << "ERROR: message:[" << e << "]" << endl;
    }
    catch(string& e)
    {
        std::cerr << "ERROR: message:[" << e << "]" << endl;
    }
    catch(exception& e)
    {
        std::cerr << "ERROR: message:[" << e.what() << "]" << endl;
    }
    
    return ret;
}
