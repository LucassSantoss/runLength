#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int cols;
  int lines;
  int whiteColor;
  FILE *ptrFile;
  char type[3];
  char **matrix;
} PgmFile;

FILE *openFile(const char *filename, const char *mode);

void compress(PgmFile imageStruct, char outputName[]);

void writeLineComp(FILE *outputFile, char *value, int count);

void decompress(PgmFile imageStruct, char outputName[]);

void loadMatrix(PgmFile *imageStruct);

char **alocateMatrix(int cols, int lines);

PgmFile createStruct(FILE *ptrFile);

void freeMatrix(PgmFile imageStruct);

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <inputFile> <outputFile>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  char *inputName = argv[1];
  char *outputName = argv[2];

  FILE *inputFile = openFile(inputName, "r");

  PgmFile imageStruct = createStruct(inputFile);

  if (strcmp(imageStruct.type, "P2") == 0) {
    compress(imageStruct, outputName);
    printf("Converting P2 > P8\n");
  }

  if (strcmp(imageStruct.type, "P8") == 0) {
    decompress(imageStruct, outputName);
    printf("Converting P8 > P2\n");
  }

  freeMatrix(imageStruct);
  fclose(inputFile);
}

FILE *openFile(const char *filename, const char *mode) {
  FILE *file = fopen(filename, mode);
  if (file == NULL) {
    printf("Can't open file: %s\n", filename);
    exit(EXIT_FAILURE);
  }
  return file;
}

char **alocateMatrix(int cols, int lines) {
  char **matrix = (char **)malloc((lines * cols) * sizeof(char *));

  for (int i = 0; i < lines * cols; i++) {
    matrix[i] = (char *)malloc(4 * sizeof(char));
  }
  return matrix;
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

void compress(PgmFile imageStruct, char outputName[]) {
  FILE *outputFile = openFile(outputName, "w+");
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
      writeLineComp(outputFile, previousValue, count);
      strcpy(previousValue, imageStruct.matrix[i]);
      count = 1;
    }
    cols++;

    if (cols == imageStruct.cols) {
      writeLineComp(outputFile, previousValue, count);
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
  fclose(outputFile);
}

void writeLineComp(FILE *outputFile, char *value, int count) {
  if (count > 3) {
    fprintf(outputFile, "@ %s %d ", value, count);
  } else {
    for (int i = 0; i < count; i++) {
      fprintf(outputFile, "%s ", value);
    }
  }
}

void decompress(PgmFile imageStruct, char outputName[]) {
  FILE *outputFile = openFile(outputName, "w+");
  fprintf(outputFile, "%s\n", "P2");
  fprintf(outputFile, "%d ", imageStruct.cols);
  fprintf(outputFile, "%d\n", imageStruct.lines);
  fprintf(outputFile, "%d\n", imageStruct.whiteColor);

  int cols = 0;
  int lines = 0;
  int i = 0;

  while (lines < imageStruct.lines) {
    if (strcmp(imageStruct.matrix[i], "@") == 0) {
      for (int j = 0; j < atoi(imageStruct.matrix[i + 2]); j++) {
        if (cols + 1 == imageStruct.cols) {
          fprintf(outputFile, "%s", imageStruct.matrix[i + 1]);
        } else {
          fprintf(outputFile, "%s ", imageStruct.matrix[i + 1]);
        }
        cols++;
      }
      i += 2;
    } else {
      if (cols + 1 == imageStruct.cols) {
        fprintf(outputFile, "%s", imageStruct.matrix[i + 1]);
      } else {
        fprintf(outputFile, "%s ", imageStruct.matrix[i + 1]);
      }
      cols++;
    }

    if (cols == imageStruct.cols) {
      fprintf(outputFile, "\n");
      cols = 0;
      lines++;
    }
    i++;
  }
  fclose(outputFile);
}

void freeMatrix(PgmFile imageStruct) {
  for (int i = 0; i < imageStruct.lines; i++) {
    free(imageStruct.matrix[i]);
  }
}
