#include <bits/stdc++.h>
using namespace std;
using ll = long long;   // -2^63 to 2^63 - 1
using ld = long double; // 12 bytes (12*8 bits)
template <typename T>
using v = vector<T>;
template <typename T>
using vv = vector<vector<T>>;
template <typename T>
using us = unordered_set<T>;
template <typename T>
using pq = priority_queue<T>;
template <typename T1, typename T2>
using p = pair<T1, T2>;
template <typename T>
using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T1, typename T2>
using um = std::unordered_map<T1, T2>;
#define pb push_back
#define cy cout << "YES\n"
#define cn cout << "NO\n"
#define all(x) x.begin(), x.end()
#define prt(x) cout << x << endl
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define SUM(v) accumulate(all(v), 0LL)
#define roundUp(a, b) ((a + b - 1) / b)
#define input(x)      \
    for (auto &i : x) \
        cin >> i;
ll lcm(ll x, ll y) { return x * y / std::__gcd(x, y); }
#define print(a)          \
    for (auto x : a)      \
        cout << x << ' '; \
    cout << endl;

const int MOD = 1e9 + 7;

void solve()
{
    ll n;
    cin >> n;
    ll sum = n * (n + 1) / 2;
    if (sum & 1)
    {
        cout << "NO";
    }
    else
    {
        cout << "YES\n";
        if (n & 1)
        {
            cout << n / 2 + 1 << endl;
            cout << 1 << ' ' << n - 1 << ' ';
            for (int i = 2, j = n - 2; i < j; i += 2, j -= 2)
            {
                cout << i << ' ' << j << ' ';
            }
            cout << endl;
            cout << n / 2 << endl;
            cout << n << ' ';
            for (int i = 3, j = n - 3; i < j; i += 2, j -= 2)
            {
                cout << i << ' ' << j << ' ';
            }
        }
        else
        {
            cout << n / 2 << endl;
            for (int i = 1, j = n; i < j; i += 2, j -= 2)
            {
                cout << i << ' ' << j << ' ';
            }
            cout << endl;
            cout << n / 2 << endl;
            for (int i = 2, j = n - 1; i < j; i += 2, j -= 2)
            {
                cout << i << ' ' << j << ' ';
            }
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}