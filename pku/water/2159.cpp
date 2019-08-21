#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
	IOS;
	string a, b;
	while (cin >> a >> b) {
		vector<int> vi1(26, 0), vi2(26, 0);
		for (int i = 0; i < a.size(); i++) {
			vi1[a.at(i) - 'A'] += 1;
		}
		for (int i = 0; i < b.size(); i++) {
			vi2[b.at(i) - 'A'] += 1;
		}
		sort(vi1.begin(), vi1.end());
		sort(vi2.begin(), vi2.end());
		bool isequal = true;
		for (int i = 25; i >= 0; i--) {
			if(vi1[i] == 0 && vi2[i] == 0) {
				break;
			}
			if (vi1[i] != vi2[i]) {
				isequal = false;
				break;
			}
		}
		if (isequal) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}