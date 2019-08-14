#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int c;
	while (cin >> c && c) {
		while (c--) {
			int n, m;
			cin >> n >> m;
			vector<vector<int> > vvi(n, vector<int>(m, 0));
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cin >> vvi[i][j];
				}
			}
			vector<vector<int> > vvi_b(n + 1, vector<int>(m + 1, -999999999)); // 注意这个初始化！
			vvi_b[1][1] = vvi[0][0];
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					int itp = max(vvi_b[i - 1][j], vvi_b[i][j - 1]);
					for (int k = 1; k <= j / 2; k++) {
						if (j % k == 0) {
							itp = max(itp, vvi_b[i][k]);
						}
					}
					vvi_b[i][j] = max(vvi_b[i][j], itp + vvi[i - 1][j - 1]);
				}
			}
			cout << vvi_b[n][m] << endl;
		}
	}
	return 0;
}