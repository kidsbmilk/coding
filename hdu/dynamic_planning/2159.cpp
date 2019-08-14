/*
10 10 1 10
1 1
0
10 10 1 9
1 1
-1
9 10 2 10
1 1
2 2
1
8 6 2 2
5 2
4 3
2
99 21 10 8
11 11
4 3
10 14
8 11
10 19
12 1
18 11
6 17
19 3
6 4
11
10 10 1 10
20 1
9
*/

/*
// ����Ĳ�������ȫ�����ܹ���������Ȼ����ac��
// ����ԭ�򣺼���for (int i = 0; i < vpii.size(); i++) {���е�ע�͡�
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, m, k, s;
	while (cin >> n >> m >> k >> s && n && m && k && s) {
		vector<pair<int, int> > vpii;
		int imaxtp = n;
		for (int i = 0; i < k; i++) {
			int itp, itp2;
			cin >> itp >> itp2;
			int imintp = min(s, m / itp2);
			if (n % itp) imintp = min(imintp, n / itp + 1);
			else imintp = min(imintp, n / itp);
			for (int j = 0; j < imintp; j++) {
				vpii.push_back(make_pair(itp, itp2));
			}
			if (imintp * itp > imaxtp) {
				imaxtp = imintp * itp;
			}
		}
		vector<int> vi_b(imaxtp + 1, -1); // �õ�ĳ����ֵʱ��������������Ͷ�
		vi_b[0] = m;
		int imax = -1;
		for (int i = 0; i < vpii.size(); i++) { // �������ԶԶ������ɱ�������ˡ���Ȼ�������ʱ��������ﲻ����s������vpii�������Զ��s�ˡ�Ҳ����˵����ĳЩ����£�������<=s������������Թ����ˡ�
			for (int j = imaxtp; j >= vpii[i].first; j--) {
				if (vi_b[j] < vi_b[j - vpii[i].first] - vpii[i].second) {
					vi_b[j] = vi_b[j - vpii[i].first] - vpii[i].second;
					if (j >= n && imax < vi_b[j]) {
						imax = vi_b[j];
					}
				}
			}
		}
		cout << imax << endl;
	}
	return 0;
}
*/

// 15ms
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, m, k, s;
	while (cin >> n >> m >> k >> s && n && m && k && s) {
		vector<pair<int, int> > vpii;
		int imaxtp = n;
		for (int i = 0; i < k; i++) {
			int itp, itp2;
			cin >> itp >> itp2;
			int imintp = min(s, m / itp2);
			if (n % itp) imintp = min(imintp, n / itp + 1);
			else imintp = min(imintp, n / itp);
			for (int j = 0; j < imintp; j++) {
				vpii.push_back(make_pair(itp, itp2));
			}
			if (imintp * itp > imaxtp) {
				imaxtp = imintp * itp;
			}
		}
		vector<int> vi_b(imaxtp + 1, -1); // �õ�ĳ����ֵʱ��������������Ͷ�
		vector<int> vi_b2(imaxtp + 1, 0); // �õ�ĳ����ֵʱ��ɱ�Ĺ�����
		vi_b[0] = m;
		vi_b2[0] = 0;
		int imax = -1;
		for (int i = 0; i < vpii.size(); i++) { // �������ԶԶ������ɱ�������ˡ���Ȼ�������ʱ��������ﲻ����s������vpii�������Զ��s�ˡ�Ҳ����˵����ĳЩ����£�������<=s������������Թ����ˡ�
			for (int j = imaxtp; j >= vpii[i].first; j--) {
				if (vi_b[j] < vi_b[j - vpii[i].first] - vpii[i].second) {
					vi_b[j] = vi_b[j - vpii[i].first] - vpii[i].second;
					vi_b2[j] = vi_b2[j - vpii[i].first] + 1;
					if (j >= n && imax < vi_b[j] && vi_b2[j] <= s) {
						imax = vi_b[j];
					}
				}
			}
		}
		cout << imax << endl;
	}
	return 0;
}

/*
// ��ά���� 109ms
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, m, k, s;
	while (cin >> n >> m >> k >> s && n && m && k && s) {
		vector<vector<int> > vvi_b(201, vector<int>(s + 1, -1));
		vvi_b[0][0] = m;
		for (int i = 0; i < k; i++) {
			int itp, itp2;
			cin >> itp >> itp2;
			for (int j = itp; j < vvi_b.size(); j++) {
				for (int k = 1; k <= s; k++) {
					vvi_b[j][k] = max(vvi_b[j][k], vvi_b[j - itp][k - 1] - itp2);
				}
			}
		}
		int imax = -1;
		for (int i = n; i < vvi_b.size(); i++) {
			for (int j = 1; j <= s; j++) {
				imax = max(imax, vvi_b[i][j]);
			}
		}
		cout << imax << endl;
	}
	return 0;
}
*/

/*
// ��ά���������˵Ĵ���
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <map>
#include <set>
#define inf 0x3f3f3f3f
#define ll long long
#define sscc ios::sync_with_stdio(false);
#define ms(a) memset(a,0,sizeof(a))
#define mss(a) memset(a,-1,sizeof(a))
#define msi(a) memset(a,-inf,sizeof(a))
using namespace std;

int dp[1002][2001];

int main()
{
	sscc;
	int n, m, k, s;
	while (cin >> n >> m >> k >> s)//n����ֵ��m���Ͷȣ�k��������s����ɱ���� 
	{
		msi(dp);
		dp[0][0] = m;
		for (int i = 0; i < k; i++)
		{
			int x, y;
			cin >> x >> y;
			for (int j = x; j <= 200; j++)//����ֵ����dp��n����Ϊ�����ܴ���dp��ʱ��j��ֵ�����n����������ֵ��Ҫ���ٵ���� 
				for (int q = 1; q <= s; q++)//��������� 
					dp[j][q] = max(dp[j][q], dp[j - x][q - 1] - y);//dp[j][q]����Ǿ���ֵΪj��ɱ��q���֣�ʣ������ֵ 
		}
		int ans = -inf;
		for (int j = n; j <= 200; j++)//���� n~200������ֵʣ������ 
			for (int i = 1; i <= s; i++)
				ans = max(ans, dp[j][i]);
		if (ans < 0)
			cout << -1 << endl;
		else
			cout << ans << endl;
	}
	return 0;
}*/