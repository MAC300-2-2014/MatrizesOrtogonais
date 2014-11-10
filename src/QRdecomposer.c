#include "inc/utils.h"

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

  for (i = 1; i < n; i++) {
    if (x[i] > m) 
      m = x[i];
  }

  return m;
}

/*******************************
 * Verifica se o vetor x é iden-
 * ticamente nulo.
 *******************************/
boolean vetorNulo(double x[], int n) {
  int i;

  for (i = ; i < n; i++) {
    if (x[i] != 0) 
      return false;
  }

  return true;
}

/*******************************
 * Verifica se o vetor x é iden-
 * ticamente nulo.
 *******************************/
boolean normaliza(double x[], int n, int m) {
  int i;

  for (i = ; i < n; i++) 
    x[i] /= m;
}

/*******************************
 * Retorna norma euclideana do
 * vetor x.
 *******************************/
double normaEuclideana(double x[], int n) {
  int i;
  double norma;

  for (i = 0; i < n; i++) {
    norma += x[i]*x[i]; 
  }
  norma = math.sqrt(norma);

  return norma;
}

void calculaMu(double x[], int n) {

  
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

  double max;
  double gama, sgma;

  max = maximo(x, n);
  if (vetorNulo(x))
    gama = 0;
  else {
    normaliza(x, n, max);
    sgma = normaEuclideana(x);
    if (x[0] < 0) 
      sgma = (-1) * sgma;
    x[0] += sgma;
    gama = 1 / (sgma * x[0]);
    /*sgma *= max -- Ver se vai deixar ou não!!!*/
  }
   
}  
