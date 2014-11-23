#include <stdio.h>
#include "utils.h"
#include "QRdecomposition.h"


int main(int argc, char* argv[]) {
  double A[nmax][mmax];
  double b[mmax];
  double sigma[mmax];
  double max;
  
  int permutacao[mmax];
  int n, m;
  int i, j;
  int stop;
  int index;

  //Leitura da matriz
  use(argc);
  input(argc, argv, A, b, &n, &m);


  //Inicio da decomposicao QR
  max = sigmaArray(A, sigma, n, m);
  stop = permuta(A, sigma, permutacao, index, n, m);

  //Iteracao da decomposicao
  for (i = 0; stop != 1; i++) {
    
    
  }

  return 0;
}
