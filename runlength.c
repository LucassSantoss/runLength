#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE* openFile(const char *filename, const char *mode);

void pgmToPgmc(char *input_file, char *output_file);

void pgmcToPgm(char *input_file, char *output_file);

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *input_file = argv[1];
    char *output_file = argv[2];
    
    FILE *ptr_input = openFile(input_file, "r");
    FILE *ptr_output = openFile(output_file, "w+");

    char input_type[4]; // 2 caracteres + \n
    fscanf(ptr_input, "%s", input_type);
    printf("INPUT TYPE: %s\n", input_type);
    
    if(strcmp(input_type, "P2") == 0){
        pgmToPgmc(input_file, output_file);
    }

    if(strcmp(input_file, "P8") == 0){
        pgmcToPgm(input_file, output_file);
    }

    
}

FILE* openFile(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("Can't open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void pgmcToPgm(char *input_file, char *output_file){

}

void pgmToPgmc(char *input_file, char *output_file){
    
}