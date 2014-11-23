#include "utils.h"
/*Funcoes testadas
  maxMatriz         ok
  sigmaArray        ok
  switchCol         ok
  clean             ok
*/

double maxMatriz(double A[nmax][nmax], int n, int m);
double sigmaArray(double A[nmax][mmax], double sigma[mmax], int n, int m);
void sigmaRecalc(double A[nmax][mmax], double sigma[mmax], int index, int n, int m);
void switchCol(double A[nmax][mmax], double sigma[mmax], int index1, int index2, int n);

int permuta(double A[nmax][mmax], double sigma[mmax], int ordem[nmax], int index,  int n, int m);
int maxIndex(double max[mmax], int k, int m);

void clean(double x[nmax], int n);

double maximo(double x[nmax], int n);

double calculaMu(double x[], int n);
void produtoQA(double A[nmax][mmax], double gama, int index, int n, int m);
