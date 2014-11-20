#include "utils.h"
#include "QRdecomposer.h"


int main() {

  return 0;
}

/*******************************
 * Retorna valor máximo do vetor
 * x.
 *******************************/
double maximo(double x[], int n) {
  int i;
  double m = x[0];

  for (i = 1; i < n; i++) 
    if (x[i] > m) 
      m = x[i];

  return m;
}

/*******************************
 * Verifica se o vetor x é iden-
 * ticamente nulo.
 *******************************/
boolean vetorNulo(double x[], int n) {
  int i;

  for (i = 0; i < n; i++) 
    if (x[i] != 0) 
      return false;

  return true;
}

/*******************************
 * Verifica se o vetor x é iden-
 * ticamente nulo.
 *******************************/
boolean normaliza(double x[], int n, int m) {
  int i;
  for (i = 0; i < n; i++) 
    x[i] /= m;
}

/*******************************
 * Retorna norma euclideana do
 * vetor x.
 *******************************/
double normaEuclideana(double x[], int n) {
  double norma = 0;
  int i;


  for (i = 0; i < n; i++) 
    norma += x[i]*x[i]; 

  norma = sqrt(norma);

  return norma;
}

/*Devolve gama?*/
double calculaMu(double x[], int n) {
  
  /*Resumo*/
  /* m  = max{Xi} */
  /* se x = 0 entao */
  /*   gama = 0 */
  /* senão */
  /*   Xi = Xi/m, i = 1,n */
  /*   sgma = raiz(X1²+...+Xn²) */
  /*   se x < 0 entao */
  /*     sgma = (-1)*sgma */
  /*   X1 = X1 + sgma */
  /*   gama = 1/(sgma*mu1) */
  /*   sgma = sgma*m */
  /* fim se */

  int i;
  double max;
  double gama, sigma;

  max = maximo(x, n);
  if (max == 0)
    gama = 0;
 
  else {
    normaliza(x, n, max);
    sigma = normaEuclideana(x, n);

    if (x[0] < 0) 
      sigma *= (-1);

    x[0] += sigma;
    gama = 1 / (sigma * x[0]);
    /*sigma *= max -- Ver se vai deixar ou não!!!*/

    /*Como x[0] = 1 sempre, começa do indice 1*/
    for (i = 1; i < n; i++)
      x[i] /= gama;

    
    x[0] = sigma;
    
    /*ou faça a funcao receber o indice e o vetor para guardar gama*/
    return (gama * max);
  }


  void produtoQA(double A[nmax][mmax], int index, int n) {
    double aux[n];
    //    for(int i = )
  



  }




   
}  
