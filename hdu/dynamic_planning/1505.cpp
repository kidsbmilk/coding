/*
// ��̬�滮��390ms
#include<iostream>
#include<vector>
#include<algorithm> // min, max
using namespace std;

// ����Ӿ���ͣ�https://blog.csdn.net/sinat_40948489/article/details/80274460 ��1081����1505�е���

int main() {
	int k;
	while (cin >> k && k) {
		while (k--) {
			int m, n;
			cin >> m >> n;
			vector<vector<int> > vvi(m, vector<int>(n, 0));
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					char ctp;
					cin >> ctp;
					vvi[i][j] = ctp;
				}
			}
			vector<int> vi_height(n, 0);
			int imax = 0;
			for (int i = 0; i < m; i++) { // ��ÿһ�п�ʼɨ�衢���㣬�൱�ڰ�1506���һά��չ����ά�ˡ�
				vector<int> vi_start_col(n, 0);
				vector<int> vi_end_col(n, 0);
				for (int j = 0; j < n; j++) {
					vi_start_col[j] = j;
					vi_end_col[j] = j;
					if (vvi[i][j] == 'F') vi_height[j] ++; // ���vi_height�ᴩ�������У��γɵ�ǰ����Ŀ��߶ȡ�
					else vi_height[j] = 0;
				}
				for (int j = 0; j < n; j++) {
					if (vi_height[j] == 0) continue; // �ڵ���ջ��ʵ���У�������continue����Ϊ����0�Ļ�����ʹջ�в�������Ӧ���±꣬����vi_start_col[j] = 0��
					// ��̬�����п�����continue���ټ��㣬����Ϊ������������-1���жϵģ��������߶�Ϊ0���±ꡣ
					while (vi_start_col[j] - 1 >= 0 && vi_height[j] <= vi_height[vi_start_col[j] - 1]) {
						vi_start_col[j] = vi_start_col[vi_start_col[j] - 1]; // ����vi_height[j]�߶��µľ������߽磬�����ȵ���ʼ�±ꡣ
					}
				}
				for (int j = n - 1; j >= 0; j--) {
					if (vi_height[j] == 0) continue; // �ڵ���ջ��ʵ���У�������continue����Ϊ����0�Ļ�����ʹջ�в�������Ӧ���±꣬����vi_start_col[j] = n - 1��
					// ��̬�����п�����continue���ټ��㣬����Ϊ������������-1���жϵģ��������߶�Ϊ0���±ꡣ
					while (vi_end_col[j] + 1 <= n - 1 && vi_height[j] <= vi_height[vi_end_col[j] + 1]) {
						vi_end_col[j] = vi_end_col[vi_end_col[j] + 1]; // ����vi_height[j]�߶��µľ�����ұ߽磬�����ȵĽ����±ꡣ
					}
				}
				for (int j = 0; j < n; j++) {
					imax = max(imax, (vi_end_col[j] - vi_start_col[j] + 1) * vi_height[j] * 3);
				}
			}
			cout << imax << endl;
		}
	}
	return 0;
}
*/

// ����ջ��514ms
#include<iostream>
#include<vector>
#include<algorithm> // min, max
#include<stack>
using namespace std;

int main() {
	int k;
	while (cin >> k && k) {
		while (k--) {
			int m, n;
			cin >> m >> n;
			vector<vector<int> > vvi(m, vector<int>(n, 0));
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					char ctp;
					cin >> ctp;
					vvi[i][j] = ctp;
				}
			}
			vector<int> vi_height(n, 0);
			int imax = 0;
			for (int i = 0; i < m; i++) { // ��ÿһ�п�ʼɨ�衢���㣬�൱�ڰ�1506���һά��չ����ά�ˡ�
				vector<int> vi_start_col(n, 0);
				vector<int> vi_end_col(n, 0);
				for (int j = 0; j < n; j++) {
					vi_start_col[j] = j;
					vi_end_col[j] = j;
					if (vvi[i][j] == 'F') vi_height[j] ++; // ���vi_height�ᴩ�������У��γɵ�ǰ����Ŀ��߶ȡ�
					else vi_height[j] = 0;
				}
				stack<int> si;
				for (int j = 0; j < n; j++) {
					// if (vi_height[j] == 0) continue; // �ڵ���ջ��ʵ���У�������continue����Ϊ����0�Ļ�����ʹջ�в�������Ӧ���±꣬����vi_start_col[j] = 0��
					// ��̬�����п�����continue���ټ��㣬����Ϊ������������-1���жϵģ��������߶�Ϊ0���±ꡣ
					while (si.size() && vi_height[si.top()] >= vi_height[j]) {
						si.pop();
					}
					// ����vi_height[j]�߶��µľ������߽磬�����ȵ���ʼ�±ꡣ
					if (si.empty()) vi_start_col[j] = 0;
					else {
						vi_start_col[j] = si.top() + 1;
					}
					si.push(j);
				}
				stack<int> ().swap(si);
				for (int j = n - 1; j >= 0; j--) {
					// if (vi_height[j] == 0) continue; // �ڵ���ջ��ʵ���У�������continue����Ϊ����0�Ļ�����ʹջ�в�������Ӧ���±꣬����vi_start_col[j] = n - 1��
					// ��̬�����п�����continue���ټ��㣬����Ϊ������������-1���жϵģ��������߶�Ϊ0���±ꡣ
					while (si.size() && vi_height[si.top()] >= vi_height[j]) {
						si.pop();
					}
					// ����vi_height[j]�߶��µľ�����ұ߽磬�����ȵĽ����±ꡣ
					if (si.empty()) vi_end_col[j] = n - 1;
					else {
						vi_end_col[j] = si.top() - 1;
					}
					si.push(j);
				}
				for (int j = 0; j < n; j++) {
					imax = max(imax, (vi_end_col[j] - vi_start_col[j] + 1) * vi_height[j] * 3);
				}
			}
			cout << imax << endl;
		}
	}
	return 0;
}