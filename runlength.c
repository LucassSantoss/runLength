#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* openFile(const char *filename, const char *mode);

void pgmToPgmc(FILE *input_file, FILE *output_file);

void pgmcToPgm(FILE *input_file, FILE *output_file);

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *input_file = argv[1];
    char *output_file = argv[2];
    
    FILE *ptr_input = openFile(input_file, "r");
    FILE *ptr_output = openFile(output_file, "w+");

    char input_type[2];
    fscanf(ptr_input, "%s", input_type);
    printf("INPUT TYPE: %s\n", input_type);
    
    if(strcmp(input_type, "P2") == 0){
        pgmToPgmc(ptr_input, ptr_output);
    }

    if(strcmp(input_type, "P8") == 0){
        pgmcToPgm(ptr_input, ptr_output);
    }

}

FILE* openFile(const char *filename, const char *mode){
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void pgmcToPgm(FILE *input_file, FILE *output_file){
  printf("OUTPUT TYPE: P2\n");
  // Podemos trocar essa parte das linhas e colunas por uma função para não ficar repetido 2x
  char strColumns[3];
  char strLines[3];
  char whiteColor[3];
  fscanf(input_file, "%s", strColumns);
  fscanf(input_file, "%s", strLines);
  fscanf(input_file, "%s", whiteColor);
  int columns = atoi(strColumns);
  int lines = atoi(strLines);
  printf("Quantidade de colunas: %d\n", columns);
  printf("Quantidade de linhas: %d\n", lines);
  printf("Tonalidade máxima (branco): %s\n", whiteColor);
}

void pgmToPgmc(FILE *input_file, FILE *output_file){
  printf("OUTPUT TYPE: P8\n");
  // Podemos trocar essa parte das linhas e colunas por uma função para não ficar repetido 2x
  char strColumns[3];
  char strLines[3];
  char whiteColor[3];
  fscanf(input_file, "%s", strColumns);
  fscanf(input_file, "%s", strLines);
  fscanf(input_file, "%s", whiteColor);
  int columns = atoi(strColumns);
  int lines = atoi(strLines);
  printf("Quantidade de colunas: %d\n", columns);
  printf("Quantidade de linhas: %d\n", lines);
  printf("Tonalidade máxima (branco): %s\n", whiteColor);
}