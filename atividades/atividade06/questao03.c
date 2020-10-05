// Nota 0,4. Tinha que enviar o valor por chamada coletiva.
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    float *arr1, *arr2;
	
    float v1;
    float v2;
    int n;
	
    sscanf(argv[1], "%f", &v1);
    sscanf(argv[2], "%f", &v2);
    sscanf(argv[3], "%d", &n);

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    double init = MPI_Wtime();
    
    if(rank == 0) {
	arr1 = (float*)malloc(n * sizeof(float));
	arr2 = (float*)malloc(n * sizeof(float));
		
	for(int i = 0; i < n; i++) {
		arr1[i] = v1;
		arr2[i] = v2;
	}		
    }
	
    int n_local = n / size;
	
    float *arr1_local = (float*)malloc(n_local * sizeof(float));
    float *arr2_local = (float*)malloc(n_local * sizeof(float));

    MPI_Scatter(arr1, n_local, MPI_FLOAT, arr1_local, n_local, MPI_FLOAT, 0, MPI_COMM_WORLD);
    MPI_Scatter(arr2, n_local, MPI_FLOAT, arr2_local, n_local, MPI_FLOAT, 0, MPI_COMM_WORLD);
	
    float sum_local = 0;
	
    for(int i = 0; i < n_local; i++) {
	sum_local += arr1_local[i] * arr2_local[i];
    }
	
    float sum_global = 0;
	
    MPI_Reduce(&sum_local, &sum_global, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	
    if(rank == 0) {
	printf("Resultado: %f\n", sum_global);
	double end = MPI_Wtime();
	printf("Tempo de demora: %lf\n", end - init);
    }
		
    MPI_Finalize();
	
    return 0;
}
