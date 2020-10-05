// Nota 0,5. 
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int n;
	int rank, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
    
	double init = MPI_Wtime();
	
	sscanf(argv[1], "%d", &n);
	
	double *m1 = (double*) malloc(n*n*sizeof(double));
	double *m2 = (double*) malloc(n*n*sizeof(double));
	double *m3 = (double*) malloc(n*n*sizeof(double));
	
	if(rank == 0) {
		for(int i = 0; i < n*n; i++) {
			m1[i] = 1.0;
			m2[i] = 1.0;
		}	
	}

	// Não era para fazer broadcast das duas.	
	MPI_Bcast(m1, n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	MPI_Bcast(m2, n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	int chunk_size = n*(n/size);
	int pos = 0;
	double *m3_local = (double*) malloc(chunk_size*sizeof(double));
	
	for(int i = rank*(n/size); i < (rank+1)*(n/size); i++) {
		for(int j = 0; j < n; j++) {
			m3_local[pos] = 0;
			for(int k = 0; k < n; k++) {
				m3_local[pos] += m1[i*n + k] * m2[k*n + j];
			}
			pos++;
		}
	}
	
	MPI_Gather(m3_local, chunk_size, MPI_DOUBLE, m3, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	
	if(rank == 0) {
		double end = MPI_Wtime();
		printf("Tempo decorrido: %.12f\n", end - init);
	}
	
//	for(int i = 0; i < n; i++) {
//		for(int j = 0; j < n; j++) {
//			int pos = i * n + j;
//			printf("%.2lf ", m3[pos]);
//		}
//		printf("\n");
//	}
	
	MPI_Finalize();
	
   	return 0;
}


