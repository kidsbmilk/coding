// ������Ϊ�������������ͣ�ֻ���ۼӣ��ۼ�������������߶������١��ۼӸ��˵Ĵ���ǣ�̫���ˣ����ܻᳬʱ�����ǣ�10000���ڵ�������û�ж��٣������ۼӰɡ�
// ��ʹ�����߶�����ҲҪѭ�������߽磬ֻ�Ǽ������������Ӷ��ѡ�Ŀǰ���д���Ѿ��ǳ����ˡ�

#include<iostream>
#include<vector>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin_tie(0)

int main() {
	vector<int> vi;
	vi.push_back(2);
	for (int i = 3; i <= 10000; i++) {
		int itp = sqrt(float(i)) + 1;
		bool isprim = true;
		for (int j = 2; j < itp; j++) {
			if (i % j == 0) {
				isprim = false;
				break;
			}
		}
		if (isprim) {
			vi.push_back(i);
		}
	}
	map<int, int> mii;
	int n;
	while (cin >> n && n) {
		mii[n] = 0;
		for (int i = 0; i < vi.size(); i++) {
			int isumtp = vi[i];
			for (int j = i + 1; j < vi.size(); j++) {
				if (isumtp < n) {
					isumtp += vi[j];
				}
				else if (isumtp > n) {
					break;
				}
				else {
					mii[n] += 1;
					break;
				}
			}
		}
		cout << mii[n] << endl;
	}
	return 0;
}