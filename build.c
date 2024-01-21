#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char* getFileNameFromPath(char* path);

int main(){

    int fileCount = 3;
    int headerCount = 4;

    char* flags = "-c -ggdb -Wall -Wextra -I dist/include";
    char** modules = malloc(sizeof(char*) * fileCount);
    char** headers  = malloc(sizeof(char*) * headerCount);

    modules[0] = "modules/LinearAlgebra/matrix.c";
    modules[1] = "modules/Utils/utils.c";
    modules[2] = "modules/String/stringClass.c";

    headers[0] = "modules/LinearAlgebra/matrix.h";
    headers[1] = "modules/Utils/utils.h";
    headers[2] = "modules/String/stringClass.h";
    headers[3] = "modules/Colors/colors.h";

    char* fileOut = "build/";
    char* headerOut = "dist/include/headers/";



    //copy headers
    for(int i = 0; i < headerCount; i++){
        char* filePath = headers[i];
        char* fileName = getFileNameFromPath(filePath);

        printf("Copying %s\n", fileName);

        char* command = (char*)malloc(sizeof(char) * 200);
        sprintf(command, "cp %s %s%s", filePath, headerOut, fileName);
        printf("Running: %s\n", command);
        system(command);
        free(command);
    }
    
    printf("\n\n");


    //compile modules
    for(int i = 0; i < fileCount; i++){
        char* filePath = modules[i];
        char* fileName = getFileNameFromPath(filePath);
        fileName[strlen(fileName) - 1] = 'o';
        

        //printf("Compiling %s\n", fileName);

        char* command = (char*)malloc(sizeof(char) * 200);
        sprintf(command, "gcc %s %s %s %s%s", flags, filePath, "-o", fileOut, fileName);
        printf("Running: %s\n", command);
        system(command);
        free(command);
    }


    

    //compile lib
    printf("\n\nCompiling lib\n");
    char* command = (char*)malloc(sizeof(char) * 200);
    
    //example "ar cr dist/libCBase.a Build/matrix.o Build/utils.o Build/stringClass.o"
    sprintf(command, "ar cr dist/libCBase.a");
    for(int i = 0; i < fileCount; i++){
        char* filePath = modules[i];
        char* fileName = getFileNameFromPath(filePath);
        fileName[strlen(fileName) - 1] = 'o';
        sprintf(command, "%s %s%s", command, fileOut, fileName);
    }
    printf("Running: %s\n", command);
    system(command);

    //cp lib header
    printf("\n\nCopying lib header\n");
    char* command2 = (char*)malloc(sizeof(char) * 200);
    sprintf(command2, "%s", "cp src/CBase.h dist/include/CBase.h");
    printf("Running: %s\n", command2);
    system(command2);

    return 0;
} 


char* getFileNameFromPath(char* path){
    int numBackslashes = 0;
    char* fileName = NULL;
    for(int j = 0; path[j] != '\0'; j++){
        if(numBackslashes == 2){
            fileName = strdup(&path[j]);
            break;
        }
        if(path[j] == '/'){
            numBackslashes++;
        }
    }

    return fileName;
}
