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

struct Node
{
    ll max_sum;
    ll prefix_sum;
    ll suffix_sum;
    ll total_sum;
};

class SegmentTree
{
public:
    SegmentTree(const vector<ll> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void update(ll idx, ll value)
    {
        update(1, 0, n - 1, idx, value);
    }

    ll getMaxSubarraySum()
    {
        return max(0LL, tree[1].max_sum);
    }

private:
    ll n;
    vector<Node> tree;

    void build(const vector<ll> &arr, ll node, ll start, ll end)
    {
        if (start == end)
        {
            ll value = arr[start];
            tree[node] = {value, value, value, value};
        }
        else
        {
            ll mid = (start + end) / 2;
            ll left_child = 2 * node;
            ll right_child = 2 * node + 1;

            build(arr, left_child, start, mid);
            build(arr, right_child, mid + 1, end);

            tree[node] = merge(tree[left_child], tree[right_child]);
        }
    }

    void update(ll node, ll start, ll end, ll idx, ll value)
    {
        if (start == end)
        {
            tree[node] = {value, value, value, value};
        }
        else
        {
            ll mid = (start + end) / 2;
            ll left_child = 2 * node;
            ll right_child = 2 * node + 1;

            if (idx <= mid)
            {
                update(left_child, start, mid, idx, value);
            }
            else
            {
                update(right_child, mid + 1, end, idx, value);
            }

            tree[node] = merge(tree[left_child], tree[right_child]);
        }
    }

    Node merge(const Node &left, const Node &right)
    {
        Node parent;
        parent.total_sum = left.total_sum + right.total_sum;
        parent.prefix_sum = max(left.prefix_sum, left.total_sum + right.prefix_sum);
        parent.suffix_sum = max(right.suffix_sum, right.total_sum + left.suffix_sum);
        parent.max_sum = max({left.max_sum, right.max_sum, left.suffix_sum + right.prefix_sum});
        return parent;
    }
};

void solve()
{
    ll n, m;
    cin >> n >> m;

    vector<ll> arr(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    for (int i = 0; i < m; ++i)
    {
        ll k, x;
        cin >> k >> x;
        segTree.update(k - 1, x);
        cout << segTree.getMaxSubarraySum() << endl;
    }
}
signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}