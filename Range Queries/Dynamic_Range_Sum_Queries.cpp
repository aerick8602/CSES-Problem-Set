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
class SegmentTree
{
public:
    vector<ll> tree;

    SegmentTree(ll n, ll val)
    {
        tree.resize(4 * n, val);
    }

    void build(vector<ll> &arr, ll s, ll e, ll i = 0)
    {
        if (s == e)
        {
            tree[i] = arr[s];
            return;
        }

        ll mid = (s + e) / 2;
        build(arr, s, mid, 2 * i + 1);
        build(arr, mid + 1, e, 2 * i + 2);
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }

    ll getSum(ll s, ll e, ll l, ll r, ll i = 0)
    {
        if (l <= s && r >= e)
        {
            return tree[i];
        }
        if (r < s || l > e)
        {
            return 0;
        }
        ll mid = (s + e) / 2;
        return getSum(s, mid, l, r, 2 * i + 1) + getSum(mid + 1, e, l, r, 2 * i + 2);
    }

    void update(ll s, ll e, ll idx, ll val, ll i = 0)
    {
        if (s == e)
        {
            tree[i] = val;
            return;
        }
        ll mid = (s + e) / 2;
        if (idx <= mid)
        {
            update(s, mid, idx, val, 2 * i + 1);
        }
        else
        {
            update(mid + 1, e, idx, val, 2 * i + 2);
        }
        tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
};

void solve()
{
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n);
    input(v);

    SegmentTree tree(n, LLONG_MAX);
    tree.build(v, 0, n - 1);

    for (int i = 0, t, l, r; i < q; i++)
    {
        cin >> t >> l >> r;
        if (t == 2)
            cout << tree.getSum(0, n - 1, l - 1, r - 1) << endl;
        else
            tree.update(0, n - 1, l - 1, r);
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}