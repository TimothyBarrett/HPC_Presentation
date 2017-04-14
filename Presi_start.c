
#include <stdio.h>
#include <complex.h>
#include "linear_algebra.h"
static int
calc_pixel(complex double c)
{
  const int max_iter = 256;
  complex double z = 0.;
  int cnt;

  for (cnt = 0; cnt < max_iter; cnt++) {
    z = z*z + c;
    if (cabs(z) >= 2.) {
      break;
    }
  }
  return cnt;
}

#define MX 2000
#define MY 2000

int
main(int argc, char **argv)
{
  const complex double z0 = -2. - 1. * I;
  const complex double z1 =  1. + 1. * I;

  // data here is made "static" for the following reason: It's a fairly large
  // array. Without the "static", it'll be put on the stack, which
  // isn't really well-suited for large amounts of data -- in
  // particular, on MacOS it's quite possible to run out of stack space,
  // which kills the program. Using "static", the memory for data is
  // "statically allocated", which doesn't have such a limitation.
  static int data[MY][MX];

  double dx = creal(z1 - z0) / (MX - 1);
  double dy = cimag(z1 - z0) / (MY - 1);
  double start=WTime();
  #pragma omp parallel for collapse(2)
  for (int iy = 0; iy < MY; iy++) {
    for (int ix = 0; ix < MX; ix++) {
      complex double c = z0 + dx * ix + dy * iy * I;
      data[iy][ix] = calc_pixel(c);
    }
  }
  /*
  for (int iy = 0; iy < MY/2; iy++) {
    for (int ix = 0; ix < MX/2; ix++) {
  printf("%d \n", data[ix][iy]);
    }
  }*/
  double tot_time=WTime()-start;
  printf("Parallel loop took %g seconds\n", tot_time);
  
  FILE *file = fopen("mandelbrot.asc", "w");
  for (int iy = 0; iy < MY; iy++) {
    for (int ix = 0; ix < MX; ix++) {
      complex double c = z0 + dx * ix + dy * iy * I;
      fprintf(file, "%g %g %d\n", creal(c), cimag(c), data[iy][ix]);
    }
    fprintf(file, "\n");
  }
  fclose(file);
}
