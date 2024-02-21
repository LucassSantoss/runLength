#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

void main(int qtdArgumentos, char *nomeArquivos[])
{
  setlocale(LC_ALL, "Portuguese");

  if (qtdArgumentos != 3) // nome do programa, arquivo de entrada, arquivo de saída
    printf("Para usar o programa, use: ./%s arquivo_entrada arquivo_saída\n", nomeArquivos[0]);
}