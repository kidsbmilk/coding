// 题看着怪长，其实要做的事很容易明白，题的事件描述反倒把问题复杂化了。
// https://blog.csdn.net/u011466175/article/details/38294513  这里的代码过不了，离散化方法不对，作者的改进离散方法也不是万能的，最正确的离散方法是：在相差大于1的数间加一个数。

#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushdown(vector<int>& vi_seg, int index) {
	if (vi_seg[index] != -1) {
		vi_seg[index * 2] = vi_seg[index * 2 + 1] = vi_seg[index];
		vi_seg[index] = -1;
	}
}

void update(vector<int>& vi_seg, int index, int left, int right, int L, int R, int v) {
	if (L <= left && right <= R) {
		vi_seg[index] = v;
		return;
	}
	if (vi_seg[index] != -1) {
		pushdown(vi_seg, index);
	}
	int mid = (left + right) / 2;
	if (R <= mid) {
		update(vi_seg, left_mode, L, R, v);
	} else if (L > mid) {
		update(vi_seg, right_mode, L, R, v);
	} else {
		update(vi_seg, left_mode, L, mid, v);
		update(vi_seg, right_mode, mid + 1, R, v);
	}
}

void query(vector<int>& vi_seg, map<int, bool>& mib, int index, int left, int right) {
	if (vi_seg[index] != -1 || left == right) { // 这个算是个优化，query期间不需要再执行pushdown，能快30ms左右。
		if (vi_seg[index] != -1 && mib.count(vi_seg[index]) == 0) {
			mib[vi_seg[index]] = true;
		}
		return; // 注意这个！！！
	}
	int mid = (left + right) / 2;
	query(vi_seg, mib, left_mode);
	query(vi_seg, mib, right_mode);
}

int main() {
	IOS;
	int c;
	while (cin >> c && c) {
		while (c--) {
			int n;
			cin >> n;
			vector<int> vi_start(n + 1);
			vector<int> vi_end(n + 1);
			vector<int> vi_all;
			vi_all.push_back(0);
			for (int i = 1; i <= n; i++) {
				cin >> vi_start[i] >> vi_end[i];
				vi_all.push_back(vi_start[i]);
				vi_all.push_back(vi_end[i]);
			}
			sort(vi_all.begin(), vi_all.end());
			int icttp = unique(vi_all.begin(), vi_all.end()) - vi_all.begin();
			vi_all.resize(icttp);
			for (int i = 2; i < icttp; i++) {
				if (vi_all[i] - vi_all[i - 1] > 1) {
					vi_all.push_back(vi_all[i] - 1);
				}
			}
			sort(vi_all.begin(), vi_all.end()); // 这里没有再开个数组，而是在部分有序的数据上再排序了，似乎性能低一些。
			vector<int> vi_seg(vi_all.size() * 4, -1);
			for (int i = 1; i <= n; i++) {
				int ilefttp = lower_bound(vi_all.begin(), vi_all.end(), vi_start[i]) - vi_all.begin();
				int irighttp = lower_bound(vi_all.begin(), vi_all.end(), vi_end[i]) - vi_all.begin();
				update(vi_seg, 1, 1, vi_all.size() - 1, ilefttp, irighttp, i); // vi_all.size() - 1是因为去掉最前面的0
			}
			map<int, bool> mib;
			query(vi_seg, mib, 1, 1, vi_all.size() - 1); // vi_all.size() - 1是因为去掉最前面的0
			cout << mib.size() << endl;
		}
	}
	return 0;
}


/*
// https://blog.csdn.net/non_cease/article/details/7383736
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define M 10005

int li[M], ri[M];
int x[M << 3], col[M << 4], ans;
bool hash_arr[M << 4]; // 这个hash_arr、hasharr过不了，但是hash, hash_arrr，hashme可以过，为什么？？？ 啥错误都有了，有RE，也有WA，就因为改了个变量名？？？
// 原因：作者有2处错误，还有一处不严谨。错误1：hash_arr[M]太小了，应为hash_arr[M << 4]；错误2：!hash_arr[col[rt]]应为：col[rt] != -1 && !hash_arr[col[rt]]。不严谨之处：全局m，其他地方也又重新定义m了。

void PushDown(int rt) {
	col[rt << 1] = col[rt << 1 | 1] = col[rt];
	col[rt] = -1;
}
// 从这里的实现可以看出：线段树节点里存储的是染色值，而非某区间内有多少可见的染色值，在统计总的可见区域时，要过滤所有节点，判断染色值是否为-1，同时要判断是否已经统计过此染色值了。
// 优化：能不能直接在线段树节点里存储某区间有多少可见的染色值？？？很难，需要存储左右子树的染色集合，再去重，比较复杂一点。
void Update(int L, int R, int c, int l, int r, int rt) {
	if (l >= L && r <= R) { // 这个不能改为：l == L && r == R，否则会报RE。
		col[rt] = c; // 这个就是染色操作，将某区间染上一个数字，表示某个海报
		return;
	}

	if (col[rt] != -1) PushDown(rt);
	int m = (l + r) >> 1;
	if (m >= L) Update(L, R, c, l, m, rt << 1);
	if (m < R)  Update(L, R, c, m + 1, r, rt << 1 | 1);
}

void query(int l, int r, int rt) {
	if (l == r) {
		if (col[rt] != -1 && !hash_arr[col[rt]]) { // 这里判断染上的数字是否已被统计过，比如1-10,2-5两段，1-10被2-5隔开了，但是1-10被2-5隔开的两段只会被统计一次。
			ans++;
			hash_arr[col[rt]] = true;
		}
		return;
	}
	if (col[rt] != -1) PushDown(rt);
	int m = (l + r) >> 1;
	query(l, m, rt << 1);
	query(m + 1, r, rt << 1 | 1);
}

int BSearch(int ll, int hh, int xx) {
	int mm;

	while (ll <= hh) { // 注意：<=表示可以搜索到下标hh处。
		mm = (ll + hh) >> 1;
		if (x[mm] == xx) return mm;
		else if (x[mm] > xx)  hh = mm - 1;
		else ll = mm + 1;
	}
	return -1;
}

int main()
{
	int t, n, i;
	scanf("%d", &t);
	while (t--) {
		memset(col, -1, sizeof(col));
		memset(hash_arr, false, sizeof(hash_arr));
		int nn = 0;
		scanf("%d", &n);
		for (i = 1; i <= n; i++) {
			scanf("%d %d", &li[i], &ri[i]);
			x[++nn] = li[i];
			x[++nn] = ri[i];
		}
		sort(x + 1, x + nn + 1);
		int m = 1;
		for (i = 2; i <= nn; i++) { // 这里可以用unique
			if (x[i] != x[i - 1]) x[++m] = x[i];
		}
		for (i = m; i > 1; i--) {
			if (x[i] - x[i - 1] > 1) x[++m] = x[i] - 1;
		}
		sort(x + 1, x + m + 1);
		for (i = 1; i <= n; i++) {
			int l = BSearch(1, m, li[i]); // 这里可以用lower_bound
			int r = BSearch(1, m, ri[i]);
			Update(l, r, i, 1, m, 1);
		}
		ans = 0;
		query(1, m, 1);
		printf("%d\n", ans);
	}
	return 0;
}
*/