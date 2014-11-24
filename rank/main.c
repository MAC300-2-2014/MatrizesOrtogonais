#include <stdio.h>
#include "utils.h"
#include "QRdecomposition.h"


int main(int argc, char* argv[]) {
  double A[nmax][mmax];
  double b[mmax];
  double sigma[mmax];
  double max;
  double gama;
  
  int permutacao[mmax];
  int n, m;
  int i, j;
  int stop;
  //  int index;
 
  //Leitura da matriz
  use(argc);
  input(argc, argv, A, b, &n, &m);

  printMAT(A, n, m);


  //Inicio da decomposicao QR
  max = sigmaArray(A, sigma, n, m);
  stop = permuta(A, sigma, permutacao, 0, n, m);


  //Iteracao da decomposicao
  for (i = 0; stop != 1; i++) {
    printf("INDICE I: %d\n", i);
    gama =calculaUMiGama(A, sigma, max, i, n, m);


    printf("POS FUNCAO GAMA\n");
    printVET(sigma, m);    


    printf("GAMA: %.3f\n", gama);
    produtoQA(A, gama, i, n, m);

    printf("POS FUNCAO PRODUTO\n");
    printVET(sigma, m);
    sigmaRecalc(A, sigma, i, n, m);
    
    printf("POS FUNCAO SIGMARECALC\n");
    printMAT(A, n, m);
    printVET(sigma, m);

    stop = permuta(A, sigma, permutacao, i, n, m);
    

  }

  printf("%d\n", i);
  printMAT(A, n, m);

  return 0;
}
