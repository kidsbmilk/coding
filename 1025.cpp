/*
#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

// 动态规划，这里的标杆是：到某个数字时最长的升序序列长度。
// 标杆找对了，但是我之前是输入一个处理一个，是不对的，要使标杆能体现出组合的效果，要使用两层for循环，就要把输入保存到数组中。
// https://blog.csdn.net/dzyhenry/article/details/8851162 这里写的思路特别好，我之前没考虑到，转化思维：
// “先将一边的（poorcities）城市按从小到大的顺序排列，按次顺序，然后求另一边的城市（rich cities）编号的最长递增序列。”
// 这个动态规划的标杆会超时，见下面的别人的解法。
int main() {
	int n;
	int cs = 1;
	while (scanf("%d", &n) == 1 && n) {
		vector<int> vi(500000 + 10, 0);
		for (int i = 0; i < n; i++) {
			int p, q;
			scanf("%d %d", &p, &q);
			vi[p] = q;
		}
		// 压缩vi
		int itp = 1;
		for (int i = 1; i < vi.size(); i++) {
			if (vi[i]) {
				vi[itp++] = vi[i];
			}
		}
		vi.resize(itp);
		vector<int> vi_b(vi.size(), 0);
		int iMax = 0;
		for (int i = 1; i < vi_b.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (vi[j] < vi[i]) {
					vi_b[i] = max(vi_b[i], vi_b[j] + 1);
				}
			}
			if (iMax < vi_b[i]) {
				iMax = vi_b[i];
			}
		}
		cout << "Case " << cs++ << ":" << endl;
		if (iMax > 1) {
			cout << "My king, at most " << iMax << " roads can be build." << endl;
		}
		else {
			cout << "My king, at most 1 road can be build." << endl;
		}
	}
	return 0;
}
*/

/*
// 下面这个是动态规划的做法，只不过是选的标杆比较奇特，选的是到某个长度时最小的号是多少，这个长度用数组下标来表示了。而且能表示组合的情况，并依不同的组合结果来更新最小的号。
// 这里只所以能选长度做为标杆，是因为此题就是求最长升序子序列，“最长”可以用长度来做为标杆，同时，“升序”又可以以最小的号来做后面的递推。
// 上面我的写法中，是以号做为下标来递推、实现动态规划算法了，就是当以某号为止时的最大的长度是多少，由于号非常多、大，导致超时了。
// 网上有人用lower_bound实现的，非常简洁，跟下面的代码思想是一样的：
// for(i = 1;i <= n;i++)
// 	*lower_bound(dp,dp + n,temp[i]) = temp[i];
// int count = lower_bound(dp,dp + n,INF) - dp;
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

struct road {
	int s;
	int e;
} a[500005] = {};
int s[500005] = {};

bool cmp(road a, road b) {
	return a.s < b.s || a.s == b.s && a.e < b.e;
}

int main() {
	int n, t = 0;
	while (cin >> n && n) {
		t++;
		memset(a, 0, sizeof(a));
		memset(s, 0, sizeof(s));
		int i, w = 0, j;
		s[0] = 0;
		for (i = 0; i < n; i++)
			scanf("%d%d", &a[i].s, &a[i].e);
		sort(a, a + n, cmp);
		for (i = 0; i < n; i++) {
			if (a[i].s == a[i - 1].s) continue;
			if (a[i].e > s[w]) { // 如果大于当前最大的，就下标增加后写入最大的号，相当于将下标作为长度来用了。s中的元素表示的是：到某个长度时最小的号是多少。
				w++;
				s[w] = a[i].e;
			}
			else { // 这里的作用就是更新到某长度时，谁才是最小的号并填到s中。也使下面这部分代码与上面的代码有交流了。
				for (j = w; j >= 0; j--) { // 注意：因为s里是从小到大的，所以可以用二分搜索，改为二分搜索后，也就成了动规+二分了，可以直接用C++里的lower_bound。
					if (s[j] < a[i].e) {
						s[j + 1] = a[i].e;
						break;
					}
				}
			}
		}
		if (w == 1) printf("Case %d:\nMy king, at most 1 road can be built.\n\n", t);
		else printf("Case %d:\nMy king, at most %d roads can be built.\n\n", t, w);
	}
	return 0;
}
*/

// 同样的东西，有的表述就非常容易懂！文字能力太重要了！
// https://blog.csdn.net/dzyhenry/article/details/8851162 这里说非常容易懂，利用堆栈来比拟的。
// https://blog.csdn.net/zzc3615/article/details/7320639 这里说的难懂。
// https://blog.csdn.net/cowboy90/article/details/73138680 这里说的难懂。
// https://blog.csdn.net/sunny606/article/details/7887878 这里说的难懂。

/*
// 自已动手实现
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

const int MaxEle = 500005;

int main() {
	int n;
	int cs = 1;
	while (cin >> n && n) {
		vector<int> vi(MaxEle, 0);
		while (n--) {
			int a, b;
			scanf("%d %d", &a, &b); // 注意：数据量比较大，不能使用cin，要使用scanf！
			vi[a] = b;
		}
		int itp = 0;
		for (int i = 0; i < MaxEle; i++) {
			if (vi[i]) {
				vi[itp++] = vi[i];
			}
		}
		vi.resize(itp);
		vector<int> vi_b(vi.size() + 1, 0);
		int len = 0;
		for (int i = 0; i < vi.size(); i++) {
			if (vi[i] > vi_b[len]) {
				vi_b[++len] = vi[i];
			}
			else {
				for (int j = len; j >= 0; j--) {
					if (vi_b[j] < vi[i]) {
						vi_b[j + 1] = vi[i];
						break; // 注意这个！
					}
				}
			}
		}
		cout << "Case " << cs ++ << ":" << endl;
		if (len > 1) {
			cout << "My king, at most " << len << " roads can be built." << endl;
		}
		else {
			cout << "My king, at most 1 road can be built." << endl;
		}
		cout << endl; // 注意：多一行空行！
	}
	return 0;
}
*/

/*
// 自已动手实现，利用lower_bound来实现二分。
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MaxEle = 500005;

int main() {
	int n;
	int cs = 1;
	while (cin >> n && n) {
		vector<int> vi(MaxEle, 0);
		while (n--) {
			int a, b;
			scanf("%d %d", &a, &b); // 注意：数据量比较大，不能使用cin，要使用scanf！
			vi[a] = b;
		}
		int itp = 0;
		for (int i = 0; i < MaxEle; i++) {
			if (vi[i]) {
				vi[itp++] = vi[i];
			}
		}
		vi.resize(itp);
		vector<int> vi_b;
		for (int i = 0; i < vi.size(); i++) {
			int indTp = lower_bound(vi_b.begin(), vi_b.end(), vi[i]) - vi_b.begin();
			if (indTp >= vi_b.size()) {
				vi_b.push_back(vi[i]);
			}
			else {
				vi_b[indTp] = vi[i];
			}
		}
		cout << "Case " << cs++ << ":" << endl;
		if (vi_b.size() > 1) {
			cout << "My king, at most " << vi_b.size() << " roads can be built." << endl;
		}
		else {
			cout << "My king, at most 1 road can be built." << endl;
		}
		cout << endl; // 注意：多一行空行！
	}
	return 0;
}
*/

/*
// 自已动手实现，自己实现递归二分。
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MaxEle = 500005;

int bs_recursion(vector<int> &vi, int istart, int iend, int value) { // 范围：[istart, iend]，左右都包含，跟lower_bound不一样，lower_bound是左闭右开的。
	if (vi.size() == 0 || istart > iend) {
		return -1;
	}
	int mid = (istart + iend) / 2; // 注意：不能加1
	if ((vi[mid] == value) || 
		(mid - 1 >= 0 && vi[mid -1] < value && vi[mid] > value) || 
		(mid == 0 && vi[mid] > value)) {
		return mid;
	}
	else if (vi[mid] < value) {
		return bs_recursion(vi, mid + 1, iend, value);
	}
	else {
		return bs_recursion(vi, istart, mid - 1, value);
	}
}

int main() {
	int n;
	int cs = 1;
	while (cin >> n && n) {
		vector<int> vi(MaxEle, 0);
		while (n--) {
			int a, b;
			scanf("%d %d", &a, &b); // 注意：数据量比较大，不能使用cin，要使用scanf！
			vi[a] = b;
		}
		int itp = 0;
		for (int i = 0; i < MaxEle; i++) {
			if (vi[i]) {
				vi[itp++] = vi[i];
			}
		}
		vi.resize(itp);
		vector<int> vi_b;
		for (int i = 0; i < vi.size(); i++) {
			int indTp = bs_recursion(vi_b, 0, vi_b.size() - 1, vi[i]);
			if (indTp == -1) {
				vi_b.push_back(vi[i]);
			}
			else {
				vi_b[indTp] = vi[i];
			}
		}
		cout << "Case " << cs++ << ":" << endl;
		if (vi_b.size() > 1) {
			cout << "My king, at most " << vi_b.size() << " roads can be built." << endl;
		}
		else {
			cout << "My king, at most 1 road can be built." << endl;
		}
		cout << endl; // 注意：多一行空行！
	}
	return 0;
}
*/

// 自已动手实现，自己实现非递归二分。
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MaxEle = 500005;

int bs(vector<int>& vi, int istart, int iend, int value) { // 范围：[istart, iend]，左右都包含，跟lower_bound不一样，lower_bound是左闭右开的。
	if (vi.size() == 0 || istart > iend) {
		return -1;
	}
	while (istart <= iend) {
		int mid = (istart + iend) / 2; // 注意：不能加1
		if ((vi[mid] == value) ||
			(mid - 1 >= 0 && vi[mid - 1] < value && vi[mid] > value) ||
			(mid == 0 && vi[mid] > value)) {
			return mid;
		}
		else if (vi[mid] < value) {
			istart = mid + 1;
		}
		else {
			iend = mid - 1;
		}
	}
	return -1;
}

int main() {
	int n;
	int cs = 1;
	while (cin >> n && n) {
		vector<int> vi(MaxEle, 0);
		while (n--) {
			int a, b;
			scanf("%d %d", &a, &b); // 注意：数据量比较大，不能使用cin，要使用scanf！
			vi[a] = b;
		}
		int itp = 0;
		for (int i = 0; i < MaxEle; i++) {
			if (vi[i]) {
				vi[itp++] = vi[i];
			}
		}
		vi.resize(itp);
		vector<int> vi_b;
		for (int i = 0; i < vi.size(); i++) {
			int indTp = bs(vi_b, 0, vi_b.size() - 1, vi[i]);
			if (indTp == -1) {
				vi_b.push_back(vi[i]);
			}
			else {
				vi_b[indTp] = vi[i];
			}
		}
		cout << "Case " << cs++ << ":" << endl;
		if (vi_b.size() > 1) {
			cout << "My king, at most " << vi_b.size() << " roads can be built." << endl;
		}
		else {
			cout << "My king, at most 1 road can be built." << endl;
		}
		cout << endl; // 注意：多一行空行！
	}
	return 0;
}