#include<iostream>
#include<vector>
using namespace std;

int main() {
	int t;
	while (cin >> t && t) {
		while (t--) {
			int n, v;
			cin >> n >> v;
			vector<int> vi_value(n, 0);
			vector<int> vi_volume(n, 0);
			for (int i = 0; i < n; i++) {
				cin >> vi_value[i];
			}
			for (int i = 0; i < n; i++) {
				cin >> vi_volume[i];
			}
			vector<int> vi_b(v + 1, 0);
			for (int i = 0; i < n; i++) {
				for (int j = v; j >= vi_volume[i]; j--) {
					if (vi_b[j] < vi_b[j - vi_volume[i]] + vi_value[i]) {
						vi_b[j] = vi_b[j - vi_volume[i]] + vi_value[i];
					}
				}
			}
			cout << vi_b[v] << endl;
		}
	}
	return 0;
}