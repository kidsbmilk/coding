/*
// 动态规划，390ms
#include<iostream>
#include<vector>
#include<algorithm> // min, max
using namespace std;

// 最大子矩阵和：https://blog.csdn.net/sinat_40948489/article/details/80274460 ，1081，与1505有点像

int main() {
	int k;
	while (cin >> k && k) {
		while (k--) {
			int m, n;
			cin >> m >> n;
			vector<vector<int> > vvi(m, vector<int>(n, 0));
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					char ctp;
					cin >> ctp;
					vvi[i][j] = ctp;
				}
			}
			vector<int> vi_height(n, 0);
			int imax = 0;
			for (int i = 0; i < m; i++) { // 从每一行开始扫描、计算，相当于把1506题的一维扩展到多维了。
				vector<int> vi_start_col(n, 0);
				vector<int> vi_end_col(n, 0);
				for (int j = 0; j < n; j++) {
					vi_start_col[j] = j;
					vi_end_col[j] = j;
					if (vvi[i][j] == 'F') vi_height[j] ++; // 这个vi_height贯穿了所有行，形成当前矩阵的宽、高度。
					else vi_height[j] = 0;
				}
				for (int j = 0; j < n; j++) {
					if (vi_height[j] == 0) continue; // 在单调栈的实现中，不能有continue，因为跳过0的话，会使栈中不存在相应的下标，导致vi_start_col[j] = 0。
					// 动态规则中可以有continue加速计算，是因为动归中是自已-1来判断的，不会错误高度为0的下标。
					while (vi_start_col[j] - 1 >= 0 && vi_height[j] <= vi_height[vi_start_col[j] - 1]) {
						vi_start_col[j] = vi_start_col[vi_start_col[j] - 1]; // 更新vi_height[j]高度下的矩阵的左边界，即长度的起始下标。
					}
				}
				for (int j = n - 1; j >= 0; j--) {
					if (vi_height[j] == 0) continue; // 在单调栈的实现中，不能有continue，因为跳过0的话，会使栈中不存在相应的下标，导致vi_start_col[j] = n - 1。
					// 动态规则中可以有continue加速计算，是因为动归中是自已-1来判断的，不会错误高度为0的下标。
					while (vi_end_col[j] + 1 <= n - 1 && vi_height[j] <= vi_height[vi_end_col[j] + 1]) {
						vi_end_col[j] = vi_end_col[vi_end_col[j] + 1]; // 更新vi_height[j]高度下的矩阵的右边界，即长度的结束下标。
					}
				}
				for (int j = 0; j < n; j++) {
					imax = max(imax, (vi_end_col[j] - vi_start_col[j] + 1) * vi_height[j] * 3);
				}
			}
			cout << imax << endl;
		}
	}
	return 0;
}
*/

// 单调栈，514ms
#include<iostream>
#include<vector>
#include<algorithm> // min, max
#include<stack>
using namespace std;

int main() {
	int k;
	while (cin >> k && k) {
		while (k--) {
			int m, n;
			cin >> m >> n;
			vector<vector<int> > vvi(m, vector<int>(n, 0));
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					char ctp;
					cin >> ctp;
					vvi[i][j] = ctp;
				}
			}
			vector<int> vi_height(n, 0);
			int imax = 0;
			for (int i = 0; i < m; i++) { // 从每一行开始扫描、计算，相当于把1506题的一维扩展到多维了。
				vector<int> vi_start_col(n, 0);
				vector<int> vi_end_col(n, 0);
				for (int j = 0; j < n; j++) {
					vi_start_col[j] = j;
					vi_end_col[j] = j;
					if (vvi[i][j] == 'F') vi_height[j] ++; // 这个vi_height贯穿了所有行，形成当前矩阵的宽、高度。
					else vi_height[j] = 0;
				}
				stack<int> si;
				for (int j = 0; j < n; j++) {
					// if (vi_height[j] == 0) continue; // 在单调栈的实现中，不能有continue，因为跳过0的话，会使栈中不存在相应的下标，导致vi_start_col[j] = 0。
					// 动态规则中可以有continue加速计算，是因为动归中是自已-1来判断的，不会错误高度为0的下标。
					while (si.size() && vi_height[si.top()] >= vi_height[j]) {
						si.pop();
					}
					// 更新vi_height[j]高度下的矩阵的左边界，即长度的起始下标。
					if (si.empty()) vi_start_col[j] = 0;
					else {
						vi_start_col[j] = si.top() + 1;
					}
					si.push(j);
				}
				stack<int> ().swap(si);
				for (int j = n - 1; j >= 0; j--) {
					// if (vi_height[j] == 0) continue; // 在单调栈的实现中，不能有continue，因为跳过0的话，会使栈中不存在相应的下标，导致vi_start_col[j] = n - 1。
					// 动态规则中可以有continue加速计算，是因为动归中是自已-1来判断的，不会错误高度为0的下标。
					while (si.size() && vi_height[si.top()] >= vi_height[j]) {
						si.pop();
					}
					// 更新vi_height[j]高度下的矩阵的右边界，即长度的结束下标。
					if (si.empty()) vi_end_col[j] = n - 1;
					else {
						vi_end_col[j] = si.top() - 1;
					}
					si.push(j);
				}
				for (int j = 0; j < n; j++) {
					imax = max(imax, (vi_end_col[j] - vi_start_col[j] + 1) * vi_height[j] * 3);
				}
			}
			cout << imax << endl;
		}
	}
	return 0;
}