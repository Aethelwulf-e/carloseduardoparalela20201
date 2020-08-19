#include <stdio.h>

// Correção: receber por linha de comando.
#define SIZE 5000

// Correção: deu certo por sorte, isto não é alocação dinâmica em C.
double a[SIZE][SIZE];
double b[SIZE][SIZE];
double c[SIZE][SIZE];
int n;

void mtxMul() {
   for (int i = 0; i < n; i++)
       for (int j = 0; j < n; j++) {
           c[i][j] = 0.0;
           for (int k = 0; k < n; k++)
               c[i][j] = c[i][j] + a[i][k] * b[k][j];
       }
}

void load() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			a[i][j] = 1.0;
			b[i][j] = 1.0;
		}
	}
}

int main(int argc, char *argv[]) {
	sscanf(argv[1], "%d", &n);
	load();
	mtxMul();
	return 0;
}
