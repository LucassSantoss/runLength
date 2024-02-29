#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
  int qtd_linhas = 4;
  int qtd_colunas = 3;

  int **mat;
  mat = (int **)malloc(sizeof(int *) * qtd_linhas);
  for (int i = 0; i < qtd_linhas; i++)
  {
    mat[i] = (int *)malloc(sizeof(int) * qtd_colunas);
  }

  for (int i = 0; i < qtd_linhas; i++)
  {
    free(mat[i]);
  }
  free(mat);
}