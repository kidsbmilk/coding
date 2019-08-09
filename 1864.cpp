#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*
动态规则，就要找一个具有唯一性的标杆，这个标杆要能体现数据的组合情况，此题的标杆就是发票金额。
注意几个点：
1、金额是小数，但是题目说了最多两位小数，所以，乘以100后，就可以转为整数来作为数组下标了；
2、单项物品价值不得超过600，但是只有A、B、C、D、X等等这些类，如果某发票上有多个A，要使加起来的和满足不超过600的条件，
仔细想一想也合理，但又有点觉得题目说的不够精准：每项应该改为每类。
*/
int main() {
    float Q;
    int N;
    while(cin >> Q >> N && N) {
        Q = Q * 100;
        vector<int> vi;
        while(N --) {
            int mTp;
            float pSumTp = 0.0;
            bool isAddTp = true;
            cin >> mTp;
            vector<float> viTp(3, 0.0);
            while(mTp --) {
                string sTp;
                cin >> sTp;
                char tTp = sTp.at(0);
                float pTp = stof(sTp.substr(2));
                pSumTp += pTp;
                if(isAddTp) {
                    if(tTp - 'A' >= 0 && tTp - 'A' <= 2) {
                        viTp[tTp - 'A'] += pTp;
                    }
                    if(tTp < 'A' || tTp > 'C' || viTp[tTp - 'A'] > 600 || pSumTp > 1000) {
                        isAddTp = false;
                    }
                }
            }
            if(isAddTp) {
                vi.push_back(pSumTp * 100);
            }
        }
        vector<int> vi_b(30 * 1000 * 100 + 10, -1);
        vi_b[0] = 0;
        int iMax = 0;
        for(int i = 0; i < vi.size(); i ++) {
            for(int j = vi_b.size() - 1; j >= vi[i]; j --) {
                if(vi_b[j - vi[i]] != -1) { // 可以直接将vi_b[j]设置为金额，不用vi_b[j - vi[i]]是否已经有了，后面会慢慢更新掉。
                    if(j <= Q) {
                        vi_b[j] = 1;
                        if(j > iMax) {
                            iMax = j;
                        }
                    }
                }
            }
        }
        printf("%.2f\n", iMax / 100.0); // cout输出2位小数太麻烦了，直接用printf了。
    }
    return 0;
}
