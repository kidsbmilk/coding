#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

// ����Ӿ���ͣ�https://blog.csdn.net/sinat_40948489/article/details/80274460 ��1505�е���
// 1559�Ƕ�ά���档

int main() {
	int t;
	while (cin >> t && t) {
		while (t--) { // ֮ǰ��Ȼ�������whileѭ���ˣ��˼���Ŀ˵�ˣ��������ݡ�
			int m, n, x, y;
			cin >> m >> n >> x >> y;
			vector<vector<int> > vvi(m + 1, vector<int>(n + 1, 0));
			int imax = 0;
			for (int i = 1; i <= m; i++) {
				for (int j = 1; j <= n; j++) {
					// cin >> vvi[i][j];
					scanf("%d", &vvi[i][j]);
					vvi[i][j] += vvi[i - 1][j] + vvi[i][j - 1] - vvi[i - 1][j - 1];
					if (i >= x && j >= y) {
						int itp = vvi[i][j] - vvi[i - x][j] - vvi[i][j - y] + vvi[i - x][j - y];
						if (itp > imax) {
							imax = itp;
						}
					}
					/*
					// ����ߵ������У��Ǵ���Ĵ��룬������Ϊ���ݽ�����Ҳ�ܹ���
					if (i >= y && j >= x) {
						int itp = vvi[i][j] - vvi[i - y][j] - vvi[i][j - x] + vvi[i - y][j - x];
						if (itp > imax) {
							imax = itp;
						}
					}*/
				}
			}
			cout << imax << endl;
		}
	}
	return 0;
}
