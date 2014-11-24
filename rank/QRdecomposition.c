#include "QRdecomposition.h"
#include <math.h>
/*
Ordem do algoritmo decomposicao QR com posto incompleto:
1) Determinar o elemento de maior valor absoluto 'max' da matriz A[n][m]
2) Multiplicar a matriz A por 1 / 'max' (evita overflow no calculo da norma) 

->Loop<-
  3) Calcular/Recalcular a norma das colunas de A[n][m]
  4) Permutar a coluna atual com a coluna de maior norma
     [se a norma for zero, avisar e sair do loop]
     [armazenar a permutacao]
  5) Encontrar a Q e fazer QA

*/


/*Algoritmo do posto incompleto*/
/*Funcao auxiliar*/
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


/*Algoritmo do posto incompleto*/
/***********************************************
 * Calcula e guarda sobre o vetor sigma, as normas(sigma) 
 * ao quadrado de cada coluna (orientada a linha)
 * Retorna o elemento maximo da matriz
 ***********************************************/
/*Guardar max no retorno*/
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


/*Algoritmo do posto incompleto*/
/***********************************************
 * "Recalcula" normas(sigma) das colunas subtraindo 
 * os elementos de A da linha index (orientada a linha)
 ***********************************************/
void sigmaRecalc(double A[nmax][mmax], double sigma[mmax], int index, int n, int m) {
  int i,j;
  printVET(sigma, m);
  printf("index = %d\n",index);
  printf("sigma[0] = %.3f\n",sigma[index]);

  for (j = index; j < m; j++) {
    sigma[j] -= (A[index][j] * A[index][j]);
    printf("sigma[%d] (%.3f) -= A[%d][%d] (%.3f) * A[%d][%d] (%.3f) \n",j,sigma[j],index,j,A[index][j],index,j,A[index][j]);
  }
}


/*Algoritmo do posto incompleto*/
/*Funcao auxiliar*/
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


/*Algoritmo do posto incompleto*/
/***************************************
 * Permuta as colunas de A checando as normas 
 * dos indices 'index' ate 'm'
 * Armazena a permutacao no vetor 'ordem'
 * Retorna 1 se a submatriz de A for nula 
 ***************************************/
int permuta(double A[nmax][mmax], double sigma[mmax], int ordem[nmax], int index,  int n, int m) {
  int i, j, k;
  double aux;
  double max;

  max = maximo(sigma, m);
  if(max < epsilon) return 1;

  k = maxIndex(sigma, index, m);

  ordem[index] = k;

  /*a coluna de maior norma se encontra no lugar certo*/
  if (k == index)
    return 0;

  switchCol(A, sigma, index, k, n);

  return 0;
}


/*Algoritmo do posto incompleto*/
/*Funcao auxiliar*/
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


/*******************************
 * Limpa o vetor
 *******************************/
void clean(double x[nmax], int n) {
  int i;
  for (i = 0; i < n; i++) 
    x[i] = 0;
}


/*Algoritmo 3.2.37 do Livro Fundamentals of Matrix Computations*/
double calculaUMiGama(double A[nmax][mmax], double norma[nmax], double max, int index, int n, int m) {
  int i;
  double x[nmax];
  double gama, sigma, aux;

  sigma = sqrt (norma[index]);

  //  printf("FUNCAO CALCULA UMIGAMA: SIGMA:   %.3f\n",sigma);


  if (sigma < epsilon) 
    return epsilon;

  copyCol(A, x, index, n);
  
  if (x[index] < 0) 
    sigma *= (-1);
  
  //  printf("FUNCAO CALCULA UMIGAMA: VETOR x:\n");
  //printVET(x,n);

  x[index] += sigma;
  gama = (x[index] / sigma) * max;

  aux = x[index];
  for (i = index; i < n; i++)
    x[i] /= aux;

  pasteCol(A, x, index, n);

  A[index][index] = sigma;
  return gama;
}


/*******************************
 * Retorna valor máximo do vetor
 * x.
 *******************************/
double maximo(double x[nmax], int n) {
  int i;
  double m = fabs(x[0]);
  for (i = 1; i < n; i++) 
    if (fabs(x[i]) > m) 
      m = fabs(x[i]);

  return m;
}


/*Algoritmo 3.2.40 do Livro Fundamentals of Matrix Computations*/
/*index = Coluna de A a ser zerado*/
void produtoQA(double A[nmax][mmax], double gama, int index, int n, int m) {
  double aux[nmax], auxT[nmax];
  double vT[nmax];
  int i, j;

  copyCol(A, aux, index, n);
  copyCol(A, vT, index, n);

  //  printf("FUNCAO produtoQA:    GAMA: %.5f\n", gama);
  //  printMAT(A,n,m);

  //  printf("FUNCAO produtoQA:   VT\n");
  //  printVET(vT, n);


  vT[index] = gama;  
  for (i = index + 1; i < n; i++)
    vT[i] *= gama;


  //  printf("FUNCAO produtoQA: VETOR vT\n");
  //  printVET(vT, n);


  /*orientada a linha*/
  /*vT <- vT B*/
  clean(auxT, nmax);

  for (i = index; i < n; i++) 
    for (j = 0; j < m; j++){
      auxT[j] += (vT[i] * A[i][j]);
      //printf("FUNCAO produtoQA: auxT[%d] += vT[%d] (%.3f) * A[%d][%d] (%.3f) = %.3f\n",j,i,vT[i],i,j,A[i][j], vT[i] * A[i][j]);      
    }
  //  printf("FUNCAO AKSODASMA===============\n");

  //  printVET(aux, n);
  // printVET(auxT, n);

  /*B <- B - uvT*/
  for(i = index; i < n; i++) 
    for(j = index; j < m; j++) 
      A[i][j] -= aux[i] * auxT[j];

  //  printMAT(A,n,m);

}

/*Copia a coluna da matriz A de indice index*/
void copyCol(double A[nmax][mmax], double x[nmax], int index, int n) {
  int i, j;
  
  clean(x, nmax);
  for (i = index; i < n; i++) 
    x[i] = A[i][index];
}

/*Copia o vetor transposto x para a coluna de A do indice index*/
void pasteCol(double A[nmax][mmax], double x[nmax], int index, int n) {
  int i, j;
  
  for (i = index; i < n; i++)
    A[i][index] = x[i];
}
