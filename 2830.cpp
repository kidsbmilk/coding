#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

int main() {
	IOS;
	int n, m;
	while (cin >> n >> m && n && m) {
		vector<string> vs(n);
		for (int i = 0; i < n; i++) {
			cin >> vs[i];
		}
		vector<int> vi_height(m, 0);
		int imax = 0;
		for (int i = 0; i < n; i++) {
			vector<int> vi_left(m, 0);
			vector<int> vi_right(m, 0);
			for (int j = 0; j < m; j++) {
				vi_left[j] = vi_right[j] = j;
				if (vs[i][j] == '1') vi_height[j] += 1;
				else vi_height[j] = 0;
			}
			vector<int> vi_height_tp(vi_height);
			sort(vi_height_tp.begin(), vi_height_tp.end());
			for (int j = 0; j < m; j++) {
				while (vi_left[j] - 1 >= 0 && vi_height_tp[j] <= vi_height_tp[vi_left[j] - 1]) {
					vi_left[j] = vi_left[vi_left[j] - 1];
				}
			}
			for (int j = m - 1; j >= 0; j--) {
				while (vi_right[j] + 1 < m && vi_height_tp[j] <= vi_height_tp[vi_right[j] + 1]) {
					vi_right[j] = vi_right[vi_right[j] + 1];
				}
				imax = max(imax, (vi_right[j] - vi_left[j] + 1) * vi_height_tp[j]);
			}
		}
		cout << imax << endl;
	}
	return 0;
}