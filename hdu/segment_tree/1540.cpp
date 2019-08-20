#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushup(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, int index, int count) {
	int left = index * 2;
	int right = left + 1;
	vi_seg_left[index] = vi_seg_left[left];
	if (vi_seg_left[left] == count - count / 2) {
		vi_seg_left[index] += vi_seg_left[right];
	}
	vi_seg_right[index] = vi_seg_right[right];
	if (vi_seg_right[index] == count / 2) {
		vi_seg_right[index] += vi_seg_right[left];
	}
	vi_seg[index] = max(max(vi_seg[left], vi_seg[right]), vi_seg_left[right] + vi_seg_right[left]);
}

void update(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, int index, int left, int right, int x, int b) {
	if (left == right) {
		vi_seg[index] = vi_seg_left[index] = vi_seg_right[index] = b; // 这个b为1表示可用，为0表示不可用。下面的pushup会更新上层节点。
		return;
	}
	int mid = (left + right) / 2;
	if (x <= mid) {
		update(vi_seg, vi_seg_left, vi_seg_right, left_mode, x, b);
	}
	else {
		update(vi_seg, vi_seg_left, vi_seg_right, right_mode, x, b);
	}
	pushup(vi_seg, vi_seg_left, vi_seg_right, index, right - left + 1);
}

int query(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, int index, int left, int right, int x) {
	if (left == right || vi_seg[index] == 0 || vi_seg[index] == right - left + 1) {
		return vi_seg[index];
	}
	int mid = (left + right) / 2;
	if (x <= mid) {
		if (x >= mid - vi_seg_right[index * 2] + 1) { // index * 2节点从右侧往左查找连续的空间，此空间包含x，所以要查找index * 2 + 1节点后面可连通的空间。
			return query(vi_seg, vi_seg_left, vi_seg_right, left_mode, x) + query(vi_seg, vi_seg_left, vi_seg_right, right_mode, mid + 1);
		}
		else {
			return query(vi_seg, vi_seg_left, vi_seg_right, left_mode, x);
		}
	}
	else {
		if (x <= mid + vi_seg_left[index * 2 + 1]) { // index * 2 + 1节点从左侧往右查找连续的空间，此空间包含x，所以要查找index * 2节点前面可连通的空间。
			return query(vi_seg, vi_seg_left, vi_seg_right, right_mode, x) + query(vi_seg, vi_seg_left, vi_seg_right, left_mode, mid);
		}
		else {
			return query(vi_seg, vi_seg_left, vi_seg_right, right_mode, x);
		}
	}
}

void build(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, int index, int left, int right) {
	vi_seg[index] = vi_seg_left[index] = vi_seg_right[index] = right - left + 1;
	if (left == right) {
		return;
	}
	int mid = (left + right) / 2;
	build(vi_seg, vi_seg_left, vi_seg_right, left_mode);
	build(vi_seg, vi_seg_left, vi_seg_right, right_mode);
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n && m) {
		vector<int> vi_seg(n * 4, 0);
		vector<int> vi_seg_left(vi_seg);
		vector<int> vi_seg_right(vi_seg);
		build(vi_seg, vi_seg_left, vi_seg_right, 1, 1, n);
		stack<int> si;
		for (int i = 0; i < m; i++) {
			char ctp[2];
			scanf("%s", &ctp);
			if (ctp[0] == 'D') {
				int itp;
				scanf("%d", &itp);
				si.push(itp);
				update(vi_seg, vi_seg_left, vi_seg_right, 1, 1, n, itp, 0);
			}
			else if (ctp[0] == 'R') {
				int itp = si.top();
				si.pop();
				update(vi_seg, vi_seg_left, vi_seg_right, 1, 1, n, itp, 1);
			}
			else { // ctp[0] == 'Q'
				int itp;
				scanf("%d", &itp);
				printf("%d\n", query(vi_seg, vi_seg_left, vi_seg_right, 1, 1, n, itp));
			}
		}
	}
	return 0;
}