#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double random(double a, double b) {
	double rValue = (double)(rand()/(double)RAND_MAX*(b - a)) + a;
	return rValue;
}

double* normalization(double** tab, int l) {

	double* max = calloc(2, sizeof(*max));

	max[0] = tab[0][0];
	max[1] = tab[0][1];

	for (int j = 1; j < l; j++) {
		if (sqrt(pow(tab[j][0], 2) + pow(tab[j][1], 2)) > sqrt(pow(max[0], 2) + pow(max[1], 2))) {
			max[0] = tab[j][0];
			max[1] = tab[j][1];
		}
	}

	if (max[0] < 0) {
		max[0] = -max[0];
	}
	if (max[1] < 0) {
		max[1] = -max[1];
	}


	return max;
}

double** propag(double* tab, double** weight) {

	double** out = calloc(2, sizeof(*out));

	out[0] = calloc(2, sizeof(*out[0]));
	out[0][0] = tanh(tab[0]*weight[0][0] + weight[0][1]);
	out[0][1] = tanh(tab[0]*weight[0][2] + weight[0][3]);
	//out[0][2] = tanh(tab[0]*weight[0][4] + weight[0][5]);

	/*out[1] = calloc(3, sizeof(*out[1]));
	out[1][0] = tanh(out[0][0]*weight[1][0] + out[0][1]*weight[1][1] + out[0][2]*weight[1][2] + weight[1][3]);
	out[1][1] = tanh(out[0][0]*weight[1][4] + out[0][1]*weight[1][5] + out[0][2]*weight[1][6] + weight[1][7]);
	out[1][2] = tanh(out[0][0]*weight[1][8] + out[0][1]*weight[1][9] + out[0][2]*weight[1][10] + weight[1][11]);

	out[2] = calloc(2, sizeof(*out[2]));
	out[2][0] = tanh(out[1][0]*weight[2][0] + out[1][1]*weight[2][1] + out[1][2]*weight[2][2] + weight[2][3]);
	out[2][1] = tanh(out[1][0]*weight[2][4] + out[1][1]*weight[2][5] + out[1][2]*weight[2][6] + weight[2][7]);*/

	out[1] = calloc(1, sizeof(*out[1]));
	out[1][0] = out[0][0]*weight[1][0] + out[0][1]*weight[1][1] + weight[1][2];

	return out;
}


double** backpropag(double* tab, double** weight, double** out) {

	double** delta = calloc(2, sizeof(*delta));

	delta[1] = calloc(1, sizeof(*delta[1]));
	delta[1][0] = -2*(tab[1] - out[1][0]);

	delta[0] = calloc(2, sizeof(*delta[0]));
	delta[0][0] = (1 - pow(out[0][0], 2))*delta[1][0]*weight[1][0];
	delta[0][1] = (1 - pow(out[0][1], 2))*delta[1][0]*weight[1][1];
	
	/*delta[1] = calloc(2, sizeof(*delta[1]));
	delta[1][0] = (1 - pow(out[1][0], 2))*(delta[2][0]*weight[2][0] + delta[2][1]*weight[2][4]);
	delta[1][1] = (1 - pow(out[1][1], 2))*(delta[2][0]*weight[2][1] + delta[2][1]*weight[2][5]);
	delta[1][2] = (1 - pow(out[1][2], 2))*(delta[2][0]*weight[2][2] + delta[2][1]*weight[2][6]);

	delta[0] = calloc(3, sizeof(*delta[0]));		
	delta[0][0] = (1 - pow(out[0][0], 2))*(delta[1][0]*weight[1][0] + delta[1][1]*weight[1][4] + delta[1][2]*weight[1][8]);
	delta[0][1] = (1 - pow(out[0][1], 2))*(delta[1][0]*weight[1][1] + delta[1][1]*weight[1][5] + delta[1][2]*weight[1][9]);
	delta[0][2] = (1 - pow(out[0][2], 2))*(delta[1][0]*weight[1][2] + delta[1][1]*weight[1][6] + delta[1][2]*weight[1][10]);*/

	return delta;
}

double** weightUpdate(double* tab, double** weight, double** out, double** delta) {

	double eta = 0.1;

	weight[1][0] -= eta*delta[1][0]*out[0][0];
	weight[1][1] -= eta*delta[1][0]*out[0][1];
	weight[1][2] -= eta*delta[1][0];


	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
		weight[2][i + 4*j] -= eta*delta[2][j]*out[1][i];
		}
	}
	for (int j = 0; j < 2; j++) {
		weight[2][3 + 4*j] -= eta*delta[2][j];
	}


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			weight[1][i + 4*j] -= eta*delta[1][j]*out[0][i];
		}
	}
	for (int j = 0; j < 3; j++) {
		weight[1][3 + 4*j] -= eta*delta[1][j];
	}*/


	for (int j = 0; j < 2; j++) {
		weight[0][2*j] -= eta*delta[0][j]*tab[0];
	}
	for (int j = 0; j < 2; j++) {
		weight[0][2*j + 1] -= eta*delta[0][j];
	}


	return weight;
}

int main() {

	int j = 0, i = 0, m = 0;

	double** tab = calloc(1000, sizeof(*tab));
	double** weight = calloc(2, sizeof(*weight));

	double** out = calloc(2, sizeof(*out));
	double** delta = calloc(2, sizeof(*delta));

	double* max;
	double x = 0, y = 0;



	scanf("%lf, %lf", &x, &y);

	tab[i] = calloc(2, sizeof(*tab[i]));
	tab[i][0] = x;
	tab[i][1] = y;

	while (x != 0 && y != 0) {
		i++;

		scanf("%lf, %lf", &x, &y);

		tab[i] = calloc(2, sizeof(*tab[i]));
		tab[i][0] = x;
		tab[i][1] = y;
	}


	max = normalization(tab, i);


	for (int i = 0; i < 2; i++) {
		weight[i] = calloc(4, sizeof(**weight));
		for (int j = 0; j < 4; j++) {
			weight[i][j] = random(-0.1, 0.1);
		}
	}

	for (int k = 0; k < i; k ++) {
		tab[k][0] = tab[k][0]/max[0];
		tab[k][1] = tab[k][1]/max[1];
	}




	for (int k = 0; k < 700; k++) {
		while (tab[j][1] != 0) {		
			out = propag(tab[j], weight);

			for (int k = 0; k < 100; k ++) {
				if (pow(tab[j][1] - out[1][0], 2) > 0.000001) {
					delta = backpropag(tab[j], weight, out);
					weight = weightUpdate(tab[j], weight, out, delta);
					out = propag(tab[j], weight);
				}
			}
			j++;
		}
		m = j;
		j = 0;
	}

	m++;

	while (scanf("%lf", &x) != EOF) {
		tab[m] = calloc(1, sizeof(*tab[m]));
		tab[m][0] = x/max[0];
		out = propag(tab[m], weight);

		printf("%lf\n", out[1][0]*max[1]);

		m++;
	}

	return 0;
}