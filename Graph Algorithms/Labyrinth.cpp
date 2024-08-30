#include <bits/stdc++.h>
using namespace std;
using ll = long long;   // -2^63 to 2^63 - 1
using ld = long double; // 12 bytes (12*8 bits)
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
#define all(first) first.begin(), first.end()
#define prt(first) cout << first << endl
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define SUM(v) accumulate(all(v), 0LL)
#define roundUp(a, b) ((a + b - 1) / b)
#define input(first)      \
    for (auto &i : first) \
        cin >> i;
ll lcm(ll first, ll second) { return first * second / std::__gcd(first, second); }
#define print(a)              \
    for (auto first : a)      \
        cout << first << ' '; \
    cout << endl;

const int MOD = 1e9 + 7;
bool vis[1000][1000];
char par[1000][1000], ans[1000000];
int N, M, sx, sy, ex, ey, dist[1000][1000];
const int h[] = {1, -1, 0, 0};
const int v[] = {0, 0, 1, -1};
queue<pair<int, int>> Q;
void solve()
{
    cin >> N >> M;
    vector<string> vs(N);

    for (int i = 0; i < N; i++)
    {
        cin >> vs[i];
        for (int j = 0; j < M; j++)
        {
            char c = vs[i][j];
            if (c == '#')
            {
                vis[i][j] = true;
            }
            else if (c == 'A')
            {
                sx = i;
                sy = j;
            }
            else if (c == 'B')
            {
                ex = i;
                ey = j;
            }
        }
    }

    vis[sx][sy] = true;
    Q.push({sx, sy});
    while (!Q.empty())
    {
        pair<int, int> P = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++)
        {
            int dx = P.first + h[i];
            int dy = P.second + v[i];
            if (dx >= 0 && dx < N && dy >= 0 && dy < M && !vis[dx][dy])
            {
                if (i == 0)
                    par[dx][dy] = 'D';
                else if (i == 1)
                    par[dx][dy] = 'U';
                else if (i == 2)
                    par[dx][dy] = 'R';
                else if (i == 3)
                    par[dx][dy] = 'L';
                dist[dx][dy] = dist[P.first][P.second] + 1;
                vis[dx][dy] = true;
                Q.push({dx, dy});
            }
        }
    }

    if (!vis[ex][ey])
    {
        cout << "NO" << endl;
    }
    else
    {
        cout << "YES" << endl;
        cout << dist[ex][ey] << endl;
        pair<int, int> P = {ex, ey};
        for (int i = dist[ex][ey]; i > 0; i--)
        {
            ans[i] = par[P.first][P.second];
            if (ans[i] == 'D')
                P = {P.first - 1, P.second};
            else if (ans[i] == 'U')
                P = {P.first + 1, P.second};
            else if (ans[i] == 'R')
                P = {P.first, P.second - 1};
            else if (ans[i] == 'L')
                P = {P.first, P.second + 1};
        }
        for (int i = 1; i <= dist[ex][ey]; i++)
            cout << ans[i];
        cout << endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}