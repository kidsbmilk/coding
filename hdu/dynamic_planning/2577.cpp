#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

struct Point {
	int first; // Caps lock亮
	int second; // Caps lock不亮

	Point() {
		this->first = 0;
		this->second = 0;
	}

	Point(int first, int second) {
		this->first = first;
		this->second = second;
	}
};

int main() {
	int t;
	while (cin >> t && t) {
		while (t--) {
			string stp;
			cin >> stp;
			vector<Point> vP; // 到某个字符时的最少敲击次数
			for (int i = 0; i < stp.size(); i++) {
				int ifirsttp, isecondtp;
				if (stp.at(i) >= 'A' && stp.at(i) <= 'Z') { // 当前字符是大写
					if (i - 1 >= 0) {
						ifirsttp = min(vP[i - 1].first + 1, vP[i - 1].second + 2);
						isecondtp = min(vP[i - 1].first + 3, vP[i - 1].second + 2);
					} else {
						ifirsttp = 2;
						isecondtp = 2;
					}
				} else { // 当前字符不是大写
					if (i - 1 >= 0) {
						ifirsttp = min(vP[i - 1].first + 2, vP[i - 1].second + 3);
						isecondtp = min(vP[i - 1].first + 2, vP[i - 1].second + 1);
					}
					else {
						ifirsttp = 3;
						isecondtp = 1;
					}
				}
				vP.push_back(Point(ifirsttp, isecondtp));
			}
			int imin = min(vP[stp.size() - 1].first + 1, vP[stp.size() - 1].second);
			cout << imin << endl;
		}
	}
	return 0;
}