#include<iostream>
#include<vector>
using namespace std;

// 跟1505非常像

int main() {
	int n;
	while (cin >> n && n) {
		vector<vector<int> > vvi(n + 1, vector<int> (n + 1, 0));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> vvi[i][j];
				vvi[i][j] += vvi[i][j - 1];
			}
		}
		int imax = vvi[0][0];
		for (int i = 1; i < n; i++) { // 列的起始下标
			for (int j = i + 1; j <= n; j++) { // 列的终止下标
				int isum = 0; // 这内部的代码就是最大连续子序列和
				for (int k = 1; k <= n; k++) {
					isum += vvi[k][j] - vvi[k][i - 1]; // 加上当前行的长度
					if (isum < 0) isum = 0;
					if (isum > imax) imax = isum;
				}
			}
		}
		cout << imax << endl;
	}
	return 0;
}