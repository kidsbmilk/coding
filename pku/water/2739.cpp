// 这题因为是求连续素数和，只能累加，累加这里可以试试线段树加速。累加给人的错觉是：太慢了，可能会超时，但是，10000以内的素数并没有多少，放心累加吧。
// 即使是用线段树，也要循环两个边界，只是加速了区间的相加而已。目前这个写法已经非常快了。

#include<iostream>
#include<vector>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin_tie(0)

int main() {
	vector<int> vi;
	vi.push_back(2);
	for (int i = 3; i <= 10000; i++) {
		int itp = sqrt(float(i)) + 1;
		bool isprim = true;
		for (int j = 2; j < itp; j++) {
			if (i % j == 0) {
				isprim = false;
				break;
			}
		}
		if (isprim) {
			vi.push_back(i);
		}
	}
	map<int, int> mii;
	int n;
	while (cin >> n && n) {
		mii[n] = 0;
		for (int i = 0; i < vi.size(); i++) {
			int isumtp = vi[i];
			for (int j = i + 1; j < vi.size(); j++) {
				if (isumtp < n) {
					isumtp += vi[j];
				}
				else if (isumtp > n) {
					break;
				}
				else {
					mii[n] += 1;
					break;
				}
			}
		}
		cout << mii[n] << endl;
	}
	return 0;
}