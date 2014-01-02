#include <cstdio>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <numeric>
#include <climits>
#include <cfloat>
using namespace std;
 
long long getLen(long long n)
{
    long long ret = 0;
 
    long long a = 1;
    long long b = 9;
    long long len = 1;
    while(a <= n){
        b = min(b, n);
        long long fizzbuzz = b / 15 - (a - 1) / 15;
        long long fizz = b / 3 - (a - 1) / 3 - fizzbuzz;
        long long buzz = b / 5 - (a - 1) / 5 - fizzbuzz;
 
        ret += fizzbuzz * 8 + fizz * 4 + buzz * 4;
        ret += (b - a + 1 - fizzbuzz - fizz - buzz) * len;
 
        a *= 10;
        b = (b * 10) + 9;
        ++ len;
    }
 
    return ret;
}
 
int main()
{
    long long n;
    while (cin >> n) {
 
    long long a = 0;
    long long b = 100000000000000000LL;
    while(a < b){
        long long c = (a + b + 1) / 2;
        if(getLen(c) < n)
            a = c;
        else
            b = c - 1;
    }
 
    ostringstream oss;
    while(oss.str().size() < 100){
        ++ a;
        if(a % 3 ==  0 || a % 5 == 0){
            if(a % 3 == 0)
                oss << "Fizz";
            if(a % 5 == 0)
                oss << "Buzz";
        }else{
            oss << a;
        }
    }
 
    string s = oss.str();
    cout << s.substr(n - getLen(b) - 1, 20) << endl;
    }
    return 0;
}
