#include<iostream>
using namespace std;

int main() {
    int n;
    while(cin >> n && n) {
        int iFirst = -1, iEnd = -1, iMax = -1, iSum = 0; // �����в�ȫΪ���������յ���������кͲ�Ϊ��������iMax���Գ�ʼ��Ϊ����
        int  iFirstTp = -1, iFirstAll, iEndAll;
        bool isFirst = true, isNewSeq = true;
        while(n --) {
            int iTp;
            //cin >> iTp; // ��Ŀ˵�ˣ��������Ƚϴ��Ƽ�ʹ��scanf��cin�ĺ�ʱ��592MS
            scanf("%d", &iTp); // scanf�ĺ�ʱ��124MS
            if(isFirst) {
                isFirst = false;
                iFirstAll = iTp;
            }
            if(n == 0) {
                iEndAll = iTp;
            }
            if(isNewSeq) {
                iFirstTp = iTp;
                isNewSeq = false;
            }
            if(iSum + iTp >= 0) {
                iSum = iSum + iTp;
                if(iSum > iMax) {
                    iMax = iSum;
                    iFirst = iFirstTp;
                    iEnd = iTp;
                }
            } else {
                iSum = 0;
                isNewSeq = true;
            }
        }
        if(iMax < 0) {
            iMax = 0;
            iFirst = iFirstAll;
            iEnd = iEndAll;
        }
        cout << iMax << " " << iFirst << " " << iEnd << endl;
    }
    return 0;
}
