#include <stdio.h>
#include <omp.h>

int main (int argc , char *argv[]) {
    int max;
    int c;
    
	sscanf (argv[1], "%d", &max);
    sscanf (argv[2], "%d", &c);
    
    int ts = omp_get_max_threads();
	int sums[ts];
	
	#pragma omp parallel
	{
		int t = omp_get_thread_num();
		sums[t] = 0;
		for(int i = c * t + 1; i <= max; i += ts * c)
			for(int j = 0; j < c; j++)
				if(i + j <= max)
					sums[t] += i + j;
	}
	
    int sum = 0;
    for (int t = 0; t < ts; t++) sum = sum + sums[t];
    printf ("%d\n", sum);
    return 0;
}
