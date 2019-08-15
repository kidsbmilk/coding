/*
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

void pushup(vector<int>& vi_seg, int index) {
	vi_seg[index] = max(vi_seg[index * 2], vi_seg[index * 2 + 1]);
}

// index表示vi_seg中的下标，是线段树中保存区间的下标，left和right是线段树中的区间上下限，这里以数组来存储二叉树，使用数组下标完美地表示了index与区间上下限的关系。
// 同时，index处的元素对应的是区间里的值，在这里表示区间内的最大值。
void build(const vector<int> &vi_origin, vector<int>& vi_seg, int index, int left, int right) { // 将vi_origin区间分隔，以二叉树的组织形式写入到vi_seg里，以vi_seg里的下标来组织父子节点关系。
	if (left == right) {
		vi_seg[index] = vi_origin[left];
		return;
	}
	int mid = (left + right) / 2;
	build(vi_origin, vi_seg, index * 2, left, mid);
	build(vi_origin, vi_seg, index * 2 + 1, mid + 1, right);
	pushup(vi_seg, index);
}

void update(vector<int>& vi_seg, int index, int left, int right, int x, int v) {
	if (left == x && right == x) {
		vi_seg[index] = v;
		return;
	}
	int mid = (left + right) / 2;
	if (x <= mid) {
		update(vi_seg, index * 2, left, mid, x, v);
	}
	else {
		update(vi_seg, index * 2 + 1, mid + 1, right, x, v);
	}
	pushup(vi_seg, index);
}

int query(const vector<int>& vi_seg, int index, int left, int right, int L, int R) {
	if (L <= left && right <= R) { // 不用怀疑这个[L, R]的区间大于[left, right]，从一开始就大，甚至直到搜索到叶子节点，可以画图看一看。
		// 这个如果写为L == left && right == R，会超内存限制，过不了！！！
		return vi_seg[index];
	}
	int mid = (left + right) / 2;
	int ans = 0;
	if (L <= mid) {
		ans = max(ans, query(vi_seg, index * 2, left, mid, L, R));
	}
	if(R > mid) {
		ans = max(ans, query(vi_seg, index * 2 + 1, mid + 1, right, L, R));
	}
	return ans;
}

int main() {
	IOS;
	int n, m;
	while (cin >> n >> m && n && m) {
		vector<int> vi_origin(n + 1, 0);
		for (int i = 1; i <= n; i++) { // 这里下标从1开始，为的是与下面建树区间保持一致，方便操作
			cin >> vi_origin[i];
		}
		vector<int> vi_seg(n * 3); // 有n个叶子节点的完全二叉树最多有2n - 1个节点，所以开辟2n个空间就可以了，只使用1~2*n-1的下标。
		// TODO：但是，n * 2竟然会Runtime Error，开到n * 3就可以了，不太明白为什么？？？
		build(vi_origin, vi_seg, 1, 1, n); // 第一个1表示线段树的二叉树形式的根节点存放在下标1处，后面的1与n表示建树、有效查询区间为1~n
		char c;
		int ix, iy;
		while (m--) {
			cin >> c >> ix >> iy;
			if (c == 'Q') {
				cout << query(vi_seg, 1, 1, n, ix, iy) << endl; // 这里的1, 1, n的含义跟build处的含义相同
			}
			else {
				update(vi_seg, 1, 1, n, ix, iy); // 这里的1, 1, n的含义跟build处的含义相同
			}
		}
	}
	return 0;
}
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushup(vector<int>& vi_seg, int index) {
	vi_seg[index] = max(vi_seg[index * 2], vi_seg[index * 2 + 1]);
}

// index表示vi_seg中的下标，是线段树中保存区间的下标，left和right是线段树中的区间上下限，这里以数组来存储二叉树，使用数组下标完美地表示了index与区间上下限的关系。
// 同时，index处的元素对应的是区间里的值，在这里表示区间内的最大值。
void build(const vector<int>& vi_origin, vector<int>& vi_seg, int index, int left, int right) { // 将vi_origin区间分隔，以二叉树的组织形式写入到vi_seg里，以vi_seg里的下标来组织父子节点关系。
	if (left == right) {
		vi_seg[index] = vi_origin[left];
		return;
	}
	int mid = (left + right) / 2;
	build(vi_origin, vi_seg, left_mode);
	build(vi_origin, vi_seg, right_mode);
	pushup(vi_seg, index);
}

void update(vector<int>& vi_seg, int index, int left, int right, int x, int v) {
	if (left == x && right == x) {
		vi_seg[index] = v;
		return;
	}
	int mid = (left + right) / 2;
	if (x <= mid) {
		update(vi_seg, left_mode, x, v);
	}
	else {
		update(vi_seg, right_mode, x, v);
	}
	pushup(vi_seg, index);
}

int query(const vector<int>& vi_seg, int index, int left, int right, int L, int R) {
	if (L <= left && right <= R) { // 不用怀疑这个[L, R]的区间大于[left, right]，从一开始就大，甚至直到搜索到叶子节点，可以画图看一看。
		// 这个如果写为L == left && right == R，会超内存限制，过不了！！！
		return vi_seg[index];
	}
	int mid = (left + right) / 2;
	int ans = 0;
	if (L <= mid) {
		ans = max(ans, query(vi_seg, left_mode, L, R));
	}
	if (R > mid) {
		ans = max(ans, query(vi_seg, right_mode, L, R));
	}
	return ans;
}

int main() {
	IOS;
	int n, m;
	while (cin >> n >> m && n && m) {
		vector<int> vi_origin(n + 1, 0);
		for (int i = 1; i <= n; i++) { // 这里下标从1开始，为的是与下面建树区间保持一致，方便操作
			cin >> vi_origin[i];
		}
		vector<int> vi_seg(n * 3); // 有n个叶子节点的完全二叉树最多有2n - 1个节点，所以开辟2n个空间就可以了，只使用1~2*n-1的下标。
		// TODO：但是，n * 2竟然会Runtime Error，开到n * 3就可以了，不太明白为什么？？？
		build(vi_origin, vi_seg, 1, 1, n); // 第一个1表示线段树的二叉树形式的根节点存放在下标1处，后面的1与n表示建树、有效查询区间为1~n
		char c;
		int ix, iy;
		while (m--) {
			cin >> c >> ix >> iy;
			if (c == 'Q') {
				cout << query(vi_seg, 1, 1, n, ix, iy) << endl; // 这里的1, 1, n的含义跟build处的含义相同
			}
			else {
				update(vi_seg, 1, 1, n, ix, iy); // 这里的1, 1, n的含义跟build处的含义相同
			}
		}
	}
	return 0;
}