// ����������û��ô�Ѷ������濴Ӣ�ģ�The inversion number of a given number sequence a1, a2, ..., an is the number of pairs (ai, aj) that satisfy i < j and ai > aj.
// һ��ʼ��Ŀ��˵�ˣ���������ָһ�������д�С˳��ߵ������ֶԵĸ�����Ȼ����Ŀ˵��һЩ�任�����ҳ����б任����С�����������
// ���Ⲣû����ô�Ѷ�������û���濴Ӣ�ģ��뵱Ȼ�ˡ�
// �������˼·����������㷨ע�͡�

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
	vi_seg[index] = vi_seg[index * 2] + vi_seg[index * 2 + 1]; // pushup�Ĳ�����ֱ��д�����ˣ�û���ٶ���һ������
}

int main() {
	IOS;
	int n;
	while (cin >> n && n > 0) {
		vector<int> vi(n + 1, 0); 
		vector<int> vi_seg(n * 4, 0); // ��ʼ����ʹ�������±�����ʾ�߽磬�����build�����Ϳ���ʡȥ�ˣ��Ա������д���������Ҫ����n * 4�ˣ�n * 3�ᱨRE��
		int itp = 0;
		for (int i = 1; i <= n; i++) {
			cin >> vi[i];
			vi[i] += 1; // ��1~n��n����
			itp += query(vi_seg, 1, 1, n, vi[i], n); // ���vi[i]���ü�1Ҳ�У���Ϊvi[i]��û��update��vi_seg�С�
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
			vi[i] += 1; // ��1~n��n����
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
// �����������̫�ã�˼·���Խ���¡�
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
void Build (int u,int left,int right){ // �����build�൱�ڳ�ʼ���߽磬Ȼ������Ԫ�ص�sum����Ϊ0�����ʹ�������±�����ʾ�߽磬�����build�����Ϳ���ʡȥ�ˣ��������д����
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
	node[u].sum = node[L(u)].sum + node[R(u)].sum;   //���ϸ��� ÿ
}
int Query(int u,int p) { //��������p~n
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
		// ��������Կ���������ĸ��Ӷ���Ҫ�����ڣ��ӷǳ�����������ͳ��ĳ���ֵ����ж���������ͨ���߶��������ٲ�ѯ��������ˡ�
		for (i = 0;i < n;i ++){
			scanf ("%d",&a[i]);
			sum += Query(1,a[i]+1); // ��ѯһ���߶���������a[i]+1 ~ n�����ֳ����˶��ٸ�������a[i]��ص�������������a[i]���ü�1Ҳ�У���Ϊa[i]��û��update���߶����С�
			Update(1,a[i]); // ��node[u].l == p && node[u].r == p��λ�õ�node[u].sum����Ϊ1����ʾa[i]�Ѿ��������߶������ˣ������ѯ�߶����õ�ĳ���ֵ�������ʱ�����п��ܽ�a[i]ͳ�ƽ�ȥ�ˡ�
		}
		int ans = sum;
		for (i = 0;i < n;i ++){ // �����ʾѭ�����У�Ȼ��Ѱ����С��������
			sum += n - a[i] - a[i] - 1; // ����ݱ乫ʽ�����������Ҳ���뵽��
			ans = min(ans,sum);
		}
		printf ("%d\n",ans);
	}
	return 0;
}
*/