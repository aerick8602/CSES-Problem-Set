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

class SGT
{
public:
    v<ll> tree;
    SGT(ll n)
    {
        tree.resize(4 * n);
    }

    void build(ll i, ll s, ll e, v<ll> &arr)
    {
        if (s == e)
        {
            tree[i] = arr[s];
            return;
        }
        ll mid = (s + e) >> 1;
        build(2 * i + 1, s, mid, arr);
        build(2 * i + 2, mid + 1, e, arr);
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
    }

    ll getVal(ll i, ll s, ll e, ll rooms)
    {
        if (tree[i] < rooms)
            return 1e9;
        if (s == e)
        {
            tree[i] -= rooms;
            return s;
        }
        ll mid = (s + e) >> 1;
        ll l = 1e9, r = 1e9;
        l = getVal(2 * i + 1, s, mid, rooms);
        if (l == 1e9)
        {
            r = getVal(2 * i + 2, mid + 1, e, rooms);
        }
        tree[i] = max(tree[2 * i + 1], tree[2 * i + 2]);
        return min(l, r);
    }
};

void solve()
{
    ll n, m;
    cin >> n >> m;
    v<ll> h(n), r(m);
    input(h);
    input(r);

    SGT tree(n);
    tree.build(0, 0, n - 1, h);

    for (auto room : r)
    {
        ll ans = tree.getVal(0, 0, n - 1, room);
        if (ans == 1e9)
            cout << 0 << " ";
        else
            cout << ans + 1 << " ";
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}