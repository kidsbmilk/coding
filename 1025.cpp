/*
#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

// ��̬�滮������ı���ǣ���ĳ������ʱ����������г��ȡ�
// ����Ҷ��ˣ�������֮ǰ������һ������һ�����ǲ��Եģ�Ҫʹ��������ֳ���ϵ�Ч����Ҫʹ������forѭ������Ҫ�����뱣�浽�����С�
// https://blog.csdn.net/dzyhenry/article/details/8851162 ����д��˼·�ر�ã���֮ǰû���ǵ���ת��˼ά��
// ���Ƚ�һ�ߵģ�poorcities�����а���С�����˳�����У�����˳��Ȼ������һ�ߵĳ��У�rich cities����ŵ���������С���
// �����̬�滮�ı�˻ᳬʱ��������ı��˵Ľⷨ��
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
		// ѹ��vi
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
// ��������Ƕ�̬�滮��������ֻ������ѡ�ı�˱Ƚ����أ�ѡ���ǵ�ĳ������ʱ��С�ĺ��Ƕ��٣���������������±�����ʾ�ˡ������ܱ�ʾ��ϵ������������ͬ����Ͻ����������С�ĺš�
// ����ֻ������ѡ������Ϊ��ˣ�����Ϊ�������������������У�����������ó�������Ϊ��ˣ�ͬʱ���������ֿ�������С�ĺ���������ĵ��ơ�
// �����ҵ�д���У����Ժ���Ϊ�±������ơ�ʵ�ֶ�̬�滮�㷨�ˣ����ǵ���ĳ��Ϊֹʱ�����ĳ����Ƕ��٣����ںŷǳ��ࡢ�󣬵��³�ʱ�ˡ�
// ����������lower_boundʵ�ֵģ��ǳ���࣬������Ĵ���˼����һ���ģ�
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
			if (a[i].e > s[w]) { // ������ڵ�ǰ���ģ����±����Ӻ�д�����ĺţ��൱�ڽ��±���Ϊ���������ˡ�s�е�Ԫ�ر�ʾ���ǣ���ĳ������ʱ��С�ĺ��Ƕ��١�
				w++;
				s[w] = a[i].e;
			}
			else { // ��������þ��Ǹ��µ�ĳ����ʱ��˭������С�ĺŲ��s�С�Ҳʹ�����ⲿ�ִ���������Ĵ����н����ˡ�
				for (j = w; j >= 0; j--) { // ע�⣺��Ϊs���Ǵ�С����ģ����Կ����ö�����������Ϊ����������Ҳ�ͳ��˶���+�����ˣ�����ֱ����C++���lower_bound��
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

// ͬ���Ķ������еı����ͷǳ����׶�����������̫��Ҫ�ˣ�
// https://blog.csdn.net/dzyhenry/article/details/8851162 ����˵�ǳ����׶������ö�ջ������ġ�
// https://blog.csdn.net/zzc3615/article/details/7320639 ����˵���Ѷ���
// https://blog.csdn.net/cowboy90/article/details/73138680 ����˵���Ѷ���
// https://blog.csdn.net/sunny606/article/details/7887878 ����˵���Ѷ���

/*
// ���Ѷ���ʵ��
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
			scanf("%d %d", &a, &b); // ע�⣺�������Ƚϴ󣬲���ʹ��cin��Ҫʹ��scanf��
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
						break; // ע�������
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
		cout << endl; // ע�⣺��һ�п��У�
	}
	return 0;
}
*/

/*
// ���Ѷ���ʵ�֣�����lower_bound��ʵ�ֶ��֡�
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
			scanf("%d %d", &a, &b); // ע�⣺�������Ƚϴ󣬲���ʹ��cin��Ҫʹ��scanf��
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
		cout << endl; // ע�⣺��һ�п��У�
	}
	return 0;
}
*/

/*
// ���Ѷ���ʵ�֣��Լ�ʵ�ֵݹ���֡�
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MaxEle = 500005;

int bs_recursion(vector<int> &vi, int istart, int iend, int value) { // ��Χ��[istart, iend]�����Ҷ���������lower_bound��һ����lower_bound������ҿ��ġ�
	if (vi.size() == 0 || istart > iend) {
		return -1;
	}
	int mid = (istart + iend) / 2; // ע�⣺���ܼ�1
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
			scanf("%d %d", &a, &b); // ע�⣺�������Ƚϴ󣬲���ʹ��cin��Ҫʹ��scanf��
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
		cout << endl; // ע�⣺��һ�п��У�
	}
	return 0;
}
*/

// ���Ѷ���ʵ�֣��Լ�ʵ�ַǵݹ���֡�
#include<iostream>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;

const int MaxEle = 500005;

int bs(vector<int>& vi, int istart, int iend, int value) { // ��Χ��[istart, iend]�����Ҷ���������lower_bound��һ����lower_bound������ҿ��ġ�
	if (vi.size() == 0 || istart > iend) {
		return -1;
	}
	while (istart <= iend) {
		int mid = (istart + iend) / 2; // ע�⣺���ܼ�1
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
			scanf("%d %d", &a, &b); // ע�⣺�������Ƚϴ󣬲���ʹ��cin��Ҫʹ��scanf��
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
		cout << endl; // ע�⣺��һ�п��У�
	}
	return 0;
}