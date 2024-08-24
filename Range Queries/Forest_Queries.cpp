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
    ll n, q;
    cin >> n >> q;
    vector<string> vs(n);
    for (ll i = 0; i < n; i++)
    {
        cin >> vs[i];
    }

    vector<vector<ll>> prefix(n + 1, vector<ll>(n + 1, 0));

    for (ll i = 1; i <= n; i++)
    {
        for (ll j = 1; j <= n; j++)
        {
            prefix[i][j] = (vs[i - 1][j - 1] == '*') + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
        }
    }

    for (int k = 0; k < q; k++)
    {
        ll y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        x1--, x2--, y1--, y2--;

        ll ans = prefix[y2 + 1][x2 + 1] - prefix[y1][x2 + 1] - prefix[y2 + 1][x1] + prefix[y1][x1];
        cout << ans << endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}