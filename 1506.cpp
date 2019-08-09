/*
#include<iostream>
#include<vector>
using namespace std;

// 这个版本直接搜每个元素的左右边界，超时了。
// 这个版本的思想是搜索左右边界，想法没有问题，只是实现上效率太低了，没有抓住数据的特点，看下面的实现。
// 既然是动态规划，就要找一个标杆，这个实现中，并没有用到动态规划，所以超时了。
int main() {
    long long n;
    while(cin >> n && n) {
        vector<long long> vi;
        while(n --) {
            long long itp;
            cin >> itp;
            vi.push_back(itp);
        }
        // 寻找正向边界
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
        // 寻找反向边界
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
// 这个版本中，用到了动态规划，用在求每个元素的左右边界上，并不是直接用在求最大面积上。
// 既然要用动态规划，就得找一个标杆，标杆就是某位置上的元素可延伸的最大左边界或者最大右边界，这样在寻找后面元素的最大左边界或者最大右边界时，
// 就可以依据已经求出的边界数组实现快速计算了。
#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;

int main() {
    long long n;
    while(cin >> n && n) {
        vector<long long> vi; // int时会WA，感觉有点奇怪，依题目的意思，又没有乘法，int也是足够的。
        while (n --) {
            long long itp;
            // cin >> itp; // 看看效率低不，换成scanf再试试。452ms
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

// 单调栈实现，单调栈也只是寻找最大左边界或者最大右边界
// 单调栈是实现连序升序/降序子序列的，对于不连序的最大升序/降序子序列需要使用动态规划，参考hdoj 1025。
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