#include <stdio.h>
#include <stdlib.h>

double *mtxMul(double *c, double *a, double *b, int n) {
   for (int i = 0; i < n; i++)
       for (int j = 0; j < n; j++) {
               c[i][j] = 0.0;
               for (int k = 0; k < n; k++)
                       c[i][j] = c[i][j] + a[i][k] * b[k][j];
       }
   return c;
}

int main(int argc, char **argv) {

   return 0;
}
