#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double random(double a, double b) {
	double rValue = (double)(rand()/(double)RAND_MAX*(b - a)) + a;
	return rValue;
}

double** normalization() {

	int i = 0;

	double* max = calloc(2, sizeof(*max));
	double** tab = calloc(1000, sizeof(*tab));
	double x = 0, y = 0, outputV = 0;


	scanf("%lf, %lf, %lf", &x, &y, &outputV);

	tab[i] = calloc(3, sizeof(*tab[i]));
	tab[i][0] = x;
	tab[i][1] = y;
	tab[i][2] = outputV;

	while (outputV != 0) {
		i++;

		scanf("%lf, %lf, %lf", &x, &y, &outputV);

		tab[i] = calloc(3, sizeof(*tab[i]));
		tab[i][0] = x;
		tab[i][1] = y;
		tab[i][2] = outputV;
	}



	max[0] = tab[0][0];
	max[1] = tab[0][1];

	for (int j = 1; j < i; j++) {
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


	while (scanf("%lf, %lf", &x, &y) != EOF) {
		i++;

		tab[i] = calloc(2, sizeof(*tab[i]));
		tab[i][0] = x;
		tab[i][1] = y;
	}

	for (int k = 0; k < i + 1; k++) {
		tab[k][0] = tab[k][0]/max[0];
		tab[k][1] = tab[k][1]/max[1];
	}

	return tab;
}

int main() {

	int j = 0;

	double out = 0, boundary = 0;
	double eta = 0.001;

	double** tab;
	double weight[3];
	double* max = calloc(2, sizeof(*max));


	tab = normalization();


	weight[0] = random(-0.001, 0.001);
	weight[1] = random(-0.001, 0.001);
	weight[2] = random(-0.001, 0.001);

	while (tab[j][2] != 0) {
		out = tanh(tab[j][0]*weight[0] + tab[j][1]*weight[1] + weight[2]);
		boundary = -weight[0]/weight[1]*tab[j][0] - weight[2]/weight[1];

		while ((tab[j][2] == -1 && tab[j][1] > boundary) || (tab[j][2] == 1 && tab[j][1] < boundary)) {
			weight[0] += 2*eta*(tab[j][2] - out)*(1 - pow(out, 2))*tab[j][0];
			weight[1] += 2*eta*(tab[j][2] - out)*(1 - pow(out, 2))*tab[j][1];
			weight[2] += 2*eta*(tab[j][2] - out)*(1 - pow(out, 2));

			out = tanh(tab[j][0]*weight[0] + tab[j][1]*weight[1] + weight[2]);
			boundary = -weight[0]/weight[1]*tab[j][0] - weight[2]/weight[1];
		}
		j++;
	}

	j++;

	while (tab[j] != NULL) {
		out = tanh(tab[j][0]*weight[0] + tab[j][1]*weight[1] + weight[2]);
		boundary = -weight[0]/weight[1]*tab[j][0] - weight[2]/weight[1];
 
		if (tab[j][1] > boundary) {
			printf("+1\n");
		}
		else {
			printf("-1\n");
		}
		j++;
	}

	return 0;
}