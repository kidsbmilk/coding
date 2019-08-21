// 对比hdu 1540, hdu 2871

#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushdown(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int count) {
	if (vi_lazy[index] != -1) {
		int left = index * 2;
		int right = left + 1;
		vi_lazy[left] = vi_lazy[right] = vi_lazy[index];
		vi_seg[left] = vi_seg_left[left] = vi_seg_right[left] = (vi_lazy[index] ? 0 : (count - (count / 2))); // vi_lazy为0表示清空区间，vi_lazy为1表示占用区间
		vi_seg[right] = vi_seg_left[right] = vi_seg_right[right] = (vi_lazy[index] ? 0 : count / 2); // 右孩子值
		vi_lazy[index] = -1;
	}
}

void pushup(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int count) {
	int left = index * 2;
	int right = left + 1;
	vi_seg_left[index] = vi_seg_left[left]; // vi_seg_left表示从左起的连续空间，从左子树加到右子树
	if (vi_seg_left[left] == count - (count / 2)) {
		vi_seg_left[index] += vi_seg_left[right]; // vi_seg_left[right]表示右子节点从左开始的连续空间。
	}
	vi_seg_right[index] = vi_seg_right[right]; // vi_seg_right表示从右起的连续空间，从右子树加到左子树
	if (vi_seg_right[right] == count / 2) {
		vi_seg_right[index] += vi_seg_right[left]; // vi_seg_right[left]表示左子节点从右开始的连续空间。
	}
	vi_seg[index] = max(max(vi_seg[left], vi_seg[right]), vi_seg_left[right] + vi_seg_right[left]);
}

// 这里是查找一个范围，所以有L、R这两个边界，对比hdu 1540。
void update(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int left, int right, int L, int R, int b) {
	if (L <= left && right <= R) {
		vi_seg[index] = vi_seg_left[index] = vi_seg_right[index] = (b ? 0 : right - left + 1);
		vi_lazy[index] = b;
		return;
	}
	pushdown(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, index, right - left + 1);
	int mid = (left + right) / 2;
	// 下面两个if可以写为：
	/*
	if (R <= mid) {
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode, L, R, b);
	}
	else if (L > mid) {
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode, L, R, b);
	}
	else {
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode, L, mid, b);
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode, mid + 1, R, b);
	}
	*/
	if (L <= mid) {
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode, L, R, b); // 注意：这个还是L、R，并没有变为L、mid。对比上面的写法。
	}
	if (mid < R) { // 注意：不是else if，之前因这里出错了。
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode, L, R, b); // 注意：这个还是L、R，并没有变为mid + 1、R。对比上面的写法。
	}
	pushup(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, index, right - left + 1);
}

int query(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int left, int right, int value) {
	if (left == right) {
		return left;
	}
	pushdown(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, index, right - left + 1);
	int mid = (left + right) / 2;
	// 注意：1、2、3的顺序不能变，查找可用空间的起始下标时，始终遵循从左到右的查询顺序。
	if (vi_seg[index * 2] >= value) { // 1
		return query(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode, value);
	}
	else if (vi_seg_left[index * 2 + 1] + vi_seg_right[index * 2] >= value) { // 2
		return mid - vi_seg_right[index * 2] + 1;
	}
	return query(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode, value); // 3
}

void build(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int left, int right) {
	vi_seg[index] = vi_seg_left[index] = vi_seg_right[index] = right - left + 1;
	vi_lazy[index] = -1;
	if (left == right) return;
	int mid = (left + right) / 2;
	build(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode);
	build(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode);
}

int main() {
	IOS;
	int n, m;
	// while (cin >> n >> m && n && m) {
	while(scanf("%d %d", &n, &m) == 2 && n && m) {
		vector<int> vi_seg(n * 4);
		vector<int> vi_seg_left(vi_seg);
		vector<int> vi_seg_right(vi_seg);
		vector<int> vi_lazy(vi_seg);
		build(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n);
		for (int i = 0; i < m; i++) {
			int q, s, e;
			scanf("%d %d", &q, &s);
			if (q == 1) {
				if (vi_seg[1] < s) {
					printf("0\n");
					continue;
				}
				int itp = query(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, s);
				printf("%d\n", itp);
				update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, itp, itp + s - 1, 1);
			}
			else {
				scanf("%d", &e);
				update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, s, s + e - 1, 0);
			}
		}
	}
	return 0;
}