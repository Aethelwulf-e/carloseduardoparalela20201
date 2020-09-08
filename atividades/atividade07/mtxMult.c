#include <stdio.h>
#include <stdlib.h>

void **mtx_mult(double **m1, double **m2, double **m3, int n) {
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) {
			for(int k = 0; k < n; k++){
				m3[i][j] = m3[i][j] + m1[i][k] * m2[k][j];
			}
		}
	}
}

int main(int argc, char *argv[]) {
    int n;
    
	sscanf(argv[1], "%d", &n);
	
	double **m1 = (double**) malloc(n * sizeof(double*));
	double **m2 = (double**) malloc(n * sizeof(double*));
	double **m3 = (double**) malloc(n * sizeof(double*));
	
	for(int i = 0; i < n; i++){
		m1[i] = (double*) malloc(n * sizeof(double));
		m2[i] = (double*) malloc(n * sizeof(double));
		m3[i] = (double*) malloc(n * sizeof(double));
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) {
			m1[i][j] = 1.0;
			m2[i][j] = 1.0;
			m3[i][j] = 0;
		}
	}
	
	mtx_mult(m1, m2, m3, n);
	
//	for(int i = 0; i < n; i++) {
//		for(int j = 0; j < n; j++) {
//			printf("%.2lf ", m3[i][j]);
//		}
//		printf("\n");
//	}
	
    return 0;
}

