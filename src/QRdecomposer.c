#include "utils.h"
#include "QRdecomposer.h"

int main() {
  return 0;
}

/*******************************
 * Limpa o vetor
 *******************************/
void clean(double x[], int n) {
  int i;
  for (i = 0; i < n; i++) 
    x[i] = 0;
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

/*Algoritmo 3.2.37 do Livro Fundamentals of Matrix Computations*/
/*Devolve gama?*/
double calculaMu(double x[], int n) {

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
    gama *= max;
  }

  /*ou faça a funcao receber o indice e o vetor para guardar gama*/
  return gama;
}



  /*Algoritmo 3.2.40 do Livro Fundamentals of Matrix Computations*/
  /*index = Coluna de A a ser zerado*/
void produtoQA(double A[nmax][mmax], double gama, int index, int n, int m) {
  double auxT[index];
  double aux[index];
  
  double vT[m - index];
  int i, j, k;

  for(i = index; i < n; i++) 
    aux[i] = A[index][i];

  /*orientada a linha*/
  /*vT (v transposta) <- vT B*/
  clean(auxT, index);
  for(i = 0; i < n; i++) {
    k = aux[i] * gama;

    for(j = 0; j < n; j++)
      auxT[j] += k * A[i][j];  
  }
    
  /*B <- B - uvT*/
  for(i = index; i < n; i++) 
    for(j = index; j < m; j++) 
      A[i][j] -= aux[i] * auxT[j];
}



  


   

