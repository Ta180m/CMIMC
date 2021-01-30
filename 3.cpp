#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

int r, c, n;
int startx, starty;
char grid[1005][1005];
char s[1005];

int perm[205];
int x[205], y[205];
int curx[205], cury[205];

int prev_dx[1005][1005];
int prev_dy[1005][1005];
bool vis[1005][1005];

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void BFS()
{
    queue<pair<int, int> > bfs;
    bfs.push(make_pair(startx, starty));
    vis[startx][starty] = true;
    while (!bfs.empty()) {
        pair<int, int> cur = bfs.front(); bfs.pop();
        for (int i = 0; i < 4; i++) {
            pair<int, int> nxt = cur;
            nxt.first += dx[i];
            nxt.second += dy[i];
            if (vis[nxt.first][nxt.second]) continue;
            vis[nxt.first][nxt.second] = true;
            prev_dx[nxt.first][nxt.second] = -dx[i];
            prev_dy[nxt.first][nxt.second] = -dy[i];
            bfs.push_back(nxt);
        }
    }
}

int get_score()
{
    for (int i = 1; i <= n; i++) {
        curx[i] = x[i]; cury
    }
}

int main()
{
    scanf("%d%d%d", &r, &c, &n);
    int tmp = 1;
    for (int i = 0; i <= r + 1; i++) {
        for (int j = 0; j <= c + 1; j++) {
            grid[i][j] = 'X';
        }
    }
    for (int i = 1; i <= r; i++) {
        scanf("%s", s + 1);
        for (int j = 1; j <= c; j++) {
            grid[i][j] = s[j];
            if (grid[i][j] == 'E') {
                startx = i, starty = j;
            } else if (grid[i][j] == 'R') {
                x[tmp] = i; y[tmp] = j; tmp++;
            }
        }
    }
    for (int i = 1; i <= n; i++) perm[i] = i;
    BFS();

}
