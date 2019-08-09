/*
#include<iostream>
#include<vector>
using namespace std;

// ����汾ֱ����ÿ��Ԫ�ص����ұ߽磬��ʱ�ˡ�
// ����汾��˼�����������ұ߽磬�뷨û�����⣬ֻ��ʵ����Ч��̫���ˣ�û��ץס���ݵ��ص㣬�������ʵ�֡�
// ��Ȼ�Ƕ�̬�滮����Ҫ��һ����ˣ����ʵ���У���û���õ���̬�滮�����Գ�ʱ�ˡ�
int main() {
    long long n;
    while(cin >> n && n) {
        vector<long long> vi;
        while(n --) {
            long long itp;
            cin >> itp;
            vi.push_back(itp);
        }
        // Ѱ������߽�
        vector<long long> viPositive(vi.size(), -1);
        for(long long i = 0; i < vi.size(); i ++) {
            for(long long j = 0; j < i; j ++) {
                if(viPositive[j] == -1 && vi[j] > vi[i]) {
                    viPositive[j] = i - 1;
                }
            }
        }
        for(long long i = 0; i < vi.size(); i ++) {
            if(viPositive[i] == -1) {
                viPositive[i] = vi.size() - 1;
            }
        }
        // Ѱ�ҷ���߽�
        vector<long long> viNegative(vi.size(), -1);
        for(long long i = vi.size() - 1; i >= 0; i --) {
            for(long long j = vi.size() - 1; j > i; j --) {
                if(viNegative[j] == -1 && vi[j] > vi[i]) {
                    viNegative[j] = i + 1;
                }
            }
        }
        for(long long i = vi.size() - 1; i >= 0; i --) {
            if(viNegative[i] == -1) {
                viNegative[i] = 0;
            }
        }
        long long llmax = 0;
        for(long long i = 0; i < vi.size(); i ++) {
            long long llTp = (viPositive[i] - viNegative[i] + 1) * vi[i];
            if(llTp > llmax) {
                llmax = llTp;
            }
        }
        cout << llmax << endl;
    }
    return 0;
}
*/

/*
// ����汾�У��õ��˶�̬�滮��������ÿ��Ԫ�ص����ұ߽��ϣ�������ֱ���������������ϡ�
// ��ȻҪ�ö�̬�滮���͵���һ����ˣ���˾���ĳλ���ϵ�Ԫ�ؿ�����������߽��������ұ߽磬������Ѱ�Һ���Ԫ�ص������߽��������ұ߽�ʱ��
// �Ϳ��������Ѿ�����ı߽�����ʵ�ֿ��ټ����ˡ�
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

int main() {
    long long n;
    while(cin >> n && n) {
        vector<long long> vi; // intʱ��WA���о��е���֣�����Ŀ����˼����û�г˷���intҲ���㹻�ġ�
        while (n --) {
            long long itp;
            // cin >> itp; // ����Ч�ʵͲ�������scanf�����ԡ�452ms
			scanf("%lld", &itp); // 124ms
            vi.push_back(itp);
        }
		vector<int> vi_b_left(vi.size(), 0);
        for(int i = 0; i < vi.size(); i ++) {
			for (int j = i - 1; j >= 0; ) {
				if (vi[j] >= vi[i]) {
					j = vi_b_left[j] - 1;
				}
				else {
					vi_b_left[i] = j + 1;
					break;
				}
			}
        }
		vector<int> vi_b_right(vi.size(), vi.size() - 1);
		for (int i = vi.size() - 1; i >= 0; i--) {
			for (int j = i + 1; j < vi.size(); ) {
				if (vi[j] >= vi[i]) {
					j = vi_b_right[j] + 1;
				}
				else {
					vi_b_right[i] = j - 1;
					break;
				}
			}
		}
		long long llmax = 0;
		for (int i = 0; i < vi.size(); i++) {
			long long lltp = (vi_b_right[i] - vi_b_left[i] + 1) * vi[i];
			if (lltp > llmax) {
				llmax = lltp;
			}
		}
        cout << llmax << endl;
    }
    return 0;
}
*/

// ����ջʵ�֣�����ջҲֻ��Ѱ�������߽��������ұ߽�
// ����ջ��ʵ����������/���������еģ����ڲ�������������/������������Ҫʹ�ö�̬�滮���ο�hdoj 1025��
#include<iostream>
#include<vector>
#include<stack>
#include<cstdio>
using namespace std;

int main() {
	int n;
	while (cin >> n && n) {
		vector<long long> vi(n, 0);
		for (int i = 0; i < n; i ++) {
			// cin >> vi[i]; // 483ms
			scanf("%lld", &vi[i]); // 171ms
		}
		stack<int> si;
		vector<int> vi_b_left(n, 0);
		for (int i = 0; i < n; i++) {
			while (si.size() && vi[si.top()] >= vi[i]) {
				si.pop();
			}
			if (!si.empty()) {
				vi_b_left[i] = si.top() + 1;
			}
			si.push(i);
		}
		stack<int> ().swap(si);
		vector<int> vi_b_right(n, n - 1);
		for (int i = n - 1; i >= 0; i--) {
			while (si.size() && vi[si.top()] >= vi[i]) {
				si.pop();
			}
			if (!si.empty()) {
				vi_b_right[i] = si.top() - 1;
			}
			si.push(i);
		}
		long long llmax = 0;
		for (int i = 0; i < n; i++) {
			long long lltp = (vi_b_right[i] - vi_b_left[i] + 1) * vi[i];
			if (lltp > llmax) {
				llmax = lltp;
			}
		}
		cout << llmax << endl;
	}
	return 0;
}