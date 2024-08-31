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
    long long sum;
    long long prefixSum;
    long long suffixSum;
    long long maxSubarraySum;

    Node(long long sum = 0, long long prefixSum = 0, long long suffixSum = 0, long long maxSubarraySum = 0)
    {
        this->sum = sum;
        this->prefixSum = prefixSum;
        this->suffixSum = suffixSum;
        this->maxSubarraySum = maxSubarraySum;
    }
};

class SegmentTree
{
private:
    vector<Node> tree;
    int n;

    Node combine(Node left, Node right)
    {
        Node parent;
        parent.sum = left.sum + right.sum;
        parent.prefixSum = max(left.prefixSum, left.sum + right.prefixSum);
        parent.suffixSum = max(right.suffixSum, right.sum + left.suffixSum);
        parent.maxSubarraySum = max({left.maxSubarraySum, right.maxSubarraySum, left.suffixSum + right.prefixSum});
        return parent;
    }

    void build(vector<long long> &arr, int node, int start, int end)
    {
        if (start == end)
        {
            long long value = arr[start];
            tree[node] = Node(value, max(0LL, value), max(0LL, value), max(0LL, value));
        }
        else
        {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void update(int node, int start, int end, int idx, long long value)
    {
        if (start == end)
        {
            tree[node] = Node(value, max(0LL, value), max(0LL, value), max(0LL, value));
        }
        else
        {
            int mid = (start + end) / 2;
            if (idx <= mid)
            {
                update(2 * node + 1, start, mid, idx, value);
            }
            else
            {
                update(2 * node + 2, mid + 1, end, idx, value);
            }
            tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    Node query(int node, int start, int end, int l, int r)
    {
        if (r < start || end < l)
        {
            return Node(0, 0, 0, 0);
        }
        if (l <= start && end <= r)
        {
            return tree[node];
        }
        int mid = (start + end) / 2;
        Node left = query(2 * node + 1, start, mid, l, r);
        Node right = query(2 * node + 2, mid + 1, end, l, r);
        return combine(left, right);
    }

public:
    SegmentTree(vector<long long> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void update(int idx, long long value)
    {
        update(0, 0, n - 1, idx, value);
    }

    long long query(int l, int r)
    {
        Node result = query(0, 0, n - 1, l, r);
        return result.prefixSum;
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    SegmentTree segTree(arr);

    for (int i = 0; i < q; i++)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int k;
            long long u;
            cin >> k >> u;
            segTree.update(k - 1, u);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            cout << segTree.query(a - 1, b - 1) << "\n";
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