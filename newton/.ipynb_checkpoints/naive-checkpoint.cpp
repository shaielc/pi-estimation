#include <math.h>
#include <cstdio>

double pi_ne(unsigned int nb_iter)
{
    double sum = 1;      // The resulting sum
    double a = 1;        // The term to add at each iteration
    double n = 1, d = 3; // The n/d term to multiply to a at each iteration

    for(std::size_t i = 0; i < nb_iter; ++i)
    {
        a *= n/d;       // Update a
        sum += a;       // Update the sum

        // Update the n/d term
        ++n;
        d += 2;
    }

    return 2*sum;
}

int main() {

    for ( int i = 1; i<24; i++) {
        double pi_est = pi_ne(i);
        printf("i:%d;import:%f;est:%f;err:%.3e\n", i, M_PI, pi_est, abs(pi_est - M_PI));
    }
    
}