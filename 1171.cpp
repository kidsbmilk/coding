#include<iostream>
#include<vector>
using namespace std;

int main() {
	int n;
	while (cin >> n && n > 0) {
		vector<int> vi;
		int isum = 0;
		for (int i = 0; i < n; i++) {
			int v, m;
			cin >> v >> m;
			while (m--) {
				vi.push_back(v);
				isum += v;
			}
		}
		int iv = isum / 2; // ±³°üÈÝÁ¿
		vector<int> vi_b;
	}
	return 0;
}