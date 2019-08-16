// 这个题的题意没那么难懂，认真看英文：The inversion number of a given number sequence a1, a2, ..., an is the number of pairs (ai, aj) that satisfy i < j and ai > aj.
// 一开始题目就说了，逆序数是指一串数字中大小顺序颠倒的数字对的个数，然后题目说了一些变换规则，找出所有变换中最小的逆序对数。
// 题意并没有那么难懂，是我没认真看英文，想当然了。
// 具体解题思路见最下面的算法注释。

#include<iostream>
#include<vector>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

#define left_mode  index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

int query(vector<int>& vi_seg, int index, int left, int right, int L, int R) {
	if (left == L && right == R) {
		return vi_seg[index];
	}
	int mid = (left + right) / 2;
	if (R <= mid) {
		return query(vi_seg, left_mode, L, R);
	} else if (L > mid) {
		return query(vi_seg, right_mode, L, R);
	} else {
		return query(vi_seg, left_mode, L, mid) + query(vi_seg, right_mode, mid + 1, R);
	}
}

void update(vector<int>& vi_seg, int index, int left, int right, int x) {
	if (left == right) {
		vi_seg[index] = 1;
		return;
	}
	int mid = (left + right) / 2;
	if (x <= mid) {
		update(vi_seg, left_mode, x);
	}
	else {
		update(vi_seg, right_mode, x);
	}
	vi_seg[index] = vi_seg[index * 2] + vi_seg[index * 2 + 1]; // pushup的操作，直接写这里了，没有再定义一个函数
}

int main() {
	IOS;
	int n;
	while (cin >> n && n > 0) {
		vector<int> vi(n + 1, 0); 
		vector<int> vi_seg(n * 4, 0); // 初始化，使用数组下标来表示边界，则这个build方法就可以省去了，对比下面的写法。这个又要开到n * 4了，n * 3会报RE。
		int itp = 0;
		for (int i = 1; i <= n; i++) {
			cin >> vi[i];
			vi[i] += 1; // 从1~n共n个数
			itp += query(vi_seg, 1, 1, n, vi[i], n); // 这个vi[i]不用加1也行，因为vi[i]还没有update进vi_seg中。
			update(vi_seg, 1, 1, n, vi[i]);
		}
		int imin = itp;
		for (int i = 1; i <= n; i++) {
			itp = itp - (vi[i] - 1) + n - (vi[i] - 1) - 1;
			if (itp < imin) {
				imin = itp;
			}
		}
		cout << imin << endl;
	}
	return 0;
}

/*
#include<iostream>
#include<vector>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
	IOS;
	int n;
	while (cin >> n && n > 0) {
		vector<int> vi(n + 1, 0);
		int itp = 0;
		for (int i = 1; i <= n; i++) {
			cin >> vi[i];
			vi[i] += 1; // 从1~n共n个数
			for (int j = 0; j <= n; j++) {
				if (vi[j] != 0 && vi[j] > vi[i]) {
					itp += 1;
				}
			}
		}
		int imin = itp;
		for (int i = 1; i <= n; i++) {
			itp = itp - (vi[i] - 1) + n - (vi[i] - 1) - 1;
			if (itp < imin) {
				imin = itp;
			}
		}
		cout << imin << endl;
	}
	return 0;
}
*/

/*
// http://blog.sina.com.cn/s/blog_691ce2b70101ldmm.html
// 这个代码风格不算太好，思路可以借鉴下。
#include
#include
#define L(u) (u<<1)
#define R(u) (u<<1|1)
const int M = 5005;

struct Node{
	int l,r,sum;
}node[M<<2];
int a[M];
int min (int a,int b){
	return a > b ? b : a;
}
void Build (int u,int left,int right){ // 这里的build相当于初始化边界，然后将所有元素的sum设置为0。如果使用数组下标来表示边界，则这个build方法就可以省去了，见上面的写法。
	node[u].l = left,node[u].r = right;
	node[u].sum  = 0;
	if (node[u].l == node[u].r)
		return ;
	int mid = (node[u].l + node[u].r)>>1;
	Build (L(u),left,mid);
	Build (R(u),mid+1,right);
}
void Update(int u,int p){
	if (node[u].l == node[u].r){
		node[u].sum ++;
		return ;
	}
	if (p <= node[L(u)].r) Update(L(u),p);
	else Update(R(u),p);
	node[u].sum = node[L(u)].sum + node[R(u)].sum;   //向上更新 每
}
int Query(int u,int p) { //查找区间p~n
	if (p <= node[u].l)
		return node[u].sum;
	if (p <= node[L(u)].r)
		return Query(L(u),p) + Query(R(u),p);
	else return Query(R(u),p);
}
int main (){
	int n,i;
	while (~scanf ("%d",&n)){
		Build(1,0,n);
		int sum = 0;
		// 从这里可以看到，此题的复杂度主要集中在：从非常长的序列中统计某数字的序列对数。这里通过线段树来加速查询逆序对数了。
		for (i = 0;i < n;i ++){
			scanf ("%d",&a[i]);
			sum += Query(1,a[i]+1); // 查询一下线段树，看看a[i]+1 ~ n的数字出现了多少个，即与a[i]相关的逆序对数。这个a[i]不用加1也行，因为a[i]还没有update进线段树中。
			Update(1,a[i]); // 将node[u].l == p && node[u].r == p的位置的node[u].sum设置为1，表示a[i]已经存在于线段树中了，后面查询线段树得到某数字的逆序数时，就有可能将a[i]统计进去了。
		}
		int ans = sum;
		for (i = 0;i < n;i ++){ // 这里表示循环序列，然后寻找最小的序列数
			sum += n - a[i] - a[i] - 1; // 这个演变公式认真分析，我也能想到。
			ans = min(ans,sum);
		}
		printf ("%d\n",ans);
	}
	return 0;
}
*/