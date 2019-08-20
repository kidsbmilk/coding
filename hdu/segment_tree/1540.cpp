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
		vi_seg[index] = vi_seg_left[index] = vi_seg_right[index] = b; // ���bΪ1��ʾ���ã�Ϊ0��ʾ�����á������pushup������ϲ�ڵ㡣
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
		if (x >= mid - vi_seg_right[index * 2] + 1) { // index * 2�ڵ���Ҳ�������������Ŀռ䣬�˿ռ����x������Ҫ����index * 2 + 1�ڵ�������ͨ�Ŀռ䡣
			return query(vi_seg, vi_seg_left, vi_seg_right, left_mode, x) + query(vi_seg, vi_seg_left, vi_seg_right, right_mode, mid + 1);
		}
		else {
			return query(vi_seg, vi_seg_left, vi_seg_right, left_mode, x);
		}
	}
	else {
		if (x <= mid + vi_seg_left[index * 2 + 1]) { // index * 2 + 1�ڵ��������Ҳ��������Ŀռ䣬�˿ռ����x������Ҫ����index * 2�ڵ�ǰ�����ͨ�Ŀռ䡣
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