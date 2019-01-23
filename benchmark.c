#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 16 //Matrix Dimension 3 < N < 2048
#define CPU_CLK 1.593E9  //3.43E9 for Dell i7-6600, 2.8E9 for i5 Surface Pro, 3.48E9 for HP i7-7700; 2.394455e9 for Xeon  for Sun 1.593E9
#define OPTIMIZATION "-o3"

int main(void)
{

    printf("Intel Xeon processor: 2.40E+09 Hz\n"); 
    printf("Sun Sparc processor: 1.59E+09 Hz\n\n");
    printf("Matrix Dimension: %d x %d\n", N, N); 
    printf("Compiler optimization setting: %s\n", OPTIMIZATION);

    double *a[N], *b[N], *c[N];
    int h, i, j, k, ij, l;
    long OUTER = 10000000/N;
    long LOOP;

    time_t start_time, end_time;

	double elapsedTime;
	double time_per_matrix;
	double time_per_element;
	double time_per_op;
	//double cycles_per_op;
	//double ops_per_cycle;
	//double ops_per_second;

    long result_elements = N*N;
    long ops_per_element = N*2-1;

    long ops_per_alg = ops_per_element * result_elements;
    long total_ops = ops_per_alg * OUTER;
    double FLOPS;


    printf("# of Accuracy Loops: %li\n", OUTER);
    printf("Algorithmically evaluated operations: %ld\n", total_ops);
    printf("Total Operations: %li\n", OUTER*N*N*(N*2-1));



    srand(time(NULL)); //Seed random number generator


    for( h = 0; h < N; h++){
        a[h] = (double*)malloc(N * sizeof(double));
        b[h] = (double*)malloc(N * sizeof(double));
        c[h] = (double*)malloc(N * sizeof(double));
    }


    // fill a and b matrices with random numbers ranging 1 - 100
    for (ij = 0 ; ij < N*N ; ij++ )
    {
         i = ij / N ;
         j = ij % N ;
         a[i][j] = (double)1 + rand() % 100;
         b[i][j] = (double)1 + rand() % 100;
      //  printf("a[%d][%d] = %f\n", i, j, a[i][j]);
        //printf("b[%d][%d] = %f\n", i, j, b[i][j]);
    }


	printf("Computation begins now...\n\n");

	start_time = (double)time(0);
    for(LOOP = 0 ; LOOP < OUTER; LOOP++){
        for (ij = 0 ; ij < N*N ; ij++ )
        {
            i = ij / N ;
            j = j % N ;

            c[i][j] = 0 ;
            for (  k = 0 ; k < N ; k++ )
            {
                c[i][j] += a[i][k] * b[k][j] ;
            }
      //  printf("c[%d][%d] = %f\n", i, j, c[i][j]);
        }
    }
	end_time = (double)time(0);

    for( l = 0; l < N; l++){
        free(a[l]);
        free(b[l]);
        free(c[l]);
    }

	printf("Finished !\n\n");


	elapsedTime = ((end_time - start_time)); //elapsed time in double precision format
	time_per_matrix = elapsedTime / OUTER;
	time_per_element = time_per_matrix / result_elements;
    time_per_op = time_per_element / ops_per_element;
    FLOPS = ops_per_element /time_per_element;

    double ops_sec = 1/time_per_op;


	printf("Total measured execution time was: %0.4e seconds \n\n", elapsedTime);
	printf("Evaluated execution time for: %d x %d matrix: %0.4e  seconds\n\n", N, N, time_per_matrix);
	printf("Evaluated execution time per matrix element: %0.4e seconds\n\n", time_per_element);
	printf("Evaluated execution time per arithmetic operation: %0.4e seconds\n\n", time_per_op);
	printf("Evaluated number of operations per clock cycle is  %0.2f  operations per CPU clock cycles\n\n", FLOPS/CPU_CLK);
	printf("Evaluated number of clock cycles per operation is  %0.2f  CPU clock cycles per operation\n\n", CPU_CLK/FLOPS);
	printf("Evaluated operations per second:  %0.2f  \n\n", ops_sec);


    puts("Press <enter> to quit:");
    getchar();
    return 0;


}