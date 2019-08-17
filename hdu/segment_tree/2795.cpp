#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushup(vector<int>& vi_seg, int index) {
	vi_seg[index] = max(vi_seg[index * 2], vi_seg[index * 2 + 1]);
}

void update(vector<int>& vi_seg, int index, int left, int right, int v) {
	if (left == right) {
		vi_seg[index] -= v;
		cout << left << endl;
		return;
	}
	int mid = (left + right) / 2;
	if (vi_seg[index * 2] >= v) { // 这里采用域比较，也就是vi_seg里的值一比较，不使用传统的边界、范围来比较。而且，先左子树优先。
		// 这里只所以可以用域来表示可用的面积，是因为题目说了，从上到下、从左到右张贴宣传单。
		update(vi_seg, left_mode, v);
	}
	else {
		update(vi_seg, right_mode, v);
	}
	pushup(vi_seg, index);
}

int main() {
	IOS;
	int h, w, n;
	while (cin >> h >> w >> n && h && w && n) {
		int isize = min(h, n);
		vector<int> vi_seg(isize * 4 + 10, w);
		for (int i = 0; i < n; i++) {
			int itp;
			cin >> itp;
			if (vi_seg[1] < itp) {
				cout << -1 << endl;
			}
			else {
				update(vi_seg, 1, 1, isize, itp);
			}
		}
	}
	return 0;
}