#include<iostream>
#include<vector>
using namespace std;

/*
��̬���򣬾�Ҫ��һ������Ψһ�Եı�ˣ�������Ҫ���������ݵ�������������ı�˾����ܵı�����
��������˼�Ƚ���Ȥ����Ҫ����˼����
Pj��ʾ����j������б���ʱ���ٷ���ץ�ĸ��ʣ�P��ʾ�������ٷ����뱻ץ�Ļ���Ҫ���ڴ˸��ʡ�
Ҳ����˵�����ٷ�������뱻ץ������������ÿ�����ж�����ץ�ĸ��ʵĳ˻���Ҫ���ڵ���1-P��

�Ա�1203��
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
            vf_b[0] = 1; // ʲô������������ץ�ĸ������Ϊ1
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
