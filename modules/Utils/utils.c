#include "utils.h"

bool isNumber(char c){
    return c >= '0' && c <= '9';
}

StringCollection loadFile(const String filename){
    FILE* file = fopen(filename.string, "r");
    int stringCount = 0;
    String* lines = NULL;
    if(file == NULL){
        printf("Error opening file: %s\n", filename.string);
        exit(1);
    }

    while(!feof(file)){
        char* line = malloc(sizeof(char) * 1000);
        fgets(line, 1000, file);

        String lineString = stringCreate(line);
        lineString.format(&lineString);
        String* linesTemp = realloc(lines, sizeof(String) * (stringCount + 1));
        if(linesTemp == NULL){
            printf("[Error] realloc failed\n");
            exit(1);
        }
        else{
            lines = linesTemp;
        }
        if(lines == NULL){
            printf("Error reallocating memory\n");
            exit(1);
        }
        lines[stringCount] = lineString;
        stringCount++;
        free(line);
    }

    StringCollection data = {lines, stringCount};
    return data;
}