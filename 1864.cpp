#include<iostream>
#include<vector>
#include<string>
using namespace std;

/*
��̬���򣬾�Ҫ��һ������Ψһ�Եı�ˣ�������Ҫ���������ݵ�������������ı�˾��Ƿ�Ʊ��
ע�⼸���㣺
1�������С����������Ŀ˵�������λС�������ԣ�����100�󣬾Ϳ���תΪ��������Ϊ�����±��ˣ�
2��������Ʒ��ֵ���ó���600������ֻ��A��B��C��D��X�ȵ���Щ�࣬���ĳ��Ʊ���ж��A��Ҫʹ�������ĺ����㲻����600��������
��ϸ��һ��Ҳ���������е������Ŀ˵�Ĳ�����׼��ÿ��Ӧ�ø�Ϊÿ�ࡣ
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
                if(vi_b[j - vi[i]] != -1) { // ����ֱ�ӽ�vi_b[j]����Ϊ������vi_b[j - vi[i]]�Ƿ��Ѿ����ˣ�������������µ���
                    if(j <= Q) {
                        vi_b[j] = 1;
                        if(j > iMax) {
                            iMax = j;
                        }
                    }
                }
            }
        }
        printf("%.2f\n", iMax / 100.0); // cout���2λС��̫�鷳�ˣ�ֱ����printf�ˡ�
    }
    return 0;
}
