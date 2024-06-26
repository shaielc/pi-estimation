/*
**  PROGRAM: Matrix Multiply
**
**  PURPOSE: This is a simple matrix multiply program. 
**           It will compute the product
**
**                C  = A * B
**
**           A and B are set to constant matrices so we
**           can make a quick test of the multiplication.
**  HISTORY: Written by Tim Mattson
*/
#include <malloc.h>
#include <stdio.h>
#include <omp.h>

#define ORDER 50
#define AVAL 3.0
#define BVAL 5.0
#define TOL  0.001

int main(int argc, char **argv)
{
    int Ndim, Pdim, Mdim;   /* A[N][P], B[P][M], C[N][M] */
    double *A, *B, *C, cval, err, errsq;
    double start_time, run_time;
    
    Ndim = ORDER;
    Pdim = ORDER*100;
    Mdim = ORDER*100;

    A = (double *)malloc(Ndim*Pdim*sizeof(double));
    B = (double *)malloc(Pdim*Mdim*sizeof(double));
    C = (double *)malloc(Ndim*Mdim*sizeof(double));

    /* Initialize matrices */

    for (int i=0; i<Ndim; i++)
        for (int j=0; j<Pdim; j++)
            *(A+(i*Pdim+j)) = AVAL;

    for (int i=0; i<Pdim; i++)
        for (int j=0; j<Mdim; j++)
            *(B+(i*Pdim+j)) = BVAL;

    for (int i=0; i<Ndim; i++)
        for (int j=0; j<Mdim; j++)
            *(C+(i*Ndim+j)) = 0.0;

    start_time = omp_get_wtime();

    /* Do the matrix product */
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < Pdim; i++) {
        for (int j = i+1; j < Mdim; j++) {
            B[j * Mdim + i] += B[i * Mdim + j];
            B[i * Mdim + j] = B[j * Mdim + i] - B[i * Mdim + j];
            B[j * Mdim + i] -= B[i * Mdim + j];
        }
    }
    
    #define BLOCK_SIZE 256
    #pragma omp parallel for collapse(3) schedule(dynamic) firstprivate(A, B)
    for (int jj=0; jj < Mdim; jj += BLOCK_SIZE)
        for (int kk=0; kk < Pdim; kk += BLOCK_SIZE)
            for (int i=0; i<Ndim; i++){
                for (int j=jj;  j < (jj + BLOCK_SIZE) && j < Mdim ; j++){
                    double sum = 0.0;
                    for(int k=kk; k < (kk + BLOCK_SIZE) && k < Pdim ;k++){
                        /* C(i,j) = sum(over k) A(i,k) * B(k,j) */
                         sum += *(A+(i*Pdim+k)) *  *(B+(j*Pdim+k));
                    }
                    #pragma omp atomic
                    *(C+(i*Mdim+j)) += sum;
                    
                }
            }

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < Pdim; i++) {
        for (int j = i+1; j < Mdim; j++) {
            B[j * Mdim + i] += B[i * Mdim + j];
            B[i * Mdim + j] = B[j * Mdim + i] - B[i * Mdim + j];
            B[j * Mdim + i] -= B[i * Mdim + j];
        }
    }
   
    run_time = omp_get_wtime() - start_time;
 
    printf(" Order %d multiplication in %f seconds \n", ORDER, run_time);
           
    /* Check the answer */
           
    cval = Pdim * AVAL * BVAL;
    errsq = 0.0;
    for (int i=0; i<Ndim; i++){
        for (int j=0; j<Mdim; j++){
            err = *(C+i*Mdim+j) - cval;
            errsq += err * err;
        }
    }

    if (errsq > TOL) 
        printf("\n Errors in multiplication: %f",errsq);
    else
        printf("\n Hey, it worked");

    printf("\n all done \n");
}
