#include "QRdecomposition.h"
#include <math.h>
/*
Ordem do algoritmo decomposicao QR com posto incompleto:
1) Determinar o elemento de maior valor absoluto 'max' da matriz A[n][m]
2) Multiplicar a matriz A por 1 / 'max' (evita overflow no calculo da norma) 

->Loop<-
  3) Calcular/Recalcular a norma das colunas de A[n][m]
  4) Permutar a coluna atual com a coluna de maior norma
  5) Encontrar a Q e fazer QA
*/


/***********************************************
 * Divide os elementos da matriz A pelo maior 
 * elemento da matriz 'max' em modulo.
 * A funcao devolve 'max'.
 ***********************************************/
double maxMatriz(double A[nmax][nmax], int n, int m) {
  int i,j;
  double max = 0;
  
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      if (fabs(A[i][j]) > max)
	max = fabs(A[i][j]);

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      A[i][j] = (A[i][j] / max);
  
  return max;
}


/***********************************************
 * Calcula e guarda sobre o vetor sigma, as normas(sigma) 
 * ao quadrado de cada coluna (orientada a linha)
 * Retorna o elemento maximo da matriz
 ***********************************************/
double sigmaArray(double A[nmax][mmax], double sigma[mmax], int n, int m) {
  double max;
  int i,j;
  
  clean(sigma, m);
  
  max = maxMatriz(A, n, m);
  
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      sigma[j] += ((A[i][j]) * (A[i][j]));
  
    return max;
}


/***********************************************
 * "Recalcula" normas(sigma) das colunas subtraindo 
 * os elementos de A da linha index (orientada a linha)
 ***********************************************/
void sigmaRecalc(double A[nmax][mmax], double sigma[mmax], int index, int n, int m) {
  int j;

  for (j = index + 1; j < m; j++)
    sigma[j] -= (A[index][j] * A[index][j]);
}


/***********************************************
 * Troca os elementos das colunas de indice
 * index1 por index2 da matriz A
 * Realiza tambem a troca das normas
 ***********************************************/
void switchCol(double A[nmax][mmax], double sigma[mmax], int index1, int index2, int n){
  int i;
  double aux;

  for (i = 0; i < n; i++) {
    aux = A[i][index1];
    A[i][index1] = A[i][index2];
    A[i][index2] = aux;
  }
 
  aux = sigma[index1];
  sigma[index1] = sigma[index2];
  sigma[index2] = aux;
}


/***************************************
 * Permuta as colunas de A checando as normas 
 * dos indices 'index' ate 'm'
 * Armazena a permutacao no vetor 'ordem'
 * Retorna 1 se a submatriz de A for nula 
 ***************************************/
int permuta(double A[nmax][mmax], double sigma[mmax], int ordem[nmax], int index, int n, int m) {
  int k;
  double max;

  max = maximo(sigma, index, m);
  ordem[index] = index;

  if(max < epsilon) return 1;

  k = maxIndex(sigma, index, m);

  /*a coluna de maior norma se encontra no lugar certo*/
  if (k == index)
    return 0;

  switchCol(A, sigma, index, k, n);
  ordem[index] = k;

  return 0;
}


/***************************************
 * Retorna o indice do maior elemento 
 * do vetor sigma a partir de k
 ***************************************/
int maxIndex(double sigma[mmax], int k, int m) {
  int i;
  int index = k;
  double max = fabs(sigma[k]);

  for (i = k + 1; i < m; i++)
    if (fabs(sigma[i]) > max) {
      max = fabs(sigma[i]);
      index = i;
    }

  return (index);
}


/***************************************
 * Limpa o vetor 
 ***************************************/
void clean(double x[nmax], int n) {
  int i;
  for (i = 0; i < n; i++) 
    x[i] = 0;
}


/***************************************
 * Calcula u, sigma, e gama para o calculo
 * de Q = I - gama * u * uT
 * Funcao retorna gama 
 ***************************************/
/*Algoritmo 3.2.37 do Livro Fundamentals of Matrix Computations*/
double calculaUSigmaGama(double A[nmax][mmax], double norma[nmax], double u[nmax], double max, int index, int n, int m) {
  int i;
  double gama, sigma, aux;

  sigma = sqrt (norma[index]);

  if (sigma < epsilon) 
    return epsilon;

  copyCol(A, u, index, n);
  
  if (u[index] < 0) 
    sigma *= (-1);
  
  u[index] += sigma;

  gama = (u[index] / sigma);

  aux = u[index];
  for (i = index; i < n; i++)
    u[i] /= aux;

  if (sigma > 0)
    sigma *= -1;

  return gama;
}


/***************************************
 * Retorna o elemento maximo do vetor x
 * do indice 'index' a 'n'
 ***************************************/
double maximo(double x[nmax], int index, int n) {
  int i;
  double max = fabs(x[index]);
  for (i = index + 1; i < n; i++) 
    if (fabs(x[i]) > max) 
      max = fabs(x[i]);

  return max;
}


/***************************************
 * Realiza o produto 
 * QA = A - u * ((gama * uT) * A)
 ***************************************/
void produtoQA(double A[nmax][mmax], double b[nmax], double u[nmax], double gama, int index, int n, int m) {
  double auxT[nmax];
  double vT[nmax];
  double s = 0;
  int i, j;

  copyU(u, vT, n);
  
  for (i = index; i < n; i++)
    vT[i] *= gama;

  clean(auxT, nmax);
  
  /*orientada a linha*/
  /*vT <- vT B*/
  for (i = index; i < n; i++) 
    for (j = index; j < m; j++)
      auxT[j] += (vT[i] * A[i][j]);


  /* vT * b */
  for (i = index; i < n; i++)
    s += (vT[i] * b[i]);


  /*B <- B - uvT*/
  for (i = index; i < n; i++) 
    for (j = index; j < m; j++) 
      A[i][j] -= u[i] * auxT[j];


  for (i = index; i < n; i++)
    b[i] -= (u[i] * s);

  /*Armazena u em A*/
  pasteCol(A, u, index, n);
}


/***************************************
 * Copia a coluna da matriz A de indice 
 * 'index' no vetor x
 ***************************************/
void copyCol(double A[nmax][mmax], double x[nmax], int index, int n) {
  int i;
  
  clean(x, nmax);
  for (i = index; i < n; i++) 
    x[i] = A[i][index];
}


/***************************************
 * Copia para a coluna da matriz A de indice 
 * 'index' o vetor x
 ***************************************/
void pasteCol(double A[nmax][mmax], double x[nmax], int index, int n) {
  int i;
  
  for (i = index + 1; i < n; i++)
    A[i][index] = x[i];
}


/***************************************
 * Copia o vetor u em v
 ***************************************/
void copyU(double u[nmax], double v[nmax], int n) {
  int i;

  clean(v, n);

  for (i = 0; i < n; i++)
    v[i] = u[i];
}


/***************************************
 * Dada a matriz A triangular superior e 
 * o vetor b, a funcao calcula  Ax = b
 * por back substitution
 ***************************************/
void backSubs(double A[nmax][mmax], double b[nmax], int rank) {
  int j, k;

  for (j = (rank - 1); j >= 0; j--) {
    b[j] /= A[j][j];
    
    for (k = j - 1; k >= 0; k--)
      b[k] -= (A[k][j] * b[j]);
  }
}


/***************************************
 * Reordena o vetor 'v' das permutacoes
 * realizadas
 ***************************************/
void reorder(double b[nmax], int permutacao[nmax], double max, int rank){
  double aux;
  int i;

  for (i = 0; i <= (rank - 1); i++)
    b[i] /= max;

  for (i = rank - 1; i >= 0; i--) 
    if (i != permutacao[i]) {
      aux = b[permutacao[i]];
      b[permutacao[i]] = b[i];
      b[i] = aux;
    }
}



/***************************************
 * Calcula possiveis solucoes de Ax = b
 ***************************************/
void solution(double A[nmax][mmax], double b[nmax], int permutacao[nmax], double max, int rank, int n, int m) {
  double aux[nmax];
  int i, j; 

  /*Caso do Posto Incompleto*/
  if (rank != m) {

    clean(aux, nmax);

    /*vetor arbitrario*/
    for (i = rank; i < m; i++)
      aux[i] = 1;
    
    for (i = 0; i < rank; i++)
      for (j = rank; j < m ; j++) 
	b[j] -= (A[i][j] * aux[j]);
  }

  backSubs (A, b, rank);
  reorder(b, permutacao, max, rank);

  printf("\nSOLUCAO: \n");
  for (i = 0; i < rank; i++)
    printf("x%d = %.5f \n", i, b[i]);
  printf("\n\n");

  residuo(b, rank, n);
}


/***************************************
 * Calcula o residuo 
 ***************************************/
void residuo(double b[nmax], int rank, int n) {
  double res = 0;
  int i;
  
  for (i = rank; i < n; i++) 
    res += (b[i] * b[i]);

  res = sqrt(res);
  printf("Residuo: = %.5f \n", res);
}



