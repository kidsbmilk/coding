#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushup(vector<int>& vi_seg, int index) {
	vi_seg[index] = max(vi_seg[index * 2], vi_seg[index * 2 + 1]);
}

void update(vector<int>& vi_seg, int index, int left, int right, int v) {
	if (left == right) {
		vi_seg[index] -= v;
		cout << left << endl;
		return;
	}
	int mid = (left + right) / 2;
	if (vi_seg[index * 2] >= v) { // ���������Ƚϣ�Ҳ����vi_seg���ֵһ�Ƚϣ���ʹ�ô�ͳ�ı߽硢��Χ���Ƚϡ����ң������������ȡ�
		// ����ֻ���Կ�����������ʾ���õ����������Ϊ��Ŀ˵�ˣ����ϵ��¡�������������������
		update(vi_seg, left_mode, v);
	}
	else {
		update(vi_seg, right_mode, v);
	}
	pushup(vi_seg, index);
}

int main() {
	IOS;
	int h, w, n;
	while (cin >> h >> w >> n && h && w && n) {
		int isize = min(h, n);
		vector<int> vi_seg(isize * 4 + 10, w);
		for (int i = 0; i < n; i++) {
			int itp;
			cin >> itp;
			if (vi_seg[1] < itp) {
				cout << -1 << endl;
			}
			else {
				update(vi_seg, 1, 1, isize, itp);
			}
		}
	}
	return 0;
}