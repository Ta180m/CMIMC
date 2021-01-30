#include <bits/stdc++.h>
#define f first
#define s second
using namespace std;
using ll = long long;
using ii = pair<int, int>;
constexpr int MX = 21e4+5;

ii P[MX];
int R[105];

int main() {
	if (fopen("in", "r")) freopen("in", "r", stdin), freopen("out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);

    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> P[i].f >> P[i].s;
    sort(P, P+N);
    int M; cin >> M;
    for (int i = 0; i < M; ++i) cin >> R[i];

    int sum = 0;
    for (int i = 0; i < M; ++i) sum += R[i];
    int j = 0;
    for (int i = 0; i < M; ++i) {
        int k = min(int(ceil(j+(double)R[i]/sum*N)), N);
        ii cen(0, 0);
        for (int a = j; a < k; ++a) {
            cen.f += P[a].f, cen.s += P[a].s;
        }
        cout << (double)cen.f / (k-j) << ' ' << (double)cen.s / (k-j) << '\n';
        j = k;
    }

}
