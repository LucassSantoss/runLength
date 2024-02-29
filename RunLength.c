#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int cols;
    int lines;
    int whiteColor;
    FILE *ptrFile;
    char type[2];
    char ***matrix;
} PgmFile;

FILE* openFile(const char *filename, const char *mode);

void compress(PgmFile imageStruct);

void unzip(PgmFile imageStruct);

void loadMatrix(PgmFile imageStruct);

char ***alocateMatrix(int cols, int lines);

PgmFile createStruct(FILE *ptrFile);

// int main(int argc, char *argv[]){
    // if (argc != 3) { 
    //     printf("Usage: %s <inputFile> <outputFile>\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    // char *inputName = argv[1];
    // char *outputName = argv[2];
    
    // FILE *ptrInput = openFile(inputName, "r");
    // FILE *ptrOutput = openFile(outputName, "w+");

int main(){


      char address[] = "C:\\users\\ian\\Desktop\\exemplo1.pgm";
      FILE *archive = openFile(address, "r"); 
    
      PgmFile imageStruct = createStruct(archive);

    if(strcmp(imageStruct.type, "P2") == 0){
        compress(imageStruct);
    }

    if(strcmp(imageStruct.type, "P8") == 0){
        unzip(imageStruct);
    }
  printf("\nImageStruct tipo: %s", imageStruct.type);
  printf("\nImageStruct colunas: %d", imageStruct.cols);
  printf("\nImageStruct linhas: %d", imageStruct.lines);
  
}

FILE* openFile(const char *filename, const char *mode){
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void unzip(PgmFile imageStruct){
  printf("OUTPUT TYPE: P2\n");
    
}

char ***alocateMatrix(int cols, int lines){
  char ***matrix = (char ***)malloc(lines * sizeof(char **));
  
  for(int i = 0; i < lines; i ++){
    matrix[i] = (char **)malloc(cols * sizeof(char*));
    for(int j = 0; j < cols; j++) {
            matrix[i][j] = (char *)malloc(4 * sizeof(char)); //cada string tem tamanho máximo de 4 caracteres
    }
  }
  
  return matrix;
}

void loadMatrix(PgmFile imageStruct){

  imageStruct.matrix = alocateMatrix(imageStruct.cols, imageStruct.lines);
  
  for(int i = 0; i < imageStruct.lines; i ++){
    for(int j = 0; j < imageStruct.cols; j++){
      fscanf(imageStruct.ptrFile, "%s", imageStruct.matrix[i][j]); 
    }
  }
  
  for(int i = 0; i < imageStruct.lines; i ++){
    printf("\n");
    for(int j = 0; j < imageStruct.cols; j++){
        printf("%s ", imageStruct.matrix[i][j]);
    }
  }
  printf("\n");
}

PgmFile createStruct(FILE *ptrFile){
  PgmFile imageStruct;
  fscanf(ptrFile, "%s", imageStruct.type);
  fscanf(ptrFile, "%d", &imageStruct.cols);
  fscanf(ptrFile, "%d", &imageStruct.lines);
  fscanf(ptrFile, "%d", &imageStruct.whiteColor);  

  loadMatrix(imageStruct);

  printf("Quantidade de colunas: %d\n", imageStruct.cols);
  printf("Quantidade de linhas: %d\n", imageStruct.lines);
  printf("Tonalidade máxima (branco): %d\n", imageStruct.whiteColor);
  return imageStruct;
}

void compress(PgmFile imageStruct){
  printf("OUTPUT TYPE: P8\n");
}

