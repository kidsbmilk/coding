#include<iostream>
#include<vector>
using namespace std;

int main() {
	int n;
	while (cin >> n && n >= 0) {
		vector<int> vi;
		int isum = 0;
		for (int i = 0; i < n; i++) {
			int v, m;
			cin >> v >> m;
			while (m--) {
				vi.push_back(v);
				isum += v;
			}
		}
		int iv = isum / 2; // 背包容量
		vector<int> vi_b(iv + 1, -1);
		vi_b[0] = 0;
		int imax = 0;
		for (int i = 0; i < vi.size(); i++) { // 注意：是vi.size()，别相当然在写成n，之前就因为这点WA。
			for (int j = iv; j >= vi[i]; j--) {
				if (vi_b[j - vi[i]] == 0) {
					vi_b[j] = 0;
					if (j > imax) {
						imax = j;
					}
				}
			}
		}
		if (imax < isum - imax) {
			imax = isum - imax;
		}
		cout << imax << " " << isum - imax << endl;
	}
	return 0;
}

/*
// 下面是别人做的，背包的思想，cost和value一样。
#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;
int V[5001] = { 0 };//最多N种（50），每种数量最多M（100） = 5000
int f[125025] = { 0 }; // >50*5001/2
int main()
{
	int _N = 0;
	int m = 0, n = 0;
	int sum = 0;
	int v_count = 0;
	while (scanf_s("%d", &_N) != EOF && _N > 0)
	{
		//每组数据处理前清零
		sum = v_count = 0;
		memset(V, 0, sizeof(V));
		memset(f, 0, sizeof(f));

		for (int i = 0; i < _N; i++)
		{
			scanf_s("%d%d", &m, &n);
			for (int i = 0; i < n; i++)
			{
				V[v_count++] = m;
				sum += m;
			}
		}
		for (int i = 0; i < v_count; i++)
		{
			for (int j = sum / 2; j >= V[i]; j--)
			{
				f[j] = max(f[j], f[j - V[i]] + V[i]); // cost和value相同
			}

		}
		printf("%d %d\n", sum - f[sum / 2], f[sum / 2]);
	}
	return 0;
}
*/