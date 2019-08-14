#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

// 最大子矩阵和：https://blog.csdn.net/sinat_40948489/article/details/80274460 与1505有点像
// 1559是二维动规。

int main() {
	int t;
	while (cin >> t && t) {
		while (t--) { // 之前竟然忘记这个while循环了！人家题目说了，多组数据。
			int m, n, x, y;
			cin >> m >> n >> x >> y;
			vector<vector<int> > vvi(m + 1, vector<int>(n + 1, 0));
			int imax = 0;
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= n; j++) {
					// cin >> vvi[i][j];
					scanf("%d", &vvi[i][j]);
					vvi[i][j] += vvi[i - 1][j] + vvi[i][j - 1] - vvi[i - 1][j - 1];
					if (i >= x && j >= y) {
						int itp = vvi[i][j] - vvi[i - x][j] - vvi[i][j - y] + vvi[i - x][j - y];
						if (itp > imax) {
							imax = itp;
						}
					}
					/*
					// 这个颠倒了行列，是错误的代码，但是因为数据较弱，也能过。
					if (i >= y && j >= x) {
						int itp = vvi[i][j] - vvi[i - y][j] - vvi[i][j - x] + vvi[i - y][j - x];
						if (itp > imax) {
							imax = itp;
						}
					}*/
				}
			}
			cout << imax << endl;
		}
	}
	return 0;
}
