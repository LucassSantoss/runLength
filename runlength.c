#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

void main(int qtdArgumentos, char *nomeArquivos[])
{
  setlocale(LC_ALL, "Portuguese");
  if (qtdArgumentos != 3) // nome do programa, arquivo de entrada, arquivo de saída
    printf("Para usar o programa, use: ./%s arquivo_entrada arquivo_saída\n", nomeArquivos[0]);

  // Declarando variáveis dos arquivos
  FILE *arqEntrada = fopen(nomeArquivos[1], "r"); // abre apenas para leitura
  FILE *arqSaida = fopen(nomeArquivos[2], "w");   // abre para escrita

  if (arqEntrada == NULL)
    printf("Erro ao abrir o arquivo de entrada.\n");

  if (arqSaida == NULL)
    printf("Erro ao abrir o arquivo de saída.\n");
}