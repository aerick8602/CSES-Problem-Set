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
    vector<ll> tree, lazy;
    ll n;

public:
    SGT(ll size)
    {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void build(ll s, ll e, vector<ll> &arr, ll i = 0)
    {
        if (s == e)
        {
            tree[i] = arr[s];
            return;
        }
        ll mid = (s + e) / 2;
        build(s, mid, arr, 2 * i + 1);
        build(mid + 1, e, arr, 2 * i + 2);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }

    void update(ll s, ll e, ll l, ll r, ll val, ll i = 0)
    {
        if (lazy[i] != 0)
        {
            tree[i] += lazy[i] * (e - s + 1);
            if (s != e)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }

        if (s > e || s > r || e < l)
            return;

        if (s >= l && e <= r)
        {
            tree[i] += val * (e - s + 1);
            if (s != e)
            {
                lazy[2 * i + 1] += val;
                lazy[2 * i + 2] += val;
            }
            return;
        }

        ll mid = (s + e) / 2;
        update(s, mid, l, r, val, 2 * i + 1);
        update(mid + 1, e, l, r, val, 2 * i + 2);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }

    ll getVal(ll s, ll e, ll idx, ll i = 0)
    {
        if (lazy[i] != 0)
        {
            tree[i] += lazy[i] * (e - s + 1);
            if (s != e)
            {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }

        if (s == e)
            return tree[i];

        ll mid = (s + e) / 2;
        if (idx <= mid)
            return getVal(s, mid, idx, 2 * i + 1);
        else
            return getVal(mid + 1, e, idx, 2 * i + 2);
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;
    v<ll> v(n);
    input(v);
    SGT sgt(n);
    sgt.build(0LL, n - 1, v);
    for (int i = 0, t, l, r, idx, val; i < q; i++)
    {
        cin >> t;
        if (t == 1)
        {
            cin >> l >> r >> val;
            l--, r--;
            sgt.update(0LL, n - 1, l, r, val);
        }
        else
        {
            cin >> idx;
            idx--;
            cout << sgt.getVal(0LL, n - 1, idx) << endl;
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