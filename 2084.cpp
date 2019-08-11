#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int c;
	while (cin >> c && c) {
		while (c--) {
			int n;
			cin >> n;
			vector<vector<int> > vvi(n + 1, vector<int>(n + 1, 0));
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= i; j++) {
					cin >> vvi[i][j];
				}
			}
			vector<vector<int> > vvi_b(n + 1, vector<int>(n + 1, 0));
			int imax = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= i; j++) {
					int itp = vvi_b[i - 1][j - 1] + vvi[i][j];
					itp = max(itp, vvi_b[i - 1][j] + vvi[i][j]);
					if (vvi_b[i][j] < itp) {
						vvi_b[i][j] = itp;
						if (itp > imax) {
							imax = itp;
						}
					}
				}
			}
			cout << imax << endl;
		}
	}
	return 0;
}