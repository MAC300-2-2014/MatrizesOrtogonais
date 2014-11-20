#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "utils.h"
 
int input(int argc, char *argv[], double A[nmax][nmax], double b[nmax]) {
  FILE *input = fopen(argv[1], "r");
  char aux[10];
  int n, r;

  if (input == 0) {
    printf("Erro ao abrir arquivo.\n");
    exit(1);
  }


  clean(aux, 10);
  for (r = fgetc(input), n = 0; ('0' <= r) && (r <= '9'); r = fgetc(input), n++) 
    aux[n] = r;
  
  n = atoi(aux);

  printf("Lendo a entrada...\n");
  /*-------------------------------------------------------------------------------*/
  /*-----------------------------ENTRADA MATRIZ------------------------------------*/
  /*-------------------------------------------------------------------------------*/
  int k = fgetc(input);    
  for(r = 0; r < (n*n);) {

    if (('0' <= k) && (k <= '9')) {
      char linha[nmax];
      char coluna[nmax];
      char val[nmax];
      int i;

      clean(val, nmax);
      clean(linha, nmax);
      clean(coluna, nmax);

      for (i = 0; ((k != ' ') && (k != 10)); i++, k = fgetc(input)) 
	linha[i] = k;


      while((k == ' ') || (k == 10))
	k = fgetc(input);
      for (i = 0; ((k != ' ') && (k != 10)); i++, k = fgetc(input)) 
	coluna[i] = k;


      while((k == ' ') || (k == 10))
	k = fgetc(input);
      for (i = 0; ((k != ' ') && (k != 10)); i++, k = fgetc(input)) 
	val[i] = k;

      A[atoi(linha)][atoi(coluna)] = atof(val);
      r++;
    }
    
    else
      k = fgetc(input);          
  }


  /*--------------------------------------------------------------------------------------*/
  /*-------------------------------ENTRADA VETOR------------------------------------------*/ 
  /*--------------------------------------------------------------------------------------*/
  for (r = 0; r < n;) {
    if (('0' <= k) && (k <= '9')) {
      int i;
      char val[nmax];
      char line[nmax];

      clean(val, nmax);
      clean(line, nmax);

      for (i = 0; ((k != ' ') && (k != 10)); i++, k = fgetc(input))
	line[i] = k;

      while((k == ' ') || (k == 10))
	k = fgetc(input);
      for (i = 0; ((k != ' ') && (k != 10) && (k != EOF)); i++, k = fgetc(input))
	val[i] = k;
            
      b[atoi(line)] = atof(val);

      r++;
    }

    else
      k = fgetc(input);    
  }
  printf("Leitura completa!\n");
  fclose(input);
  return n;
}


void clean (char vet[], int n) {
  int i;
  for(i = 0; i < n; i++)
    vet[i] = 0;
}

void use(int argc) {
  if (argc <= 1) {
    printf("Modo de uso:\n");
    printf("$ ./main <nome_do_arquivo> \n");
    exit(1);
  }
}

void printMAT(double mat[nmax][nmax], int n) {
  int i;
  int j;
  for (i = 0; i < n; i++) {
    for (j = 0; j< n; j++) 
      printf("%.3f  ",mat[i][j]);
    printf("\n");
  }
  printf("\n");
}

void printVET(double vet[nmax], int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%.3f  \n", vet[i]);
  printf("\n");
}
