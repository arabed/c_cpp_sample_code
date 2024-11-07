#include <iostream>

using namespace std;

class a
{
public:
    a( int val = 0 );
    virtual ~a();
    virtual int getVal();
protected:
    int mVal;
};

class b: public a
{
public:
    b( int val = 0);
    ~b();
    b operator+( b& b_class );
    b operator+( int val );
    int getVal();
};

a::a( int val ):
    mVal( val )
{
    cout << "Class \'a\' created." << endl;
}

a::~a()
{
    cout << "Class \'a\' deleted." << endl;
}

int a::getVal()
{
    cout << "Class \'a\' getVal:" << mVal << endl;
    return mVal;
}

b::b( int val ):
    a( val )
{
    cout << "Class \'b\' created." << endl;
}

b::~b()
{
    cout << "Class \'b\' deleted." << endl;
}

b b::operator+( b& b_class )
{
    return b( getVal() + b_class.getVal() );
}

b b::operator+( int val )
{
    return b( getVal() + val );
}

int b::getVal()
{
    cout << "Class \'b\' getVal:" << mVal << endl;
    return mVal;
}

int main()
{
    b b_class1( 10 );
    b b_class2( 20 );

    cout << "b_class1" << b_class1.a::getVal() << endl; 
    cout << "b_class2" << b_class2.a::getVal() << endl; 
    b b_class3 = b_class1 + b_class2;
    cout << "b_class3" << b_class3.a::getVal() << endl; 
    b b_class4 = b_class3 + 10;
    cout << "b_class4" << b_class4.a::getVal() << endl; 

    return 0;
}
