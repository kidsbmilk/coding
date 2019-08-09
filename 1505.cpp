#include<iostream>
#include<vector>
using namespace std;

struct Dire {
	int up;
	int left;

	Dire() {
		this->up = -1;
		this->left = -1;
	}

	Dire(int up, int left) {
		this->up = up;
		this->left = left;
	}

	Dire(const Dire& copy) {
		this->up = copy.up;
		this->left = copy.left;
	}

	Dire &operator=(const Dire &copy) { // 这个const不能少！
		this->up = copy.up;
		this->left = copy.left;
		return *this;
	}
};

int main() {
	int k;
	while (cin >> k && k) {
		int m, n;
		cin >> m >> n;
		vector<vector<int> > vvi(m, vector<int>(n, 0));
		for (int i = 0; i < m; i ++) {
			for (int j = 0; j < n; j ++) {
				cin >> vvi[i][j];
			}
		}
		vector<vector<Dire> > vvD_b(m, vector<Dire>(n, Dire())); // 记录到某位置为止时的最左与最上边界。
		vvD_b[0][0] = Dire(0, 0);
		int imax = 0;
		for (int i = 0; i < m; i ++) {
			for (int j = 0; j < n; j++) {
				if (vvi[i][j] == 'R') {
					vvD_b[i][j] = Dire(i, j);
				}
				else {
					if (i > 0 && vvi[i - 1][j] == 'F') {
						vvD_b[i][j].up = vvD_b[i - 1][j].up;
					}
					else {
						vvD_b[i][j].up = i;
					}
					if (j > 0 && vvi[i][j - 1] == 'F') {
						vvD_b[i][j].left = vvD_b[i][j - 1].left;
					}
					else {
						vvD_b[i][j].left = j;
					}
					int itp = (i - vvD_b[i][j].up + 1) * (j - vvD_b[i][j].left + 1) * 3;
					if (itp > imax) {
						imax = itp;
					}
				}
			}
		}
		cout << imax << endl;
	}
	return 0;
}