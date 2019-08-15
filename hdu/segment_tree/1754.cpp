/*
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

void pushup(vector<int>& vi_seg, int index) {
	vi_seg[index] = max(vi_seg[index * 2], vi_seg[index * 2 + 1]);
}

// index��ʾvi_seg�е��±꣬���߶����б���������±꣬left��right���߶����е����������ޣ��������������洢��������ʹ�������±������ر�ʾ��index�����������޵Ĺ�ϵ��
// ͬʱ��index����Ԫ�ض�Ӧ�����������ֵ���������ʾ�����ڵ����ֵ��
void build(const vector<int> &vi_origin, vector<int>& vi_seg, int index, int left, int right) { // ��vi_origin����ָ����Զ���������֯��ʽд�뵽vi_seg���vi_seg����±�����֯���ӽڵ��ϵ��
	if (left == right) {
		vi_seg[index] = vi_origin[left];
		return;
	}
	int mid = (left + right) / 2;
	build(vi_origin, vi_seg, index * 2, left, mid);
	build(vi_origin, vi_seg, index * 2 + 1, mid + 1, right);
	pushup(vi_seg, index);
}

void update(vector<int>& vi_seg, int index, int left, int right, int x, int v) {
	if (left == x && right == x) {
		vi_seg[index] = v;
		return;
	}
	int mid = (left + right) / 2;
	if (x <= mid) {
		update(vi_seg, index * 2, left, mid, x, v);
	}
	else {
		update(vi_seg, index * 2 + 1, mid + 1, right, x, v);
	}
	pushup(vi_seg, index);
}

int query(const vector<int>& vi_seg, int index, int left, int right, int L, int R) {
	if (L <= left && right <= R) { // ���û������[L, R]���������[left, right]����һ��ʼ�ʹ�����ֱ��������Ҷ�ӽڵ㣬���Ի�ͼ��һ����
		// ������дΪL == left && right == R���ᳬ�ڴ����ƣ������ˣ�����
		return vi_seg[index];
	}
	int mid = (left + right) / 2;
	int ans = 0;
	if (L <= mid) {
		ans = max(ans, query(vi_seg, index * 2, left, mid, L, R));
	}
	if(R > mid) {
		ans = max(ans, query(vi_seg, index * 2 + 1, mid + 1, right, L, R));
	}
	return ans;
}

int main() {
	IOS;
	int n, m;
	while (cin >> n >> m && n && m) {
		vector<int> vi_origin(n + 1, 0);
		for (int i = 1; i <= n; i++) { // �����±��1��ʼ��Ϊ���������潨�����䱣��һ�£��������
			cin >> vi_origin[i];
		}
		vector<int> vi_seg(n * 3); // ��n��Ҷ�ӽڵ����ȫ�����������2n - 1���ڵ㣬���Կ���2n���ռ�Ϳ����ˣ�ֻʹ��1~2*n-1���±ꡣ
		// TODO�����ǣ�n * 2��Ȼ��Runtime Error������n * 3�Ϳ����ˣ���̫����Ϊʲô������
		build(vi_origin, vi_seg, 1, 1, n); // ��һ��1��ʾ�߶����Ķ�������ʽ�ĸ��ڵ������±�1���������1��n��ʾ��������Ч��ѯ����Ϊ1~n
		char c;
		int ix, iy;
		while (m--) {
			cin >> c >> ix >> iy;
			if (c == 'Q') {
				cout << query(vi_seg, 1, 1, n, ix, iy) << endl; // �����1, 1, n�ĺ����build���ĺ�����ͬ
			}
			else {
				update(vi_seg, 1, 1, n, ix, iy); // �����1, 1, n�ĺ����build���ĺ�����ͬ
			}
		}
	}
	return 0;
}
*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define IOS ios_base::sync_with_stdio(0); cin.tie(0);

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushup(vector<int>& vi_seg, int index) {
	vi_seg[index] = max(vi_seg[index * 2], vi_seg[index * 2 + 1]);
}

// index��ʾvi_seg�е��±꣬���߶����б���������±꣬left��right���߶����е����������ޣ��������������洢��������ʹ�������±������ر�ʾ��index�����������޵Ĺ�ϵ��
// ͬʱ��index����Ԫ�ض�Ӧ�����������ֵ���������ʾ�����ڵ����ֵ��
void build(const vector<int>& vi_origin, vector<int>& vi_seg, int index, int left, int right) { // ��vi_origin����ָ����Զ���������֯��ʽд�뵽vi_seg���vi_seg����±�����֯���ӽڵ��ϵ��
	if (left == right) {
		vi_seg[index] = vi_origin[left];
		return;
	}
	int mid = (left + right) / 2;
	build(vi_origin, vi_seg, left_mode);
	build(vi_origin, vi_seg, right_mode);
	pushup(vi_seg, index);
}

void update(vector<int>& vi_seg, int index, int left, int right, int x, int v) {
	if (left == x && right == x) {
		vi_seg[index] = v;
		return;
	}
	int mid = (left + right) / 2;
	if (x <= mid) {
		update(vi_seg, left_mode, x, v);
	}
	else {
		update(vi_seg, right_mode, x, v);
	}
	pushup(vi_seg, index);
}

int query(const vector<int>& vi_seg, int index, int left, int right, int L, int R) {
	if (L <= left && right <= R) { // ���û������[L, R]���������[left, right]����һ��ʼ�ʹ�����ֱ��������Ҷ�ӽڵ㣬���Ի�ͼ��һ����
		// ������дΪL == left && right == R���ᳬ�ڴ����ƣ������ˣ�����
		return vi_seg[index];
	}
	int mid = (left + right) / 2;
	int ans = 0;
	if (L <= mid) {
		ans = max(ans, query(vi_seg, left_mode, L, R));
	}
	if (R > mid) {
		ans = max(ans, query(vi_seg, right_mode, L, R));
	}
	return ans;
}

int main() {
	IOS;
	int n, m;
	while (cin >> n >> m && n && m) {
		vector<int> vi_origin(n + 1, 0);
		for (int i = 1; i <= n; i++) { // �����±��1��ʼ��Ϊ���������潨�����䱣��һ�£��������
			cin >> vi_origin[i];
		}
		vector<int> vi_seg(n * 3); // ��n��Ҷ�ӽڵ����ȫ�����������2n - 1���ڵ㣬���Կ���2n���ռ�Ϳ����ˣ�ֻʹ��1~2*n-1���±ꡣ
		// TODO�����ǣ�n * 2��Ȼ��Runtime Error������n * 3�Ϳ����ˣ���̫����Ϊʲô������
		build(vi_origin, vi_seg, 1, 1, n); // ��һ��1��ʾ�߶����Ķ�������ʽ�ĸ��ڵ������±�1���������1��n��ʾ��������Ч��ѯ����Ϊ1~n
		char c;
		int ix, iy;
		while (m--) {
			cin >> c >> ix >> iy;
			if (c == 'Q') {
				cout << query(vi_seg, 1, 1, n, ix, iy) << endl; // �����1, 1, n�ĺ����build���ĺ�����ͬ
			}
			else {
				update(vi_seg, 1, 1, n, ix, iy); // �����1, 1, n�ĺ����build���ĺ�����ͬ
			}
		}
	}
	return 0;
}