#include <stdio.h>
#include <stdlib.h>

void mtx_mult(double *m1, double *m2, double *m3, int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int pos = i * n + j;
			m3[pos] = 0;
			for(int k = 0; k < n; k++) {
				m3[pos] += m1[i*n + k] * m2[k*n + j];
			}
		}
	}
}

int main(int argc, char *argv[]) {
    int n;
	
	sscanf(argv[1], "%d", &n);
	
	double *m1 = (double*) malloc(n*n*sizeof(double*));
	double *m2 = (double*) malloc(n*n*sizeof(double*));
	double *m3 = (double*) malloc(n*n*sizeof(double*));
	
	for(int i = 0; i < n*n; i++){
		m1[i] = 1.0;
		m2[i] = 1.0;
	}
	
	mtx_mult(m1, m2, m3, n);
	
//	for(int i = 0; i < n; i++) {
//		for(int j = 0; j < n; j++) {
//			int pos = i * n + j;
//			printf("%.2lf ", m3[pos]);
//		}
//		printf("\n");
//	}
	
    return 0;
}


