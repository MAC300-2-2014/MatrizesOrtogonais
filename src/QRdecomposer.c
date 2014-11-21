#include "utils.h"
#include "QRdecomposer.h"

int main() {
  return 0;
}

/*Algoritmo do posto incompleto*/
/***************************************
 * Coloca sobre o vetor max, os maiores
 * elementos de cada coluna (orientada a linha)
 ***************************************/
void maxCol(double A[nmax][mmax], double max[mmax], int n, int m) {
  int i,j;

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      if (fabs(A[i][j]) > max[j])
	max[j] = fabs(A[i][j]);
}

/*Algoritmo do posto incompleto*/
/***************************************
 * Calcula e guarda sobre o vetor max, as 
 * normas(sigma) ao quadrado de cada coluna 
 * (orientada a linha)
 ***************************************/
void sigmaArray(double A[nmax][mmax], double sigma[mmax], int n, int m) {
  double max[mmax];
  int i,j;

  clean(sigma, m);
  clean(max, m);

  maxCol(A,max,n,m);

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      sigma[j] += ((A[i][j] / max[j]) * (A[i][j] / max[j]));
}


/*Algoritmo do posto incompleto*/
/***************************************
 * "Recalcula" normas(sigma) das colunas
 * subtraindo os elementos de A da linha index
 * (orientada a linha)
 ***************************************/
void sigmaRecalc(double A[nmax][mmax], double sigma[mmax], int index, int n, int m) {
  int i,j;

  for (j = 0; j < m; j++)
    sigma[j] -= (A[index][j] * A[index][j]);
}


/*Algoritmo do posto incompleto*/
/***************************************
 * Permuta as colunas de A  a partir dos 
 * checando as normas dos indices 
 * 'index' ate 'm'
 ***************************************/
void permuta(double A[nmax][mmax], double sigma[mmax], int index,  int n, int m) {
  int i, j, k;
  double aux;
  double max = sigma[index];

  k = maxIndex(sigma, index, m);

  /*a coluna de maior norma se encontra no lugar certo*/
  if (k == index)
    return;

  /*realiza a permutacao*/
  for (i = 0; i < n; i++) {
    aux = A[i][index];
    A[i][index] = A[i][k];
    A[i][k] = aux;
  }

  aux = sigma[index];
  sigma[index] = sigma[k];
  sigma[k] = aux;
}

/*Algoritmo do posto incompleto*/
/***************************************
 * Retorna o indice do maior elemento 
 * do vetor max a partir de k
 ***************************************/
int maxIndex(double max[mmax], int k, int m) {
  int i;
  int index = k;
  double val = fabs(max[k]);

  for (i = k + 1; i < m; i++)
    if (fabs(max[i]) > val) {
      val = fabs(max[i]);
      index = i;
    }
      
  return (index);
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
  double m = (x[0]);

  for (i = 1; i < n; i++) 
    if ((x[i]) > m) 
      m = (x[i]);

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



  


   

