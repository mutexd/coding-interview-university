/*
 *  We'll calculate sqrt() by using Newton's method
 *
 */

#include <stdio.h>
#include <math.h>

/*  
 *
 */
double mySqrt(int num)
{
    double x0 = 0;
    double x_next = num / 2;
    while (fabs(x_next - x0) > 10e-6) {
        x0 = x_next;
        x_next = x0 - (x0*x0 - num) / (2*x0);
    }
    return x_next; 
}

int main(int argc, char **argv)
{
    printf("sqrt(100) = %g\n", mySqrt(100));
}
