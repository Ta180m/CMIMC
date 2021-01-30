#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <chrono>
#include <random>
#include <cstring>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int r, c, n;
int startx, starty;
char grid[1005][1005];
char s[1005];

int perm[205];
int pperm[205];
int sx[205], sy[205];
int x[205], y[205];

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
            if (grid[nxt.first][nxt.second] == 'X') continue;
            vis[nxt.first][nxt.second] = true;
            prev_dx[nxt.first][nxt.second] = -dx[i];
            prev_dy[nxt.first][nxt.second] = -dy[i];
            bfs.push(nxt);
        }
    }
}

int get_score(vector<pair<int, int> >& ops)
{
    for (int i = 1; i <= n; i++) {
        x[i] = sx[i]; y[i] = sy[i];
    }
    for (int idx = 1; idx <= n; idx++) {
        int i = perm[idx];
        while (x[i] != startx || y[i] != starty) {
            int d_x = prev_dx[x[i]][y[i]];
            int d_y = prev_dy[x[i]][y[i]];
            for (int j = 1; j <= n; j++) {
                if (x[j] == startx && y[j] == starty) continue;
                if (grid[x[j] + d_x][y[j] + d_y] == 'X') continue;
                x[j] += d_x;
                y[j] += d_y;
            }
            ops.push_back(make_pair(d_x, d_y));
        }
    }
    return (int)ops.size();
}

int main()
{
    int testid;
    scanf("%d%d%d%d", &r, &c, &n, &testid);
    int tmp = 1;
    for (int i = 0; i <= r + 1; i++) {
        for (int j = 0; j <= c + 1; j++) {
            grid[i][j] = 'X';
        }
    }
    //fprintf(stderr, "Here");
    for (int i = 1; i <= r; i++) {
        scanf("%s", s + 1);
        for (int j = 1; j <= c; j++) {
            grid[i][j] = s[j];
            if (grid[i][j] == 'E') {
                startx = i, starty = j;
            } else if (grid[i][j] == 'R') {
                sx[tmp] = i; sy[tmp] = j; tmp++;
            }
        }
    }
    for (int i = 1; i <= n; i++) perm[i] = i;
    //fprintf(stderr, "Here");
    BFS();
    /*for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            printf("%d %d ", prev_dx[i][j], prev_dy[i][j]);
        }
        printf("\n");
    }*/
    //fprintf(stderr, "Here");
    int curscore = 1000000000;
    while (true) {
        for (int i = 1; i <= n; i++) pperm[i] = perm[i];
        for (int i = 1; i <= 10; i++) {
            int a = rng() % n + 1;
            int b = a + (rng() % 5) + 1;
            if (b > n) continue;
            swap(perm[a], perm[b]);
        }
        vector<pair<int, int> > ops;
        int newscore = get_score(ops);
        if (newscore < curscore) {
            char out_file[10];
            strcpy(out_file, "3_1.out");
            out_file[2] = '0' + testid;
            FILE* file = fopen(out_file, "w");
            for (int i = 0; i < ops.size(); i++) {
                if (ops[i].first == 0) {
                    if (ops[i].second == 1) {
                        fprintf(file, "R");
                    } else {
                        fprintf(file, "L");
                    }
                } else if (ops[i].first == -1) {
                    fprintf(file, "U");
                } else {
                    fprintf(file, "D");
                }
            }
            printf("%d\n", newscore);
            fclose(file);
            out_file[0] = 'p';
            file = fopen(out_file, "w");
            for (int i = 1; i <= n; i++) fprintf(file, "%d", perm[i]);
            fclose(file);
            curscore = newscore;
        } else {
            for (int i = 1; i <= n; i++) perm[i] = pperm[i];
        }
    }
    return 0;
}
