#include <iostream>
using namespace std;

size_t factorial(int n)
{
    size_t ret;
    if (n == 1 || n == 0)
        ret = 1;
    else
        ret = n * factorial(n - 1);
    return ret;
}

size_t permutaion_with_duplicates2(int n, int dn1, int dn2)
{
    return (size_t)(factorial(n) / (factorial(dn1) * factorial(dn2)));
}

int main()
{
    int t, n;
    int maxDoubles;
    int nDouble, nSingle;
    size_t k;
    cin >> t;

    while (t--)
    {
        cin >> n;
        k = 0;
        maxDoubles = n / 2;
        for (int i = 0; i <= maxDoubles; i++)
        {
            nDouble = i;
            nSingle = n - (2 * nDouble);
            k += permutaion_with_duplicates2(nDouble + nSingle, nDouble, nSingle);
        }
        cout << k << endl;
    }
}