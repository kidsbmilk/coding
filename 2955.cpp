#include<iostream>
#include<vector>
using namespace std;

/*
动态规则，就要找一个具有唯一性的标杆，这个标杆要能体现数据的组合情况，此题的标杆就是总的被抢金额。
这个题的意思比较有趣，需要认真思考：
Pj表示的是j这个银行被抢时抢劫犯被抓的概率，P表示的是抢劫犯不想被抓的话需要低于此概率。
也就是说：抢劫犯如果不想被抓，则在所抢的每个银行都不被抓的概率的乘积需要大于等于1-P。

对比1203。
*/
int main() {
    int T;
    while(cin >> T && T) {
        for(int circle = 0; circle < T; circle ++) {
            float P;
            int N;
            int ALL = 0;
            cin >> P >> N;
            vector<pair<int, float> > vpif;
            for(int i = 0; i < N; i ++) {
                int itp;
                float ftp;
                cin >> itp >> ftp;
                ALL += itp;
                vpif.push_back(make_pair(itp, 1 - ftp));
            }
            vector<float> vf_b(ALL + 1, 0);
            vf_b[0] = 1; // 什么都不抢，不被抓的概率最大，为1
            int maxi = 0;
            for(int i = 0; i < N; i ++) {
                for(int j = ALL; j >= vpif[i].first; j --) {
                    float ftp = vf_b[j - vpif[i].first] * vpif[i].second;
                    if(ftp >= 1 - P && ftp > vf_b[j]) {
                        vf_b[j] = ftp;
                        if(j > maxi) {
                            maxi = j;
                        }
                    }
                }
            }
            cout << maxi << endl;
        }
    }
    return 0;
}
