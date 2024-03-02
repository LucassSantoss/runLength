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

void compress(PgmFile imageStruct, char outputName[]);

void unzip(PgmFile imageStruct);

void loadMatrix(PgmFile *imageStruct);

char ***alocateMatrix(int cols, int lines);

PgmFile createStruct(FILE *ptrFile);


int main(int argc, char *argv[]){
  if (argc != 3) { 
        printf("Usage: %s <inputFile> <outputFile>\n", argv[0]);
        exit(EXIT_FAILURE);
  }


  char *inputName = argv[1];
  char *outputName = argv[2];
  
  FILE *inputFile = openFile(inputName, "r");

  PgmFile imageStruct = createStruct(inputFile);

  if(strcmp(imageStruct.type, "P2") == 0){
    compress(imageStruct, outputName);
  }

  if(strcmp(imageStruct.type, "P8") == 0){
      unzip(imageStruct);
  }
  printf("\nImageStruct tipo: %s", imageStruct.type);
  printf("\nImageStruct colunas: %d", imageStruct.cols);
  printf("\nImageStruct linhas: %d", imageStruct.lines);
  printf("\n\n");
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
            matrix[i][j] = (char *)malloc(4 * sizeof(char));
    }
  }
  
  return matrix;
}

void loadMatrix(PgmFile *imageStruct){

  imageStruct->matrix = alocateMatrix(imageStruct->cols, imageStruct->lines);
  
  for(int i = 0; i < imageStruct->lines; i ++){
    for(int j = 0; j < imageStruct->cols; j++){
      fscanf(imageStruct->ptrFile, "%s", imageStruct->matrix[i][j]); 
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

  loadMatrix(&imageStruct);

  return imageStruct;
}

void compress(PgmFile imageStruct, char outputName[]){
  
  FILE *outputFile = openFile(outputName, "w+"); 

  fprintf(outputFile, "%s\n","P8");
  fprintf(outputFile, "%d ",imageStruct.cols);
  fprintf(outputFile, "%d\n",imageStruct.lines);
  fprintf(outputFile, "%d\n",imageStruct.whiteColor);
  
  char previousValue[3] = "";
  for (int i = 0; i < imageStruct.lines; i++) {
      strcpy(previousValue, imageStruct.matrix[i][0]);
      int count = 1;
      for (int j = 1; j < imageStruct.cols; j++) {
          if (strcmp(previousValue, imageStruct.matrix[i][j]) == 0) {
              count++;
          } 
          else {
              if (count > 3) {
                  fprintf(outputFile, "@ %s %d ", previousValue, count);
              } else {
                  for (int i = 0; i < count; i++) {
                      fprintf(outputFile, "%s ", previousValue);
                  }
              }
              strcpy(previousValue, imageStruct.matrix[i][j]);
              count = 1;
          }

          if (j == imageStruct.cols - 1) {
              if (count > 3) {
                  fprintf(outputFile, "@ %s %d ", previousValue, count);
              } else {
                  for (int i = 0; i < count; i++) {
                      fprintf(outputFile, "%s ", previousValue);
                  }
              }
              fprintf(outputFile, "\n");
              count = 1;
          }
      }
  }
}



