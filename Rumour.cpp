#include <iostream>
#include <cmath>

using namespace std;

int height(int val)
{
    return (int)floor(log2(val));
}

int nth_level_elements(int n)
{
    return (int)pow(2, n);
}

int next(int current, int target)
{

    if (current == target)
        return target;

    int dir, ret; // down =1 up =0
    int hcurrent, htarget, hdiff;
    int cPad, tPad, tSeg;
    int cFirst, tFirst;
    int tBegin, tEnd, tHalf;

    dir = -1;

    hcurrent = height(current);
    htarget = height(target);

    cFirst = nth_level_elements(hcurrent);
    cPad = current - cFirst;

    if (hcurrent >= htarget)
        dir = 0;
    if (dir != 0)
    {
        hdiff = htarget - hcurrent;
        if (hdiff < 0)
            hdiff *= -1;

        tFirst = nth_level_elements(htarget);

        tSeg = (int)pow(2, hdiff);
        tPad = tSeg * cPad;

        tBegin = tFirst + tPad;
        tEnd = tBegin + tSeg;
        tHalf = tBegin + tSeg / 2;

        if (target >= tBegin && target < tEnd)
            dir = 1;
        else
            dir = 0;
    }

    if (dir == 1)
    {
        int belowLevelFirst = nth_level_elements(hcurrent + 1);
        ret = belowLevelFirst + cPad * 2;
        if (target >= tHalf && target < tEnd)
            ret++;
    }
    else
    {
        int topLevelFirst = nth_level_elements(hcurrent - 1);
        ret = topLevelFirst + cPad / 2;
    }
    return ret;
}

int main()
{
    int q, a, b;
    int current, steps;
    cin >> q;
    while (q--)
    {
        cin >> a >> b;
        steps = 0;
        current = a;
        while (current != b)
        {
            current = next(current, b);
            steps++;
        }
        cout << steps << endl;
    }
}