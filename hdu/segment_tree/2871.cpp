// �Ա�hdu 1540, pku 3667

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

#define left_mode index * 2, left, mid
#define right_mode index * 2 + 1, mid + 1, right

void pushdown(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int count) {
	if (vi_lazy[index] != -1) {
		int left = index * 2;
		int right = left + 1;
		vi_lazy[left] = vi_lazy[right] = vi_lazy[index];
		vi_seg[left] = vi_seg_left[left] = vi_seg_right[left] = vi_lazy[index] ? 0 : count - count / 2; // vi_lazy[index]Ϊ1��ʾ��ռ���ˣ�vi_lazy[index]Ϊ0��ʾδ��ռ�á�
		vi_seg[right] = vi_seg_left[right] = vi_seg_right[right] = vi_lazy[index] ? 0 : count / 2;
		vi_lazy[index] = -1; // ע��������뵱Ȼ��дΪ��ֵΪ0��������������ˣ�����
	}
}

void pushup(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int count) {
	int left = index * 2; // �����left��right��ʾ�����ӽڵ���±꣬��update�������left��right��ʾ��Ӧ��index�ڵ��Ӧ����������±߽硣ע��������𣡣������Ǳ������������ã�����
	int right = left + 1;
	vi_seg_left[index] = vi_seg_left[left];
	if (vi_seg_left[index] == count - count / 2) {
		vi_seg_left[index] += vi_seg_left[right];
	}
	vi_seg_right[index] = vi_seg_right[right];
	if (vi_seg_right[index] == count / 2) {
		vi_seg_right[index] += vi_seg_right[left];
	}
	vi_seg[index] = max(max(vi_seg[left], vi_seg[right]), vi_seg_left[right] + vi_seg_right[left]);
}

// �����Ǹ���һ���ڴ���״̬��������L��R�������߽硣
void update(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int left, int right, int L, int R, int b) {
	if (L <= left && right <= R) {
		vi_seg[index] = vi_seg_left[index] = vi_seg_right[index] = b ? 0 : right - left + 1; // ע���������
		vi_lazy[index] = b; // ע���������
		return;
	}
	pushdown(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, index, right - left + 1);
	int mid = (left + right) / 2;
	if (L <= mid) {
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode, L, R, b); // ע�⣺�������L��R����û�б�ΪL��mid��
	}
	if (R > mid) {
		update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode, L, R, b); // ע�⣺�������L��R����û�б�Ϊmid + 1��R��
	}
	pushup(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, index, right - left + 1);
}

// �����ǲ�ѯһ�ο��õĿռ䣬����ֻ��һ����ʾ���ȵ�ֵ��û�б߽硣
int query(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int left, int right, int count) {
	if (vi_seg[index] < count) {
		return 0;
	}
	if (left == right) { // �����һ��if����������if�����ҵ������㳤�ȵĿ��ÿռ����ʼ�±ꡣ����������������߶������±���в��ҡ�
		return left;
	}
	pushdown(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, index, right - left + 1);
	int mid = (left + right) / 2;
	// ����Ĳ���˳���pku 3667һ�¡�
	if (vi_seg[index * 2] >= count) {
		return query(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode, count);
	}
	else if (vi_seg_left[index * 2 + 1] + vi_seg_right[index * 2] >= count) {
		return mid - vi_seg_right[index * 2] + 1;
	}
	else {
		return query(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode, count);
	}
}

void build(vector<int>& vi_seg, vector<int>& vi_seg_left, vector<int>& vi_seg_right, vector<int>& vi_lazy, int index, int left, int right) {
	vi_seg[index] = vi_seg_left[index] = vi_seg_right[index] = right - left + 1;
	vi_lazy[index] = -1;
	if (left == right) return;
	int mid = (left + right) / 2;
	build(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, left_mode);
	build(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, right_mode);
}


bool pair_cmp(const pair<int, int>& a, const pair<int, int>& b) {
	return a.second < b.first;
}

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2 && n && m) {
		vector<int> vi_seg(n * 4);
		vector<int> vi_seg_left(vi_seg);
		vector<int> vi_seg_right(vi_seg);
		vector<int> vi_lazy(vi_seg);
		vector<pair<int, int> > vpii;
		vpii.push_back(make_pair(0, 0));
		build(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n);
		while (m--) {
			char ctp[6];
			int itp;
			scanf("%s", ctp);
			if (ctp[0] == 'N') {
				scanf("%d", &itp);
				if (vi_seg[1] < itp) {
					printf("Reject New\n");
					continue;
				}
				int iindextp = query(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, itp);
				if (iindextp >= 1) {
					update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, iindextp, iindextp + itp - 1, 1);
					int iindextp2 = lower_bound(vpii.begin(), vpii.end(), make_pair(iindextp, iindextp), pair_cmp) - vpii.begin();
					vpii.insert(vpii.begin() + iindextp2, make_pair(iindextp, iindextp + itp - 1));
					printf("New at %d\n", iindextp);
				}
				else {
					printf("Reject New\n");
					continue;
				}
			}
			else if (ctp[0] == 'F') {
				scanf("%d", &itp);
				/*
				// ����������İ汾����
				vector<pair<int, int> >::iterator vpiiittp = lower_bound(vpii.begin(), vpii.end(), make_pair(itp, itp), pair_cmp);
				if (vpiiittp != vpii.end() && (*vpiiittp).first == itp || (*vpiiittp).second == itp) {
					printf("Free from %d to %d\n", (*vpiiittp).first, (*vpiiittp).second);
					update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, (*vpiiittp).first, (*vpiiittp).second, 0);
					vpii.erase(vpiiittp);
				}
				*/
				int iindextp = lower_bound(vpii.begin(), vpii.end(), make_pair(itp, itp), pair_cmp) - vpii.begin();
				if (iindextp < vpii.size()) {
					if (vpii[iindextp].first <= itp && vpii[iindextp].second >= itp) {
						printf("Free from %d to %d\n", vpii[iindextp].first, vpii[iindextp].second);
						update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, vpii[iindextp].first, vpii[iindextp].second, 0);
						vpii.erase(vpii.begin() + iindextp);
						continue;
					}
				}
				printf("Reject Free\n");
			}
			else if (ctp[0] == 'G') {
				scanf("%d", &itp);
				if (itp >= vpii.size()) {
					printf("Reject Get\n");
				}
				else {
					printf("Get at %d\n", vpii[itp].first);
				}
			}
			else if (ctp[0] == 'R') {
				printf("Reset Now\n");
				update(vi_seg, vi_seg_left, vi_seg_right, vi_lazy, 1, 1, n, 1, n, 0);
				vpii.erase(vpii.begin() + 1, vpii.end());
			}
		}
		cout << endl;
	}
	return 0;
}