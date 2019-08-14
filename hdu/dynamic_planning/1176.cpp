#include<iostream>
#include<vector>
#include<cmath>
#include<cstdio>
using namespace std;

int main() {
	int n;
	while (cin >> n && n) {
		vector<vector<int> > vvi;
		vector<int> vitp(11, 0);
		vitp[5] = 0;
		vvi.push_back(vitp);
		for (int i = 0; i < n; i++) {
			int x, t;
			// cin >> x >> t;
			scanf("%d %d", &x, &t);
			while (vvi.size() - 1 < t) {
				vvi.push_back(vector<int>(11, 0));
			}
			vvi[t][x] += 1;
		}
		vector<vector<int> > vvi_b(vvi.size() + 1, vector<int>(11, 0));
		int imax = 0;
		int istart = 5, iend = 5;
		for (int i = 0; i < vvi.size() - 1; i++) { // 所有层
			int istp = istart, ietp = iend;
			for (int j = istart; j <= iend; j++) { // 当前层每一个元素
				if (j < 0 || j >= 11) continue;
				if (j - 1 < istp) istp = j - 1;
				if (j + 1 > ietp) ietp = j + 1;
				for (int k = j - 1; k <= j + 1; k++) { // 下一层可能的元素
					if (k < 0 || k >= 11) continue;
					if (vvi_b[i + 1][k] < vvi_b[i][j] + vvi[i + 1][k]) {
						vvi_b[i + 1][k] = vvi_b[i][j] + vvi[i + 1][k];
						if (vvi_b[i + 1][k] > imax) {
							imax = vvi_b[i + 1][k];
						}
					}
				}
			}
			istart = istp;
			iend = ietp;
		}
		cout << imax << endl;
	}
	return 0;
}