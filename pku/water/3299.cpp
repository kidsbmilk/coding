#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;

int main() {
	char ctp[2][2];
	while (scanf("%s", &ctp[0]) == 1) {
		if (ctp[0][0] == 'E') {
			break;
		}
		double dtp[2], t = -200.0, d = -200.0, h = -200.0;
		scanf("%lf %s %lf", &dtp[0], &ctp[1], &dtp[1]);
		for (int i = 0; i < 2; i++) {
			if (ctp[i][0] == 'T') {
				t = dtp[i];
			}
			else if (ctp[i][0] == 'D') {
				d = dtp[i];
			}
			else if (ctp[i][0] == 'H') {
				h = dtp[i];
			}
		}
		if (t < -100.0) {
			t = h - 0.5555 * (6.11 * exp(5417.7530 * (1/273.16 - 1/(d + 273.16))) - 10.0);
		}
		else if (d < -100.0) {
			d = 1 / (1 / 273.16 - log(((h - t) / 0.5555 + 10.0) / 6.11) / 5417.7530) - 273.16;
		}
		else if (h < -100.0) {
			h = t + 0.5555 * (6.11 * exp(5417.7530 * (1 / 273.16 - 1 / (d + 273.16))) - 10.0);
		}
		printf("T %.1lf D %.1lf H %.1lf\n", t, d, h);
	}
	return 0;
}