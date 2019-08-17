#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<sstream>
using namespace std;

int main() {
    string R;
    int n;
    while(cin >> R >> n && n) {
        vector<int> vi(27 * 3, 0);
        vi[vi.size() - 1] = 1;
        long long lR = 0;
		for (int i = 0; i < R.size(); i++) { // atof可能会出现错误。
			if (R.at(i) != '.') {
				lR = lR * 10 + (R.at(i) - '0');
			}
		}
		int ntp = n;
        while(ntp --) {
            for(int i = vi.size() - 1; i >= 0; i --) {
                vi[i] = vi[i] * lR;
            }
            int itp = vi.size() - 1;
            while(itp - 1 >= 0) {
				vi[itp - 1] += vi[itp] / 10000;
                vi[itp] = vi[itp] % 10000;
                itp --;
            }
        }
        string sres = "";
		bool isfirst = true;
		bool isNonEmptyFirst = true;
        for(int i = 0; i < vi.size(); i++) {
			if (isNonEmptyFirst && vi[i] == 0) {
				continue;
			}
			stringstream ss;
			ss << vi[i];
			string stp = ss.str();
			if (isfirst == false) {
				while (stp.size() < 4) {
					stp = "0" + stp;
				}
			}
			else {
				isfirst = false;
			}
			sres += stp;
			isNonEmptyFirst = false;
        }
		if (R.find('.') != R.npos) {
			int posIndex = (R.length() - 1 - R.find('.')) * n;
			while (sres.size() < posIndex) {
				sres = "0" + sres;
			}
			posIndex = sres.size() - posIndex;
			sres.insert(posIndex, ".");
			// 去除小数点后面的0
			int stopInd = sres.size();
			for (int i = sres.size() - 1; i >= posIndex; i--) {
				if (sres[i] == '.' || sres[i] == '0') {
					stopInd = i;
				}
				else {
					break;
				}
			}
			cout << sres.substr(0, stopInd) << endl;
		}
		else {
			cout << sres << endl;
		}
		
    }
    return 0;
}
