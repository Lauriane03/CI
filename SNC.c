#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double random(double a, double b) {
	double rValue = (double)(rand()/(double)RAND_MAX*(b - a)) + a;
	return rValue;
}

int snc() {

	int i = 0;
	double max[2];

	double x, y;
	double outputV = 0;

	double out = 0;
	double eta = 0.001;
	double net = 0;
	double boundary = 0;

	double (*tab)[3] = calloc(1000, sizeof(*tab));

	double weight[3];

	weight[0] = random(-0.001, 0.001);
	weight[1] = random(-0.001, 0.001);
	weight[2] = -1;

	scanf("%lf, %lf, %lf", &x, &y, &outputV);
	tab[i][0] = x;
	tab[i][1] = y;
	tab[i][2] = outputV;

	while (x != 0 && y != 0 && outputV != 0) {
		i++;
		scanf("%lf, %lf, %lf", &x, &y, &outputV);
		tab[i][0] = x;
		tab[i][1] = y;
		tab[i][2] = outputV;
	}

	for (int k = 0; k < i; k++) {
		if (sqrt(pow(tab[k][0], 2) + pow(tab[k][1], 2)) > sqrt(pow(tab[k + 1][0], 2) + pow(tab[k + 1][1], 2))) {
			max[0] = tab[k][0];
			max[1] = tab[k][1];
		}
		else {
			max[0] = tab[k + 1][0];
			max[1] = tab[k + 1][1];
		}
	}

	for (int j = 0; j < i; j++) {
		tab[j][0] = tab[j][0]/max[0];
		tab[j][1] = tab[j][1]/max[1];
	}

	for (int j = 0; j < i; j++) {
		net = tab[j][0]*weight[0] + tab[j][1]*weight[1];
		out = tanh(net - weight[2]);
		boundary = -weight[0]/weight[1]*tab[j][0] - weight[2]/weight[1];

		if (tab[j][2] == -1 && tab[j][1] > boundary) {
			while (tab[j][1] > boundary) {
				weight[0] += -2*eta*(tab[j][2] - out)*(1 - tanh(net - weight[2]))*tab[j][0];
				weight[1] += -2*eta*(tab[j][2] - out)*(1 - tanh(net - weight[2]))*tab[j][1];
				weight[2] += -2*eta*(tab[j][2] - out);

				net = tab[j][0]*weight[0] + tab[j][1]*weight[1];
				out = tanh(net - weight[2]);
				boundary = -weight[0]/weight[1]*tab[j][0] - weight[2]/weight[1];
			}
		}
		else if (tab[j][2] == 1 && tab[j][1] < boundary) {
			while (tab[j][1] < boundary) {
				weight[0] += -2*eta*(tab[j][2] - out)*(1 - tanh(net - weight[2]))*tab[j][0];
				weight[1] += -2*eta*(tab[j][2] - out)*(1 - tanh(net - weight[2]))*tab[j][1];
				weight[2] += -2*eta*(tab[j][2] - out);

				net = tab[j][0]*weight[0] + tab[j][1]*weight[1];
				out = tanh(net - weight[2]);
				boundary = -weight[0]/weight[1]*tab[j][0] - weight[2]/weight[1];		
			}
		}
	}

	while (scanf("%lf, %lf", &x, &y) != EOF) {
		net = x*weight[0] + y*weight[1];
		out = tanh(net - weight[2]);
		boundary = -weight[0]/weight[1]*x - weight[2]/weight[1];

		if (y > boundary) {
			printf("+1\n");
		}
		else {
			printf("-1\n");
		}
	}

	return 0;
}