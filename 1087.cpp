/*
// 超时了
#include<iostream>
#include<vector>
using namespace std;

int main() {
	int n;
	while (cin >> n && n) {
		vector<int> vi(n, 0);
		int isum = 0;
		for (int i = 0; i < n; i++) {
			cin >> vi[i];
			isum += vi[i];
		}
		vector<int> vi_b(isum + 1, 2147483647);
		vi_b[0] = 0;
		int imax = 0;
		for (int i = 0; i < n; i++) {
			for (int j = isum; j >= vi[i]; j--) {
				if (vi_b[j - vi[i]] < vi[i] && vi_b[j] > vi[i]) {
					vi_b[j] = vi[i];
					if (j > imax) {
						imax = j;
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
using namespace std;

int main() {
	int n;
	while (cin >> n && n) {
		vector<int> vi(n + 1, 0);
		vector<int> vi_b(n + 1, 0); // vi_b[i]表示以vi[i]结尾的最大和
		int imax = 0;
		for (int i = 1; i <= n; i++) {
			cin >> vi[i];
			for (int j = 0; j < i; j++) {
				if (vi[i] > vi[j] && vi_b[i] < vi_b[j] + vi[i]) {
					vi_b[i] = vi_b[j] + vi[i];
					if (vi_b[i] > imax) {
						imax = vi_b[i];
					}
				}
			}
		}
		cout << imax << endl;
	}
	return 0;
}