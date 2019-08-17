// �⿴�Źֳ�����ʵҪ�����º��������ף�����¼��������������⸴�ӻ��ˡ�
// https://blog.csdn.net/u011466175/article/details/38294513  ����Ĵ�������ˣ���ɢ���������ԣ����ߵĸĽ���ɢ����Ҳ�������ܵģ�����ȷ����ɢ�����ǣ���������1�������һ������

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
	if (vi_seg[index] != -1 || left == right) { // ������Ǹ��Ż���query�ڼ䲻��Ҫ��ִ��pushdown���ܿ�30ms���ҡ�
		if (vi_seg[index] != -1 && mib.count(vi_seg[index]) == 0) {
			mib[vi_seg[index]] = true;
		}
		return; // ע�����������
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
			sort(vi_all.begin(), vi_all.end()); // ����û���ٿ������飬�����ڲ���������������������ˣ��ƺ����ܵ�һЩ��
			vector<int> vi_seg(vi_all.size() * 4, -1);
			for (int i = 1; i <= n; i++) {
				int ilefttp = lower_bound(vi_all.begin(), vi_all.end(), vi_start[i]) - vi_all.begin();
				int irighttp = lower_bound(vi_all.begin(), vi_all.end(), vi_end[i]) - vi_all.begin();
				update(vi_seg, 1, 1, vi_all.size() - 1, ilefttp, irighttp, i); // vi_all.size() - 1����Ϊȥ����ǰ���0
			}
			map<int, bool> mib;
			query(vi_seg, mib, 1, 1, vi_all.size() - 1); // vi_all.size() - 1����Ϊȥ����ǰ���0
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
bool hash_arr[M << 4]; // ���hash_arr��hasharr�����ˣ�����hash, hash_arrr��hashme���Թ���Ϊʲô������ ɶ�������ˣ���RE��Ҳ��WA������Ϊ���˸�������������
// ԭ��������2�����󣬻���һ�����Ͻ�������1��hash_arr[M]̫С�ˣ�ӦΪhash_arr[M << 4]������2��!hash_arr[col[rt]]ӦΪ��col[rt] != -1 && !hash_arr[col[rt]]�����Ͻ�֮����ȫ��m�������ط�Ҳ�����¶���m�ˡ�

void PushDown(int rt) {
	col[rt << 1] = col[rt << 1 | 1] = col[rt];
	col[rt] = -1;
}
// �������ʵ�ֿ��Կ������߶����ڵ���洢����Ⱦɫֵ������ĳ�������ж��ٿɼ���Ⱦɫֵ����ͳ���ܵĿɼ�����ʱ��Ҫ�������нڵ㣬�ж�Ⱦɫֵ�Ƿ�Ϊ-1��ͬʱҪ�ж��Ƿ��Ѿ�ͳ�ƹ���Ⱦɫֵ�ˡ�
// �Ż����ܲ���ֱ�����߶����ڵ���洢ĳ�����ж��ٿɼ���Ⱦɫֵ���������ѣ���Ҫ�洢����������Ⱦɫ���ϣ���ȥ�أ��Ƚϸ���һ�㡣
void Update(int L, int R, int c, int l, int r, int rt) {
	if (l >= L && r <= R) { // ������ܸ�Ϊ��l == L && r == R������ᱨRE��
		col[rt] = c; // �������Ⱦɫ��������ĳ����Ⱦ��һ�����֣���ʾĳ������
		return;
	}

	if (col[rt] != -1) PushDown(rt);
	int m = (l + r) >> 1;
	if (m >= L) Update(L, R, c, l, m, rt << 1);
	if (m < R)  Update(L, R, c, m + 1, r, rt << 1 | 1);
}

void query(int l, int r, int rt) {
	if (l == r) {
		if (col[rt] != -1 && !hash_arr[col[rt]]) { // �����ж�Ⱦ�ϵ������Ƿ��ѱ�ͳ�ƹ�������1-10,2-5���Σ�1-10��2-5�����ˣ�����1-10��2-5����������ֻ�ᱻͳ��һ�Ρ�
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

	while (ll <= hh) { // ע�⣺<=��ʾ�����������±�hh����
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
		for (i = 2; i <= nn; i++) { // ���������unique
			if (x[i] != x[i - 1]) x[++m] = x[i];
		}
		for (i = m; i > 1; i--) {
			if (x[i] - x[i - 1] > 1) x[++m] = x[i] - 1;
		}
		sort(x + 1, x + m + 1);
		for (i = 1; i <= n; i++) {
			int l = BSearch(1, m, li[i]); // ���������lower_bound
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