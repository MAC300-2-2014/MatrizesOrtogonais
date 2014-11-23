/*Testar as funcoes, de preferencia*/
#include "utils.h"

double maxMatriz(double A[nmax][nmax], int n, int m);
double sigmaArray(double A[nmax][mmax], double sigma[mmax], int n, int m);
void sigmaRecalc(double A[nmax][mmax], double sigma[mmax], int index, int n, int m);
void switchCol(double A[nmax][mmax], int orderm[mmax], int index1, int index2, int n);

void permuta(double A[nmax][mmax], double sigma[mmax], int ordem[nmax], int index,  int n, int m);
int maxIndex(double max[mmax], int k, int m);



double maximo(double x[], int n);
boolean vetorNulo(double x[], int n);
boolean normaliza(double x[], int n, int m);
double calculaMu(double x[], int n);
void produtoQA(double A[nmax][mmax], double gama, int index, int n, int m);
