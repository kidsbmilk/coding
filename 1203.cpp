#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

// �Ա�2955��

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break; // ע�⣺��Ŀ��˵�ˣ�n����m������Ϊ0��ֻ��n��m��Ϊ0ʱ�Ž�����
		vector<pair<int, float> > vpif;
		for (int i = 0; i < m; i++) {
			int itp;
			float ftp;
			cin >> itp >> ftp;
			vpif.push_back(make_pair(itp, 1 - ftp));
		}
		vector<float> vf_b(n + 1, 1); // �ò���offer�ĸ��ʣ����Ϊ1��
		float fmin = 1.0;
		for (int i = 0; i < m; i++) {
			for (int j = n; j >= vpif[i].first; j--) {
				if (vf_b[j] > vf_b[j - vpif[i].first] * vpif[i].second) {
					vf_b[j] = vf_b[j - vpif[i].first] * vpif[i].second;
					if (vf_b[j] < fmin) {
						fmin = vf_b[j];
					}
				}
			}
		}
		printf("%.1f%%\n", (1.0 - fmin) * 100);
	}
	return 0;
}