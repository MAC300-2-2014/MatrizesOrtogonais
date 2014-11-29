#include <stdio.h>
#include "utils.h"
#include "QRdecomposition.h"

int main(int argc, char* argv[]) {
  double A[nmax][mmax], b[nmax];
  double sigma[mmax], u[mmax];
  double max, gama;

  int permutacao[mmax];
  int m, n;
  int rank;
  int stop;

 
  /*Leitura da matriz*/
  use(argc);
  input(argc, argv, A, b, &n, &m);

  printMAT(A, n, m);
  printVET(b, n);


  /*Inicio da decomposicao QR*/
  max = sigmaArray(A, sigma, n, m);


  /*Iteracao da decomposicao*/
  for (rank = 0; rank < m ; rank++) {
    stop = permuta(A, sigma, permutacao, rank, n, m);    

    printMAT(A, n , m);

    if (stop == TRUE)      break;

    gama = calculaUSigmaGama(A, sigma, u, max, rank, n, m);
    produtoQA(A, b, u, gama, rank, n, m);
    sigmaRecalc(A, sigma, rank, n, m);
  }

  solution(A, b, permutacao, max, rank, n, m);

  return 0;
}
