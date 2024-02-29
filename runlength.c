#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int cols;
    int lines;
    int whiteColor;
    FILE *ptrFile;
    char type[2];
    char **matrix;
} PgmFile;

FILE* openFile(const char *filename, const char *mode);

void compress(PgmFile imageStruct);

void unzip(PgmFile imageStruct);

void loadMatrix(PgmFile imageStruct);

char **alocateMatrix(int cols, int lines);

PgmFile createStruct(FILE *ptrFile);

int main(int argc, char *argv[]){
    if (argc != 3) { 
        printf("Usage: %s <inputFile> <outputFile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *inputName = argv[1];
    char *outputName = argv[2];
    
    FILE *ptrInput = openFile(inputName, "r");
    FILE *ptrOutput = openFile(outputName, "w+");
    
    PgmFile imageStruct = createStruct(ptrInput);

    if(strcmp(imageStruct.type, "P2") == 0){
        compress(imageStruct);
    }

    if(strcmp(imageStruct.type, "P8") == 0){
        unzip(imageStruct);
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

void unzip(PgmFile imageStruct){
  printf("OUTPUT TYPE: P8\n");
    
}

char **alocateMatrix(int cols, int lines){
  char **matrix = (char **)malloc(lines * sizeof(char *));
  
  for(int i = 0; i < lines; i ++){
    matrix[i] = (char *)malloc(cols * sizeof(char*));
  }
  
  return matrix;
}

void loadMatrix(PgmFile imageStruct){
  char **matrix = alocateMatrix(imageStruct.cols, imageStruct.lines);

  for(int i = 0; i < imageStruct.lines; i ++){
    for(int j = 0; j < imageStruct.cols; j++){
      char pixel[3];
      fscanf(imageStruct.ptrFile, "%s", &pixel); //Lendo como inteiro, mas deveria ser string
      printf(" %s", pixel);
      strcpy(&matrix[i][j], pixel);
      printf("%s", &matrix[i][j]);
    }
    printf("/n");
  }
  printf("TESTEE");
  /*
  for (int i=0; i<imageStruct.lines;i++){
    for (int j=0; j<imageStruct.cols;j++){
      printf("SAFADEZA");
      printf("%d %d", imageStruct.lines, imageStruct.cols);
      printf("%s ", matrix[i][j]);
      printf("chega nunca");
    }
    printf("\n");
  }
  */

  imageStruct.matrix = matrix;
}

PgmFile createStruct(FILE *ptrFile){
  PgmFile imageStruct;
  fscanf(ptrFile, "%s", imageStruct.type);
  fscanf(ptrFile, "%d", &imageStruct.cols);
  fscanf(ptrFile, "%d", &imageStruct.lines);
  fscanf(ptrFile, "%d", &imageStruct.whiteColor);
  imageStruct.ptrFile = ptrFile;

  loadMatrix(imageStruct);

  for (int i=0; i < imageStruct.lines;i++){
    for (int j=0; j < imageStruct.cols;j++){
      printf("%d ", imageStruct.matrix[i][j]);
    }
    printf("\n");
  }


  // for (int i=0; i<imageStruct.lines;i++){
  //   for (int j=0; j<imageStruct.cols;j++){
  //     printf("%c ", imageStruct.matrix[i][j]);
  //   }
  //   printf("\n");
  // }

  printf("Quantidade de colunas: %d\n", imageStruct.cols);
  printf("Quantidade de linhas: %d\n", imageStruct.lines);
  printf("Tonalidade máxima (branco): %d\n", imageStruct.whiteColor);
  return imageStruct;
}

void compress(PgmFile imageStruct){
  printf("OUTPUT TYPE: P8\n");
}