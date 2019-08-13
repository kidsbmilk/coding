/*
// 这里对扫描边界做了很多优化，然而还是会超时。
// 超时原因见最下面一层解法。
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		vector<int> vi_coin(n, 0);
		vector<int> vi;
		for (int i = 0; i < n; i++) {
			cin >> vi_coin[i];
		}
		for (int i = 0; i < n; i++) {
			int itp;
			cin >> itp;
			while (itp--) {
				vi.push_back(vi_coin[i]);
			}
		}
		if (m < 0) { // 注意：题目没说最小多少，所以可能有负值。
			cout << 0 << endl;
			continue;
		}
		sort(vi.begin(), vi.end());
		vector<int> vi_b(m + 1, -1);
		vi_b[0] = 0;
		int istart = 0, iend = 1;
		for (int i = 0; i < vi.size(); i++) {
			istart = min(istart + vi[i], m);
			int ietp = iend;
			for (int j = istart; j >= iend; j--) {
				if (vi_b[j] == -1) {
					if (j - vi[i] < 0) {
						ietp = j;
						break;
					}
					if (vi_b[j - vi[i]] == 0) {
						vi_b[j] = 0;
					}
					else {
						ietp = j - vi[i];
					}
				}
			}
			if (vi_b[ietp] == 0) {
				ietp = istart + 1;
			}
			iend = ietp;
		}
		int ict = 0;
		for (int i = 1; i <= m; i++) {
			if (vi_b[i] == 0) {
				ict += 1;
			}
		}
		cout << ict << endl;
	}
	return 0;
}
*/

/*
// 依然超时
// 超时原因见最下面一层解法。
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		vector<int> vi_coin(n, 0);
		vector<int> vi_num(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> vi_coin[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> vi_num[i];
		}
		if (m < 0) { // 注意：题目没说最小多少，所以可能有负值。
			cout << 0 << endl;
			continue;
		}
		vector<int> vi_b(m + 1, -1);
		vi_b[0] = 0;
		int iend = 0;
		for (int i = 0; i < n; i++) {
			iend = min(iend, m);
			int ietp = iend;
			for (int j = 0; j <= iend; j++) {
				if (vi_b[j] == 0) {
					for (int k = 1; k <= vi_num[i]; k++) {
						if (j + k * vi_coin[i] > m) {
							break;
						}
						vi_b[j + k * vi_coin[i]] = 0;
					}
					if (j + vi_num[i] * vi_coin[i] > ietp) {
						ietp = j + vi_num[i] * vi_coin[i];
					}
				}
			}
			iend = ietp;
		}
		int ict = 0;
		for (int i = 1; i <= m; i++) {
			if (vi_b[i] == 0) {
				ict += 1;
			}
		}
		cout << ict << endl;
	}
	return 0;
}
*/

// 265ms
// 二进制优化，同时理解了完全背包与01背包的区别
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 01背包，元素有限，从高到低循环，即：在原来的基础上，加上当前的元素可以达到的效果
void bag01(vector<int>& vi, int icoin, int im) {
	for (int i = im; i >= icoin; i--) {
		if (vi[i] == -1 && vi[i - icoin] == 0) {
			vi[i] = 0;
		}
	}
}

// 完全背包，元素无限，从低到高循环，即：无限使用此元素可以达到的效果
void bagcomplete(vector<int>& vi, int icoin, int im) {
	for (int i = icoin; i <= im; i++) {
		if (vi[i] == -1 && vi[i - icoin] == 0) {
			vi[i] = 0;
		}
	}
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		vector<int> vi_coin(n, 0);
		vector<int> vi_num(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> vi_coin[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> vi_num[i];
		}
		if (m < 0) { // 注意：题目没说最小多少，所以可能有负值。
			cout << 0 << endl;
			continue;
		}
		vector<int> vi_b(m + 1, -1);
		vi_b[0] = 0;
		for (int i = 0; i < n; i++) {
			if (vi_num[i] * vi_coin[i] >= m) {
				bagcomplete(vi_b, vi_coin[i], m);
			}
			else {
				int k = 1;
				int inumtp = vi_num[i];
				while (k <= inumtp) {
					bag01(vi_b, k * vi_coin[i], m);
					inumtp -= k;
					k *= 2;
				}
				bag01(vi_b, inumtp * vi_coin[i], m);
			}
		}
		int ict = 0;
		for (int i = 1; i <= m; i++) {
			if (vi_b[i] == 0) {
				ict += 1;
			}
		}
		cout << ict << endl;
	}
	return 0;
}

/*
// 374ms
// 下面是别人的写法，没有超时，仔细看一下，这里只对未知元素判断一次，非常快，我的前两个超时，就是因为对已知元素多次递推了。
// 更深层次的：这个解法还有上面的二进制优化，都是减少元素个数，我的前两个，因为对多个相同元素重复计算了，所以超时了。
// 这里动规记录已使用的元素个数，非常巧妙。
// 这个解法里，用了两个动规，一个是f[i]，另一个是记录每个硬币种类使用个数的used[i]。
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n, m;
int a[105], c[105], used[100010];
bool f[100010];
int i, j;
int main() {
	while (scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0) break;
		for (i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (i = 1; i <= n; i++)
			scanf("%d", &c[i]);
		memset(f, 0, sizeof(f));
		f[0] = 1;
		int ans = 0;
		for (i = 1; i <= n; i++)
		{
			memset(used, 0, sizeof(used));
			for (j = a[i]; j <= m; j++)
				if (!f[j] && f[j - a[i]] && used[j - a[i]] < c[i]) // 这里动规记录已使用的元素个数，非常巧妙。
				{
					f[j] = 1;
					used[j] = used[j - a[i]] + 1;
					++ans;
				}
		}
		printf("%d\n", ans);
	}
	return 0;
}
*/