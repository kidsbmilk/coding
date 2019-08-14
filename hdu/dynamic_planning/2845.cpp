/*
// ��ʱ��
// ���ʵ�ֵĸ��Ӷ�̫���ˣ��������ǣ�û�н�ϴ����������ö��档
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstdio>
using namespace std;

int main() {
	int m, n;
	while (cin >> m >> n && m && n) {
		vector<vector<int> > vvi(m, vector<int>(n, 0));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				// cin >> vvi[i][j];
				scanf("%d", &vvi[i][j]);
			}
		}
		vector<vector<int> > vvi_b(vvi);
		int imax = 0;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				for (int p = max(0, i - 3); p <= i; p++) { // �п���ͬһ��
					if (abs(p - i) == 1) continue;
					for (int q = 0; q < n; q++) { // ������ͬһ��
						if (p == i && q >= j) break;
						if (p == i && abs(q - j) == 1) continue;
						if (vvi_b[i][j] < vvi_b[p][q] + vvi[i][j]) {
							vvi_b[i][j] = vvi_b[p][q] + vvi[i][j];
							if (vvi_b[i][j] > imax) {
								imax = vvi_b[i][j];
							}
						}
					}
				}
			}
		}
		cout << imax << endl;
	}
	return 0;
}
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdio>
using namespace std;

int main() {
	int m, n;
	while (cin >> m >> n && m && n) {
		vector<int> vi(m + 2, 0);
		for (int i = 2; i < m + 2; i++) {
			vector<int> vitp(n + 2, 0);
			for (int j = 2; j < n + 2; j++) {
				// cin >> vitp[j]; // �ᳬʱ
				scanf("%d", &vitp[j]); // 280ms
			}
			vector<int> vitp_b(n + 2, 0);
			int imaxtp = 0;
			for (int j = 2; j < n + 2; j++) {
				vitp_b[j] = max(vitp_b[j - 2] + vitp[j], vitp_b[j - 1]); // ��һ�ζ�����ÿһ�е����ֵ
				if (vitp_b[j] > imaxtp) {
					imaxtp = vitp_b[j];
				}
			}
			vi[i] = imaxtp;
		}
		vector<int> vi2(m + 2, 0);
		int imax = 0;
		for (int i = 2; i < m + 2; i++) {
			vi2[i] = max(vi2[i - 2] + vi[i], vi2[i - 1]);
			if (vi2[i] > imax) {
				imax = vi2[i];
			}
		}
		cout << imax << endl;
	}
	return 0;
}

/*
// ���˵ĳ�����Ĵ��룬���ǣ���ϣ���Լ�д��ô�漼���ɵĴ��롣
#include <cstdio>
#include <algorithm>
using namespace std;
int const N = 200010;
int m, n, c[N], l, dp[N], i, j;
int main() {
  while(~scanf("%d%d", &m, &n)) {
	for(j=1; j<=m; c[j++]=dp[n])
	  for(i=2, scanf("%d", &dp[1]); i<=n && scanf("%d", &l); i++)
		dp[i] = max(dp[i-2]+l, dp[i-1]);
	for(i=2, dp[1]=c[1]; i<=m; i++)
	  dp[i] = max(dp[i-2]+c[i], dp[i-1]);
	printf("%d\n", dp[m]);
  }
  return 0;
}
*/