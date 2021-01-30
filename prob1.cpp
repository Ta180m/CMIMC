#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

bool comp[200005];

//#define BOUND 40

void find_all(int m, int min_factor, int max_factor, vector<int>& res)
{
    for (int i = 2; i <= m; i++) {
        int cur = i;
        bool good = true;
        for (int j = 2; j * j <= i; j++) {
            while (cur % j == 0) {
                cur /= j;
                if (j < min_factor || j > max_factor) good = false;
            }
        }
        if (cur < min_factor || cur > max_factor) good = false;
        if (good) res.push_back(i);
    }
}

int solve_bound(int n, int m)
{
    int BOUND;
    if (m == 40000) {
        BOUND = 46;
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

int main()
{
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 2; i <= 200000; i++) {
       if (comp[i]) continue;
       for (int j = i * 2; j <= 200000; j += i) {
           comp[j] = true;
       }
    }
    if (n == 2) {
        solve_bound(n, m);
    } else {
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
    }
    return 0;
}
