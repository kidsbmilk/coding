#include<iostream>
using namespace std;

int main() {
    int n;
    while(cin >> n && n) {
        int iFirst = -1, iEnd = -1, iMax = -1, iSum = 0; // 若序列不全为负，则最终的最大子序列和不为负，所以iMax可以初始化为负。
        int  iFirstTp = -1, iFirstAll, iEndAll;
        bool isFirst = true, isNewSeq = true;
        while(n --) {
            int iTp;
            //cin >> iTp; // 题目说了，输入量比较大，推荐使用scanf。cin的耗时：592MS
            scanf("%d", &iTp); // scanf的耗时：124MS
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
