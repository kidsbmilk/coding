#include<iostream>
#include<vector>
using namespace std;

// ��1505�ǳ���

int main() {
	int n;
	while (cin >> n && n) {
		vector<vector<int> > vvi(n + 1, vector<int> (n + 1, 0));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> vvi[i][j];
				vvi[i][j] += vvi[i][j - 1];
			}
		}
		int imax = vvi[0][0];
		for (int i = 1; i < n; i++) { // �е���ʼ�±�
			for (int j = i + 1; j <= n; j++) { // �е���ֹ�±�
				int isum = 0; // ���ڲ��Ĵ������������������к�
				for (int k = 1; k <= n; k++) {
					isum += vvi[k][j] - vvi[k][i - 1]; // ���ϵ�ǰ�еĳ���
					if (isum < 0) isum = 0;
					if (isum > imax) imax = isum;
				}
			}
		}
		cout << imax << endl;
	}
	return 0;
}