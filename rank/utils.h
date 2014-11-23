#include <stdio.h>
#include <math.h>

#define nmax 1000
#define mmax 1000
#define epsilon 1E-10

void input(int argc, char *argv[], double A[nmax][nmax], double b[nmax], int *line, int *col);
void printMAT(double mat[nmax][nmax], int n, int m);
void printVET(double vet[mmax], int n);


void limpa(char vet[], int n);
void use(int argc);

