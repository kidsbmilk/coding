#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 要认真分析题目上，本质上跟1025一样，最长上升子序列。

int main() {
	int n;
	while (cin >> n && n) {
		vector<int> vi(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> vi[i];
		}
		vector<int> vi_b;
		for (int i = 0; i < n; i++) {
			int indtp = lower_bound(vi_b.begin(), vi_b.end(), vi[i]) - vi_b.begin();
			// cout << vi_b.size() - 1 << endl; // 非常大的整数！
			if (vi_b.size() > 0 && indtp <= vi_b.size() - 1) {
				vi_b[indtp] = vi[i];
			}
			else {
				vi_b.push_back(vi[i]);
			}
		}
		cout << vi_b.size() << endl;
	}
	return 0;
}