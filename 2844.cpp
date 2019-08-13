/*
// �����ɨ��߽����˺ܶ��Ż���Ȼ�����ǻᳬʱ��
// ��ʱԭ���������һ��ⷨ��
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		vector<int> vi_coin(n, 0);
		vector<int> vi;
		for (int i = 0; i < n; i++) {
			cin >> vi_coin[i];
		}
		for (int i = 0; i < n; i++) {
			int itp;
			cin >> itp;
			while (itp--) {
				vi.push_back(vi_coin[i]);
			}
		}
		if (m < 0) { // ע�⣺��Ŀû˵��С���٣����Կ����и�ֵ��
			cout << 0 << endl;
			continue;
		}
		sort(vi.begin(), vi.end());
		vector<int> vi_b(m + 1, -1);
		vi_b[0] = 0;
		int istart = 0, iend = 1;
		for (int i = 0; i < vi.size(); i++) {
			istart = min(istart + vi[i], m);
			int ietp = iend;
			for (int j = istart; j >= iend; j--) {
				if (vi_b[j] == -1) {
					if (j - vi[i] < 0) {
						ietp = j;
						break;
					}
					if (vi_b[j - vi[i]] == 0) {
						vi_b[j] = 0;
					}
					else {
						ietp = j - vi[i];
					}
				}
			}
			if (vi_b[ietp] == 0) {
				ietp = istart + 1;
			}
			iend = ietp;
		}
		int ict = 0;
		for (int i = 1; i <= m; i++) {
			if (vi_b[i] == 0) {
				ict += 1;
			}
		}
		cout << ict << endl;
	}
	return 0;
}
*/

/*
// ��Ȼ��ʱ
// ��ʱԭ���������һ��ⷨ��
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		vector<int> vi_coin(n, 0);
		vector<int> vi_num(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> vi_coin[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> vi_num[i];
		}
		if (m < 0) { // ע�⣺��Ŀû˵��С���٣����Կ����и�ֵ��
			cout << 0 << endl;
			continue;
		}
		vector<int> vi_b(m + 1, -1);
		vi_b[0] = 0;
		int iend = 0;
		for (int i = 0; i < n; i++) {
			iend = min(iend, m);
			int ietp = iend;
			for (int j = 0; j <= iend; j++) {
				if (vi_b[j] == 0) {
					for (int k = 1; k <= vi_num[i]; k++) {
						if (j + k * vi_coin[i] > m) {
							break;
						}
						vi_b[j + k * vi_coin[i]] = 0;
					}
					if (j + vi_num[i] * vi_coin[i] > ietp) {
						ietp = j + vi_num[i] * vi_coin[i];
					}
				}
			}
			iend = ietp;
		}
		int ict = 0;
		for (int i = 1; i <= m; i++) {
			if (vi_b[i] == 0) {
				ict += 1;
			}
		}
		cout << ict << endl;
	}
	return 0;
}
*/

// 265ms
// �������Ż���ͬʱ�������ȫ������01����������
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 01������Ԫ�����ޣ��Ӹߵ���ѭ����������ԭ���Ļ����ϣ����ϵ�ǰ��Ԫ�ؿ��Դﵽ��Ч��
void bag01(vector<int>& vi, int icoin, int im) {
	for (int i = im; i >= icoin; i--) {
		if (vi[i] == -1 && vi[i - icoin] == 0) {
			vi[i] = 0;
		}
	}
}

// ��ȫ������Ԫ�����ޣ��ӵ͵���ѭ������������ʹ�ô�Ԫ�ؿ��Դﵽ��Ч��
void bagcomplete(vector<int>& vi, int icoin, int im) {
	for (int i = icoin; i <= im; i++) {
		if (vi[i] == -1 && vi[i - icoin] == 0) {
			vi[i] = 0;
		}
	}
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		vector<int> vi_coin(n, 0);
		vector<int> vi_num(n, 0);
		for (int i = 0; i < n; i++) {
			cin >> vi_coin[i];
		}
		for (int i = 0; i < n; i++) {
			cin >> vi_num[i];
		}
		if (m < 0) { // ע�⣺��Ŀû˵��С���٣����Կ����и�ֵ��
			cout << 0 << endl;
			continue;
		}
		vector<int> vi_b(m + 1, -1);
		vi_b[0] = 0;
		for (int i = 0; i < n; i++) {
			if (vi_num[i] * vi_coin[i] >= m) {
				bagcomplete(vi_b, vi_coin[i], m);
			}
			else {
				int k = 1;
				int inumtp = vi_num[i];
				while (k <= inumtp) {
					bag01(vi_b, k * vi_coin[i], m);
					inumtp -= k;
					k *= 2;
				}
				bag01(vi_b, inumtp * vi_coin[i], m);
			}
		}
		int ict = 0;
		for (int i = 1; i <= m; i++) {
			if (vi_b[i] == 0) {
				ict += 1;
			}
		}
		cout << ict << endl;
	}
	return 0;
}

/*
// 374ms
// �����Ǳ��˵�д����û�г�ʱ����ϸ��һ�£�����ֻ��δ֪Ԫ���ж�һ�Σ��ǳ��죬�ҵ�ǰ������ʱ��������Ϊ����֪Ԫ�ض�ε����ˡ�
// �����εģ�����ⷨ��������Ķ������Ż������Ǽ���Ԫ�ظ������ҵ�ǰ��������Ϊ�Զ����ͬԪ���ظ������ˣ����Գ�ʱ�ˡ�
// ���ﶯ���¼��ʹ�õ�Ԫ�ظ������ǳ����
// ����ⷨ������������棬һ����f[i]����һ���Ǽ�¼ÿ��Ӳ������ʹ�ø�����used[i]��
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n, m;
int a[105], c[105], used[100010];
bool f[100010];
int i, j;
int main() {
	while (scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0) break;
		for (i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (i = 1; i <= n; i++)
			scanf("%d", &c[i]);
		memset(f, 0, sizeof(f));
		f[0] = 1;
		int ans = 0;
		for (i = 1; i <= n; i++)
		{
			memset(used, 0, sizeof(used));
			for (j = a[i]; j <= m; j++)
				if (!f[j] && f[j - a[i]] && used[j - a[i]] < c[i]) // ���ﶯ���¼��ʹ�õ�Ԫ�ظ������ǳ����
				{
					f[j] = 1;
					used[j] = used[j - a[i]] + 1;
					++ans;
				}
		}
		printf("%d\n", ans);
	}
	return 0;
}
*/