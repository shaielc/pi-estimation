/*
**  PROGRAM: Mandelbrot area
**
**  PURPOSE: Program to compute the area of a  Mandelbrot set.
**           Correct answer should be around 1.510659.
**           WARNING: this program may contain errors
**
**  USAGE:   Program runs without input ... just run the executable
**            
**  HISTORY: Written:  (Mark Bull, August 2011).
**           Changed "comples" to "d_comples" to avoid collsion with 
**           math.h complex type (Tim Mattson, September 2011)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <stdbool.h>

# define NPOINTS 5000
# define MAXITER 5000
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

struct d_complex {
   double r;
   double i;
};

bool testpoint(struct d_complex* c);

int main() {
    
   int threads[] = {1,2,4,8,16,24};
   double area, error, eps = 1.0e-5;
   double start_time, run_time;

   // Test varying number of threads: 1,2,4,8,16 and 24 threads
   for (int k=0; k< NELEMS(threads); k++) {
        int numoutside = 0;
        int num_of_threads = threads[k];
        omp_set_num_threads(num_of_threads);
        start_time = omp_get_wtime();
       
       // Loop over grid of points in the complex plane which contains 
       // the Mandelbrot set, test each point to see whether it is 
       // inside or outside the set
       #pragma omp parallel
       {
         int thread_id = omp_get_thread_num();
         struct d_complex c;
         for (int i = 0; i < NPOINTS; i++) {
            for (int j = thread_id; j < NPOINTS; j+=num_of_threads) {
               c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
               c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;
               bool out_of_set = !testpoint(&c);
               if (fabs(c.i - 0.591933) < 0.000001){}
               
               #pragma omp atomic
               numoutside += out_of_set;
            }
         }
       }
       
       run_time = omp_get_wtime() - start_time;
       // Calculate area of set and error estimate and output the results
       area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) 
             / (double)(NPOINTS * NPOINTS);
       error = area / (double)NPOINTS;
       printf("Area of Mandlebrot set = %12.8f +/- %12.8f, count:%d\n",area,error, numoutside);
       printf("\n atomic implementation - time: %f seconds, with %d threads\n",run_time, num_of_threads);
   }
    
   printf("(Correct answer should be around 1.506)\n");
}

bool testpoint(struct d_complex* cp) {

   // Does the iteration z=z*z+c, until |z| > 2 when point is known to 
   // be outside set. If loop count reaches MAXITER, point is considered 
   // to be inside the set.

   int iter;
   double temp;
   struct d_complex z = (*cp);
   
   for (iter = 0; iter < MAXITER; iter++) {
      temp = (z.r * z.r) - (z.i * z.i) + cp->r;
      z.i = z.r * z.i * 2 + cp->i;
      z.r = temp;
      if ((z.r * z.r + z.i * z.i) > 4.0) {
         return false;
      }
   }
   return true;
}


