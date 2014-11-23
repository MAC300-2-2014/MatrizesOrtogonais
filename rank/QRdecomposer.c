#include "utils.h"
#include "QRdecomposer.h"

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

int main() {
  return 0;
}

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
 * Calcula e guarda sobre o vetor sigma, as  normas(sigma) 
 * ao quadrado de cada coluna (orientada a linha)
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

  for (j = index; j < m; j++)
    sigma[j] -= (A[index][j] * A[index][j]);
}


/*Algoritmo do posto incompleto*/
/*Funcao auxiliar*/
/***********************************************
 * Troca os elementos das colunas de indice
 * index1 por index2 da matriz A
 * Realiza tambem a troca das normas
 ***********************************************/
void switchCol(double A[nmax][mmax], int ordem[mmax], int index1, int index2, int n){
  int i;
  double aux;

  for (i = 0; i < n; i++) {
    aux = A[i][index1];
    A[i][index1] = A[i][index2];
    A[i][index2] = aux;
  }

  i = ordem[index1];
  ordem[index1] = ordem[index2];
  ordem[index2] = i;
}


/*Algoritmo do posto incompleto*/
/***************************************
 * Permuta as colunas de A 
 * checando as normas dos indices 
 * 'index' ate 'm'
 * armazena a permutacao em ordem
 ***************************************/
/*ARRUMAR PERMUTACAO*/
/*CASO ZERO AVISAR!*/
void permuta(double A[nmax][mmax], double sigma[mmax], int ordem[nmax], int index,  int n, int m) {
  int i, j, k;
  double aux;
  double max = sigma[index];

  k = maxIndex(sigma, index, m);

  /*a coluna de maior norma se encontra no lugar certo*/
  if (k == index)
    return;

  switchCol(A, ordem, index, k, n);
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
/*
void clean(double x[nmax], int n) {
  int i;
  for (i = 0; i < n; i++) 
    x[i] = 0;
}
*/

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


/*Algoritmo do posto incompleto*/
/***************************************
 * Identico a funcao calculaMu adaptada
 * para o algoritmo da decomp QR com
 * posto incompleto
 ***************************************/
/*Calcula Q para a iteracao de numero 'n - index'*/
/*
void calculaQ(double A[nmax][mmax], double norma[mmax], int index, int n, int m) {
  int i;
  double max;
  double gama, sigma;

  sigma = sqrt(norma[index]);
  
  if (sigma == 0)
    gama = 0;
 
  else {
    normaliza(x, n, max);
    sigma = normaEuclideana(x, n);
    
    if (x[0] < 0) 
      sigma *= (-1);

    x[0] += sigma;
    gama = 1 / (sigma * x[0]);


    for (i = 1; i < n; i++)
      x[i] /= gama;
    
    x[0] = sigma;
    gama *= max;
  }


  return gama;
}
*/
