/*
// 这个超时，是因为找右边界时，没有从右往左找，没有发挥出动规的优势。
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

int main() {
	IOS;
	int m, n;
	while (cin >> m >> n && m && n) {
		vector<string> vs(m);
		for (int i = 0; i < m; i++) {
			cin >> vs[i];
		}
		int nowc = 'a';
		int imax = 0;
		while (nowc <= 'c') {
			vector<int> vi_height(n, 0);
			for (int i = 0; i < m; i++) {
				vector<int> vi_left(n, 0);
				vector<int> vi_right(n, 0);
				for (int j = 0; j < n; j++) {
					vi_left[j] = vi_right[j] = j; // 初始化每列的左右边界
					if (nowc == 'a') {
						if (vs[i][j] == 'a' || vs[i][j] == 'w' || vs[i][j] == 'y' || vs[i][j] == 'z') {
							vi_height[j] += 1;
						} else {
							vi_height[j] = 0;
						}
					}
					else if (nowc == 'b') {
						if (vs[i][j] == 'b' || vs[i][j] == 'w' || vs[i][j] == 'x' || vs[i][j] == 'z') {
							vi_height[j] += 1;
						} else {
							vi_height[j] = 0;
						}
					} else if (nowc == 'c') {
						if (vs[i][j] == 'c' || vs[i][j] == 'x' || vs[i][j] == 'y' || vs[i][j] == 'z') {
							vi_height[j] += 1;
						} else {
							vi_height[j] = 0;
						}
					}
				}
				// 找每列的左右边界
				for (int j = 0; j < n; j++) {
					while (vi_left[j] - 1 >= 0 && vi_height[j] <= vi_height[vi_left[j] - 1]) {
						vi_left[j] = vi_left[vi_left[j] - 1];
					}
					while (vi_right[j] + 1 < n && vi_height[j] <= vi_height[vi_right[j] + 1]) { // 这个超时，是因为找右边界时，没有从右往左找，没有发挥出动规的优势。
						vi_right[j] = vi_right[vi_right[j] + 1];
					}
					imax = max(imax, (vi_right[j] - vi_left[j] + 1) * vi_height[j]);
				}
			}
			++nowc;
		}
		cout << imax << endl;
	}
	return 0;
}
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

int main() {
	IOS;
	int m, n;
	while (cin >> m >> n && m && n) {
		vector<string> vs(m);
		for (int i = 0; i < m; i++) {
			cin >> vs[i];
		}
		int nowc = 'a';
		int imax = 0;
		while (nowc <= 'c') {
			vector<int> vi_height(n, 0);
			for (int i = 0; i < m; i++) {
				vector<int> vi_left(n, 0);
				vector<int> vi_right(n, 0);
				for (int j = 0; j < n; j++) {
					vi_left[j] = vi_right[j] = j; // 初始化每列的左右边界
					if (nowc == 'a') {
						if (vs[i][j] == 'a' || vs[i][j] == 'w' || vs[i][j] == 'y' || vs[i][j] == 'z') {
							vi_height[j] += 1;
						}
						else {
							vi_height[j] = 0;
						}
					}
					else if (nowc == 'b') {
						if (vs[i][j] == 'b' || vs[i][j] == 'w' || vs[i][j] == 'x' || vs[i][j] == 'z') {
							vi_height[j] += 1;
						}
						else {
							vi_height[j] = 0;
						}
					}
					else if (nowc == 'c') {
						if (vs[i][j] == 'c' || vs[i][j] == 'x' || vs[i][j] == 'y' || vs[i][j] == 'z') {
							vi_height[j] += 1;
						}
						else {
							vi_height[j] = 0;
						}
					}
				}
				// 找每列的左右边界
				for (int j = 0; j < n; j++) {
					while (vi_left[j] - 1 >= 0 && vi_height[j] <= vi_height[vi_left[j] - 1]) {
						vi_left[j] = vi_left[vi_left[j] - 1];
					}
				}
				for (int j = n - 1; j >= 0; j--) { // 找右边界时，从右往左找，发挥出动规的优势
					while (vi_right[j] + 1 < n && vi_height[j] <= vi_height[vi_right[j] + 1]) {
						vi_right[j] = vi_right[vi_right[j] + 1];
					}
					imax = max(imax, (vi_right[j] - vi_left[j] + 1) * vi_height[j]);
				}
			}
			++nowc;
		}
		cout << imax << endl;
	}
	return 0;
}

/*
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdio>
using namespace std;

int R, C, h[1001], l[1001], r[1001];
char s[1001][1001];

int solve(int kind) {
	for (int i = 1; i <= C; ++i) {
		h[i] = 0;
	}
	int ans = 0;
	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			if (kind == 0) {
				if (s[i][j] == 'a' || s[i][j] == 'w' || s[i][j] == 'y' || s[i][j] == 'z') h[j] = h[j] + 1;
				else h[j] = 0;
			}
			if (kind == 1) {
				if (s[i][j] == 'b' || s[i][j] == 'w' || s[i][j] == 'x' || s[i][j] == 'z') h[j] = h[j] + 1;
				else h[j] = 0;
			}
			if (kind == 2) {
				if (s[i][j] == 'c' || s[i][j] == 'x' || s[i][j] == 'y' || s[i][j] == 'z') h[j] = h[j] + 1;
				else h[j] = 0;
			}
			l[j] = r[j] = j;
		}
		h[0] = -1;
		for (int j = 1; j <= C; ++j) {
			while (h[j] <= h[l[j] - 1]) {
				l[j] = l[l[j] - 1];
			}
			
		}
		h[C + 1] = -1;
		for (int j = C - 1; j >= 1; --j) {
			while (h[j] <= h[r[j] + 1]) {
				r[j] = r[r[j] + 1];
			}
			ans = max(ans, (r[j] - l[j] + 1) * h[j]);
		}
	}
	return ans;

}
int main() {
	while (scanf("%d %d", &R, &C) != EOF) {
		for (int i = 1; i <= R; ++i) {
			for (int j = 1; j <= C; ++j) {
				s[i][j] = getchar();
				while (s[i][j] < 'a' || s[i][j] > 'z') {
					s[i][j] = getchar();
				}
			}
		}
		int ans = 0;
		ans = max(ans, solve(0));
		ans = max(ans, solve(1));
		ans = max(ans, solve(2));
		printf("%d\n", ans);
	}
}
*/