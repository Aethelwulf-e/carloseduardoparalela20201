#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

int primo(int n) {
    int i;
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (!(n % 2)) return 0;
    for (i = 3; i < (sqrt(n)+1); i+=2) {
        if (n%i == 0) return 0;
    }
    return 1;
}

int get_random_number(int l, int size, int seed) {
	return l + (100003*seed)%(size);
}

int main(int argc, char *argv[]) {
    int rank, size;
    int n = 1000000;
    
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int chunk_size = 10000;
    
    if(rank == 0) {
	int *is_prime = (int*)malloc(n * sizeof(int));
		
	for(int i = 0; i < n/chunk_size; i++) {
		int snd = i * chunk_size;
			
		MPI_Send(&snd, 1, MPI_INT, get_random_number(1, size-1, i), 0, MPI_COMM_WORLD);
	}
		
	for(int i = 0; i < n/chunk_size; i++) {
		int source_rank = get_random_number(1, size-1, i);
		MPI_Recv(is_prime + (i * chunk_size), chunk_size, MPI_INT, source_rank, 0, MPI_COMM_WORLD, &status);
	}
		
	for(int i = 0; i < n; i++) {
		if(is_prime[i]) {
			printf("%d, ", i);
		}
	}
	printf("\n");
		
	for(int i = 1; i < size; i++) {
		int snd = -1;
		MPI_Send(&snd, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	}
		
    } else {
	while(1) {
		int inicio;
		MPI_Recv(&inicio, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			
		if(inicio == -1) {
			break;
		}
			
		int *is_prime_local = (int*)malloc(chunk_size * sizeof(int));
		
		for(int i = 0; i < chunk_size; i++) {
			is_prime_local[i] = primo(i+inicio);
		}
		
		MPI_Send(is_prime_local, chunk_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
    }
    
    MPI_Finalize();
    return 0;
}
