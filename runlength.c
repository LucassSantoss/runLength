#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

void main(int qtdArgumentos, char *argumentos[])
{
  setlocale(LC_ALL, "Portuguese");
  if (qtdArgumentos != 3) // nome do programa, arquivo de entrada, arquivo de saída
    printf("Para usar o programa, use: %s arquivo_entrada arquivo_saída\n", argumentos[0]);

  FILE *arqEntrada = fopen(argumentos[1], "r"); // abre apenas para leitura
  FILE *arqSaida = fopen(argumentos[2], "w");   // abre para escrita

  if (arqEntrada == NULL)
    printf("Erro ao abrir o arquivo de entrada.\n");

  if (arqSaida == NULL)
    printf("Erro ao abrir o arquivo de saída.\n");

  char caracter;
  char proxCaracter;
  char repetido;
  char qtd;
  char qtdVetor[2];
  int int_qtd;
  while ((caracter = fgetc(arqEntrada)) != EOF) // EOF -> end of file
  {
    if (caracter == '@')
    {
      // Verifica se tem algum @ com números repetidos
      fgetc(arqEntrada);
      repetido = fgetc(arqEntrada);
      proxCaracter = fgetc(arqEntrada);
      qtd = fgetc(arqEntrada);

      // Verifica se a quantidade de números repetidos tem 2 dígitos (para podermos usar o atoi, precisamos de uma string)
      if ((qtdVetor[1] = fgetc(arqEntrada)) != ' ')
      {
        // Se for de 2 dígitos, atríbuimos os dígitos a esse vetor
        qtdVetor[0] = qtd;
      }
      else
      {
        // Se for de 1 dígito, atríbuimos um 0 antes do primeiro número, para se tornar uma string (mais de um caracter)
        qtdVetor[0] = '0';
        qtdVetor[1] = qtd;
      }
      int_qtd = atoi(qtdVetor);
      printf("Quantidade = %d, letra = %c\n", int_qtd, repetido);
      for (int i = 0; i < int_qtd; i++)
      {
        fputc(repetido, arqSaida);
        fputc(proxCaracter, arqSaida);
        if (proxCaracter != ' ')
        {
          if (i < int_qtd - 1)
            fputc(' ', arqSaida);
        }
      }
    }
    else
    {
      fputc(caracter, arqSaida);
    }
  }

  fclose(arqEntrada);
  fclose(arqSaida);
}