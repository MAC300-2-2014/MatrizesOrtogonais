#include "utils.h"

double maxMatriz(double A[nmax][nmax], int n, int m);
double sigmaArray(double A[nmax][mmax], double sigma[mmax], int n, int m);
void sigmaRecalc(double A[nmax][mmax], double sigma[mmax], int index, int n, int m);
void switchCol(double A[nmax][mmax], double sigma[mmax], int index1, int index2, int n);
int permuta(double A[nmax][mmax], double sigma[mmax], int ordem[nmax], int index,  int n, int m);
int maxIndex(double max[mmax], int k, int m);
void clean(double x[nmax], int n);
double maximo(double x[nmax], int index, int n);
void produtoQA(double A[nmax][mmax], double b[nmax], double u[nmax], double gama, int index, int n, int m);
double calculaUSigmaGama(double A[nmax][mmax], double norma[nmax], double u[nmax], double max, int index, int n, int m);
void copyCol(double A[nmax][mmax], double x[nmax], int index, int n);
void pasteCol(double A[nmax][mmax], double x[nmax], int index, int n);
void copyU(double u[nmax], double v[nmax], int n);
void backSubs(double A[nmax][mmax], double b[nmax], int rank);
void reorder(double b[nmax], int permutacao[nmax], double max, int rank);
void printResult(double b[nmax], int rank);
void residuo(double A[nmax][mmax], double b[nmax], int rank, int n, int m);
void solution(double A[nmax][mmax], double b[nmax], int permutacao[nmax], double max, int rank, int n, int m);
