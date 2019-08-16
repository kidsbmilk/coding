#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushup(vector<int>& vi_seg, int index) {
	vi_seg[index] = vi_seg[index * 2] + vi_seg[index * 2 + 1];
}

void pushdown(vector<int>& vi_seg, vector<int>& vi_lazy, int index, int left, int right) {
	if (vi_lazy[index]) {
		int mid = (left + right) / 2;
		vi_lazy[index * 2] = vi_lazy[index * 2 + 1] = vi_lazy[index];
		vi_seg[index * 2] = (mid - left + 1) * vi_lazy[index * 2];
		vi_seg[index * 2 + 1] = (right - mid) * vi_lazy[index * 2 + 1]; // right - (mid + 1) + 1 ===> right - mid
		vi_lazy[index] = 0;
	}
}

void update(vector<int>& vi_seg, vector<int>& vi_lazy, int index, int left, int right, int L, int R, int V) {
	if (L == left && right == R) { // 试试换成<=
		vi_seg[index] = (right - left + 1) * V;
		vi_lazy[index] = V;
		return;
	}
	int mid = (left + right) / 2;
	pushdown(vi_seg, vi_lazy, index, left, right); // 更新下层子区间之前，先将以前的更新应用到下层子区间上。
	if (R <= mid) update(vi_seg, vi_lazy, left_mode, L, R, V);
	else if (L > mid) update(vi_seg, vi_lazy, right_mode, L, R, V);
	else {
		update(vi_seg, vi_lazy, left_mode, L, mid, V);
		update(vi_seg, vi_lazy, right_mode, mid + 1, R, V);
	}
	pushup(vi_seg, index);
}

void build(vector<int>& vi_seg, vector<int>& vi_lazy, int index, int left, int right) {
	if (left == right) {
		vi_seg[index] = 1;
		vi_lazy[index] = 1;
		return;
	}
	vi_seg[index] = vi_lazy[index] = 0;
	int mid = (left + right) / 2;
	build(vi_seg, vi_lazy, left_mode);
	build(vi_seg, vi_lazy, right_mode);
	pushup(vi_seg, index);
}

int main() {
	IOS;
	int t;
	while (cin >> t && t) {
		for (int i = 1; i <= t; i++) {
			int n, q;
			cin >> n >> q;
			vector<int> vi_seg(n * 4, 0); // 这个开到n*3会WA，竟然不是RE，好奇怪？？？可能这个越界的不多，同时越界的地方的数值也合理，所以没报RE，而是报WA了。
			vector<int> vi_lazy(n * 4, 0); // 这个开到n*3会WA，竟然不是RE，好奇怪？？？可能这个越界的不多，同时越界的地方的数值也合理，所以没报RE，而是报WA了。
			build(vi_seg, vi_lazy, 1, 1, n);
			while(q--) {
				int ix, iy, iz;
				// cin >> ix >> iy >> iz; // 尽管关闭了cin的同步，也还是慢，会超时。
				scanf("%d %d %d", &ix, &iy, &iz);
				update(vi_seg, vi_lazy, 1, 1, n, ix, iy, iz);
			}
			// cout << "Case " << i << ": The total value of the hook is " << vi_seg[1] << "." << endl;
			printf("Case %d: The total value of the hook is %d.\n", i, vi_seg[1]);
		}
	}
	return 0;
}