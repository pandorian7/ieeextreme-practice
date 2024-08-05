#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;

class PrimeEngine
{
private:
    vector<int> primes = {2};
    vector<int> streamIndexes;
    unordered_map<int, bool> nonPrimeMap;
    unordered_map<int, int> primeIndexes;
    const int Block = 50;

    int limit = 0;

    void setNonPrime(int n)
    {
        nonPrimeMap[n] = true;
    }

    void extend(int byNBlocks = 1)
    {
        int prvLimit = limit;
        int newLimit = prvLimit + byNBlocks * Block;

        limit = newLimit;

        int prvTo = prvLimit / 2;
        int to = newLimit / 2;
        int from = 1;

        int val;

        for (int i = from; i <= to; i++)
        {
            if (isPrime(i))
            {
                val = i * 2;
                while (val <= newLimit)
                {
                    // cout << val << ' ';
                    setNonPrime(val);
                    val += i;
                }
            }
        }
        for (int i = primes.back() + 1; i <= limit; i++)
        {
            if (isPrime(i))
            {

                primes.push_back(i);
                primeIndexes[i] = primes.size() - 1;
            }
        }
        // cout << "extended" << endl;
    }

public:
    PrimeEngine()
    {
        nonPrimeMap[1] = true;
        primeIndexes[2] = 0;
        extend();
    }

    bool isPrime(int n)
    {
        extendUntil(n);
        if (n <= 0)
            return false;
        return !nonPrimeMap[n];
    }

    void show()
    {
        for (int i = 0; i < 50; i++)
        {
            cout << i << " " << nonPrimeMap[i] << endl;
        }
    }

    int getLimit() { return limit; }

    void extendUntil(int n)
    {
        if (limit >= n)
            return;
        int nBlocks = ((n - getLimit()) / Block) + 1;
        extend(nBlocks);
    }

    int nthPrime(int n)
    {
        // cout << "prime requested: " << n << endl;
        while (primes.size() <= n)
            extend();
        return primes[n - 1];
    }
    int nPrimes() { return primes.size(); }

    int nextPrime(int num)
    {
        extendUntil(num);
        return nthPrime(primeIndexes[num] + 2);
    }
    int previousPrime(int num)
    {
        extendUntil(num);
        return nthPrime(primeIndexes[num]);
    }

    std::function<int()> primeStream(int &counter)
    {
        return [&counter, this]() mutable -> int
        {
            return this->nthPrime(counter++);
        };
    }
};

vector<int> factors(PrimeEngine &pe, int val)
{
    int index = 1;
    auto next = pe.primeStream(index);
    vector<int> ps;
    int prime = next();
    while (val > 1)
    {
        while (val % prime == 0)
        {
            ps.push_back(prime);
            val /= prime;
        }
        prime = next();
    }
    return ps;
}

struct factor_map
{
    static PrimeEngine *pe;
    unordered_map<int, int> fm;

    factor_map()
    {
        if (!pe)
        {
            cout << "factor_map: prime engine unavailable" << endl;
        }
    }
    vector<pair<int, int>> pairs() const
    {
        vector<pair<int, int>> ret;
        for (auto it = fm.cbegin(); it != fm.cend(); it++)
        {
            ret.emplace_back(it->first, it->second);
        }
        return ret;
    }

    vector<int> flatten() const
    {
        vector<int> flatten_map;
        for (auto p : pairs())
        {
            for (int i = 0; i < p.second; i++)
            {
                flatten_map.push_back(p.first);
            }
        }
        return flatten_map;
    }

    bool isDrowning() const
    // determines if there is factors with minus exponents
    {

        for (auto p : pairs())
        {
            if (p.second < 0)
                return true;
        }
        return false;
    }

    size_t eval() const
    {
        size_t ret = 1;
        for (int val : flatten())
        {
            ret *= val;
        }
        return ret;
    }

    void operator*=(int val)
    {
        for (int factor : factors(*pe, val))
        {
            fm[factor] = fm[factor] + 1;
        }
    }

    void operator*=(const factor_map &other)
    {
        for (auto p : other.pairs())
        {
            fm[p.first] = fm[p.first] + p.second;
        }
    }

    factor_map operator*(const factor_map &other)
    {
        factor_map new_fm;

        new_fm = *this;
        new_fm *= other;

        return new_fm;
    }

    void operator/=(int val)
    {
        for (int factor : factors(*pe, val))
        {
            fm[factor] = fm[factor] - 1;
        }
    }

    void operator/=(const factor_map &other)
    {
        for (auto p : other.pairs())
        {
            fm[p.first] = fm[p.first] - p.second;
        }
    }

    factor_map operator/(const factor_map &other)
    {
        factor_map new_fm;

        new_fm = *this;
        new_fm /= other;

        return new_fm;
    }

    factor_map operator=(const factor_map &other)
    {
        for (auto p : other.pairs())
        {
            fm[p.first] = p.second;
        }
        return *this;
    }
};
PrimeEngine *factor_map::pe = nullptr;

factor_map factorial_fm(int num)
{
    factor_map fm;
    if (num <= 0)
        return fm;
    for (int i = 0; i <= num; i++)
    {
        fm *= i;
    }
    return fm;
}

double permutaion_with_duplicates2(int n, int d1, int d2)
{
    auto ret = factorial_fm(n) / (factorial_fm(d1) * factorial_fm(d2));
    return ret.eval();
}

int main()
{
    PrimeEngine pe;
    factor_map::pe = &pe;

    int t, n;
    int maxDoubles;
    int nDouble, nSingle;
    double k;
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