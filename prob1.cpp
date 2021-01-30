#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool comp[200005];

//#define BOUND 40

int min_f[200005], max_f[200005];

void find_all(int m, int min_factor, int max_factor, vector<int>& res)
{
    for (int i = 2; i <= m; i++) {
        if (min_f[i] >= min_factor && max_f[i] <= max_factor) {
            res.push_back(i);
        }
    }
}

int solve_bound(int n, int m)
{
    int BOUND;
    if (m == 40000) {
        BOUND = 50;
    } else if (m == 4000) {
        BOUND = 20;
    } else {
        BOUND = 10;
    }
    vector<int> group1, group2;
    find_all(m, 1, BOUND, group1);
    find_all(m, BOUND + 1, m, group2);
    fprintf(stderr, "%d %d\n", (int)group1.size(), (int)group2.size());
    for (int i = 0; i < min(group1.size(), group2.size()); i++) {
        printf("%d ", group1[i]);
    }
    printf("\n");
    for (int i = 0; i < min(group1.size(), group2.size()); i++) {
        printf("%d ", group2[i]);
    }
}

bool f[10][4005];
int pre[10][4005];

void do_dp(int n, int m, int min_cnt)
{
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j] = false;
        }
    }
    f[0][1] = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            if (j != m && comp[j + 1]) continue;
            for (int k = 1; k < j; k++) {
                if (comp[k+1]) continue;
                if (!f[i-1][k]) continue;
                vector<int> res; find_all(m, k+1, j, res);
                if (res.size() < min_cnt) continue;
                f[i][j] = true;
                pre[i][j] = k;
                break;
            }
        }
    }
}

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 2; i <= m; i++) {
        min_f[i] = 10000000;
        max_f[i] = 0;
        int cur = i;
        bool good = true;
        for (int j = 2; j * j <= i; j++) {
            while (cur % j == 0) {
                cur /= j;
                max_f[i] = max(max_f[i], j);
                min_f[i] = min(min_f[i], j);
                good = false;
            }
        }
        if (cur > 1) {
            max_f[i] = max(max_f[i], cur);
            min_f[i] = min(min_f[i], cur);
        }
        //if (cur != 1 && (cur < min_factor || cur > max_factor)) good = false;
        //if (good) res.push_back(i);
        printf("%d %d\n", min_f[i], max_f[i]);
    }
    for (int i = 2; i <= 200000; i++) {
       if (comp[i]) continue;
       for (int j = i * 2; j <= 200000; j += i) {
           comp[j] = true;
       }
    }
    if (n == 2) {
        solve_bound(n, m);
    } else {
        int l = 1; int r = m;
        while (l < r) {
            int mid = (l + r) / 2 + 1;
            do_dp(n, m, mid);
            if (f[n][m]) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        do_dp(n, m, l);
        vector<int> ans[20];
        int cur = m;
        for (int i = n; i >= 1; i--) {
            find_all(m, pre[i][cur] + 1, cur, ans[i]);
            cur = pre[i][cur];
        }
        for (int i = 1; i <= n; i++) {
            printf("1 ");
            for (int j = 0; j < l; j++) {
                printf("%d ", ans[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}

/*
vector<int> primes;
int prime_above_cnt = 0;
for (int i = 2; i <= m; i++) {
    if (!comp[i]) {
        primes.push_back(i);
    }
}
printf("%d\n", prime_above_cnt);
int cnt = primes.size() / n;
for (int i = 0; i < n; i++) {
    for (int j = i * cnt; j < (i + 1) * cnt; j++) {
        printf("%d ", primes[j]);
    }
    printf("\n");
}
*/
