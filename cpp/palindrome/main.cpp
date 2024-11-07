#include "iostream"

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        long y=0;
        if(x<0){
            return false;
        }
        long c=x;
        while(c!=0){
            y=y*10;
            y=(c%10)+y;
            c=c/10;
        }
        if(y==x){
            return true;
        }
        return false;
    }
};

int main()
{
    Solution solution;
    cout << solution.isPalindrome( 123456 ) << endl;
    return 0;
}