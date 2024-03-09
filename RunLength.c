#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Made by: Lucas Santos, Ian Fernandes, Bruno Mascioli de Souza 
// Github: LucassSantoss, IofSoft, brunomascioli 

typedef struct {
  int cols;
  int lines;
  int whiteColor;
  FILE *ptrFile;
  char type[3];
  char **matrix;
} PgmFile;

FILE *openFile(const char *filename, const char *mode);

void compress(PgmFile imageStruct, FILE *outputFile);

void writePixel(FILE *outputFile, char *value, int count);

void decompress(PgmFile imageStruct, FILE *outputFile);

void loadMatrix(PgmFile *imageStruct);

char **alocateMatrix(int cols, int lines);

PgmFile createStruct(FILE *ptrFile);

void freeMatrix(PgmFile *imageStruct);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <inputFile> <outputFile>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *inputName = argv[1];
  char *outputName = argv[2];
  FILE *inputFile = openFile(inputName, "r");
  FILE *outputFile = openFile(outputName, "w");
  char *inputType = strrchr(inputName, '.');

  if (strcmp(inputType, ".pgm") != 0 && strcmp(inputType, ".pgmc") != 0) {
    printf("Invalid extension!");
    exit(EXIT_FAILURE);
  }

  PgmFile imageStruct = createStruct(inputFile);

  if (strcmp(inputType, ".pgm") == 0) {
    compress(imageStruct, outputFile);
  }
  if (strcmp(inputType, ".pgmc") == 0) {
    decompress(imageStruct, outputFile);
  }
  
  fclose(inputFile);
  fclose(outputFile);
}

FILE *openFile(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (file == NULL) {
    printf("Can't open file: %s\n", filename);
    exit(EXIT_FAILURE);
  }
  return file;
}

PgmFile createStruct(FILE *ptrFile) {
  PgmFile imageStruct;
  fscanf(ptrFile, "%s", imageStruct.type);
  fscanf(ptrFile, "%d", &imageStruct.cols);
  fscanf(ptrFile, "%d", &imageStruct.lines);
  fscanf(ptrFile, "%d", &imageStruct.whiteColor);
  imageStruct.ptrFile = ptrFile;
  loadMatrix(&imageStruct);
  return imageStruct;
}

void loadMatrix(PgmFile *imageStruct) {
  imageStruct->matrix = alocateMatrix(imageStruct->cols, imageStruct->lines);
  int i = 0;
  int count = 1;
  while (fscanf(imageStruct->ptrFile, "%s", imageStruct->matrix[i]) != EOF) {
    count++;
    if (count == imageStruct->cols) {
      count = 1;
    }
    i++;
  }
}

char **alocateMatrix(int cols, int lines) {
  char **matrix = (char **)malloc((lines * cols) * sizeof(char *));
  if (matrix == NULL) {
    printf("Error allocating memory to 'bufferString'.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < lines * cols; i++) {
    matrix[i] = (char *)malloc(5 * sizeof(char));
    if (matrix[i] == NULL) {
      printf("Error allocating memory to 'bufferString'.\n");
      exit(EXIT_FAILURE);
    }
  }
  return matrix;
}

void freeMatrix(PgmFile *imageStruct) {
  for (int i = 0; i < imageStruct->lines * imageStruct->cols; i++) {
    free(imageStruct->matrix[i]);
  }
  free(imageStruct->matrix);
}

void compress(PgmFile imageStruct, FILE *outputFile) {
  fprintf(outputFile, "%s\n", "P8");
  fprintf(outputFile, "%d ", imageStruct.cols);
  fprintf(outputFile, "%d\n", imageStruct.lines);
  fprintf(outputFile, "%d\n", imageStruct.whiteColor);

  char previousValue[3];
  int count = 1;
  int cols = 1;
  int line = 1;
  int arraySize = imageStruct.cols * imageStruct.lines;

  strcpy(previousValue, imageStruct.matrix[0]);
  for (int i = 1; i < arraySize; i++) {
    if (strcmp(previousValue, imageStruct.matrix[i]) == 0) {
      count++;
    } else {
      writePixel(outputFile, previousValue, count);
      strcpy(previousValue, imageStruct.matrix[i]);
      count = 1;
    }
    cols++;

    if (cols == imageStruct.cols) {
      writePixel(outputFile, previousValue, count);
      fprintf(outputFile, "\n");
      if (line < imageStruct.lines) {
        strcpy(previousValue, imageStruct.matrix[i + 1]);
      }
      i++;
      count = 1;
      cols = 1;
      line++;
    }
  }
}

void writePixel(FILE *outputFile, char *value, int count) {
  if (count > 3) {
    fprintf(outputFile, "@ %s %d ", value, count);
  } else {
    for (int i = 0; i < count; i++) {
      fprintf(outputFile, "%s ", value);
    }
  }
}

void decompress(PgmFile imageStruct, FILE *outputFile) {
  fprintf(outputFile, "%s\n", "P2");
  fprintf(outputFile, "%d ", imageStruct.cols);
  fprintf(outputFile, "%d\n", imageStruct.lines);
  fprintf(outputFile, "%d\n", imageStruct.whiteColor);

  char previousValue[3];
  int cols = 0;
  int lines = 0;
  int i = 0;
  int arraySize = imageStruct.cols * imageStruct.lines;
  
  strcpy(previousValue, imageStruct.matrix[0]);
  while (lines < imageStruct.lines) {
    if (strcmp(imageStruct.matrix[i], "@") == 0) {
      for (int j = 0; j < atoi(imageStruct.matrix[i + 2]); j++) {
        fprintf(outputFile, "%s ", imageStruct.matrix[i + 1]);
        cols++;
      }
      i += 2;
      
    } else {
      fprintf(outputFile, "%s ", imageStruct.matrix[i]);
      cols++;
    }

    if (cols == imageStruct.cols) {
      fprintf(outputFile, "\n");
      if (lines < imageStruct.lines) {
        strcpy(previousValue, imageStruct.matrix[i + 1]);
      }
      cols = 0;
      lines++;
    }
    i++;
  }
  fclose(outputFile);
}