#include <iostream>
#include <unordered_map>

using namespace std;

unordered_map<int, int> *fibMem = NULL;

int Fibonacci(int n)
{
    int ret;
    if (fibMem)
    {
        if (fibMem->count(n))
            return fibMem->at(n);
    }
    if (n == 1)
        ret = 1;
    else if (n == 2)
        ret = 2;
    else
        ret = Fibonacci(n - 1) + Fibonacci(n - 2);
    if (fibMem)
    {
        (*fibMem)[n] = ret;
    }
    return ret;
}

int main()
{
    unordered_map<int, int> fm;
    fibMem = &fm;

    int t, n, justBefore;
    cin >> t;
    while (t--)
    {
        cin >> n;
        justBefore = Fibonacci(n);
        cout << justBefore % 10 << endl;
    }
}