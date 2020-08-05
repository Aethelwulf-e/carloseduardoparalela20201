#include <stdio.h>

#define SIZE 5000

float m[2][SIZE][SIZE];
int n;
int k;
int cores_number;
int current = 0;

void load() {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			m[0][i][j] = i * j;
		}
	}
}

void update() {
	current = !current;
	#pragma omp parallel for num_threads(cores_number)
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			m[current][i][j] = (m[!current][i+1][j] + m[!current][i][j+1] + m[!current][i-1][j] + m[!current][i][j-1]) * 0.25;
		}
	}
}

int main(int argc , char *argv[]) {
	sscanf (argv[1], "%d", &n);
	sscanf (argv[2], "%d", &k);
	sscanf (argv[3], "%d", &cores_number);
	
	load();
	
	for(int i = 0; i < k; i++)
		update();
	
	return 0;
}
