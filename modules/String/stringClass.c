#include "stringClass.h"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

static String* split(String str, int index);
static void destroy(String* str);
static String concat(String str1, String str2);
static bool compare(String s1, String s2);
static String substring(String s, int start, int end);
static StringCollection slice(String s, const char token);
static bool contains(String s, String target);
static void format(String* s);
static int indexOf(String s, String target);

String stringCreate(char* data) {
    String string;
    char* stringData = malloc(sizeof(char) * (strlen(data) + 1)); // +1 for the null terminator
    strcpy(stringData, data);

    string.string = stringData;
    string.length = strlen(data);
    string.split = split;
    string.destroy = destroy;
    string.concat = concat;
    string.compare = compare;
    string.substring = substring;
    string.slice = slice;
    string.contains = contains;
    string.format = format;
    string.indexOf = indexOf;
    return string;
}



static String* split(String str, int I_index){
    size_t index = (size_t)I_index;
    if(index < 1){
        printf("%s\n", "Invalid index; split index must be >= 1");
        exit(1);
    }
    else if(index > str.length - 1){
        printf("%s\n", "Invalid index; split index is larger than str length");
        exit(1);
    }

    char* string1Data = malloc(sizeof(char) * index);
    for(size_t i = 0; i < index + 1; i++){
        string1Data[i] = str.string[i];
    }

    char* string2Data = malloc(sizeof(char) * (str.length - (size_t)index));
    for (size_t i = 0; i < str.length - (size_t)index; i++) {
        string2Data[i] = str.string[i + index];
    }

    String string1, string2;
    string1.string = string1Data; string2.string = string2Data;
    string1.length = (size_t)index; string2.length = (size_t)(str.length - index);

    String* strings = malloc(sizeof(String) * 2);
    strings[0] = string1; strings[1] = string2;
    return strings;
}

static void destroy(String* str){
    free(str->string);
}

static bool compare(String s1, String s2){
    if(s1.length != s2.length){
        return false;
    }
    
    for(size_t i = 0; i < s1.length; i++){
        if(s1.string[i] != s2.string[i]){
            return false;
        }
    }
    return true;
}

static String substring(String s, int start, int end){
    char* data = malloc(end - start);
    for(int i = start; i < end; i++){
        data[i - start] = s.string[i]; 
    }

    //add null terminator if it doesn't exist
    if(data[end - start - 1] != '\0'){
        data = realloc(data, end - start + 1);
        data[end - start] = '\0';
    }

    return stringCreate(data);
    free(data);
}


static StringCollection slice(String s, const char token){
    String* strings = NULL;
    int subCount = 0;
    int lastHit = 0;

    for(size_t i = 0; i < s.length; i++){
        if(s.string[i] == token){
            String sub = s.substring(s, lastHit, i);
            strings = realloc(strings, sizeof(String) * (subCount + 1));
            strings[subCount++] = sub;
            lastHit = i + 1;
        }
        else if(i == s.length - 1){
            String sub = s.substring(s, lastHit, s.length);
            strings = realloc(strings, sizeof(String) * (subCount + 1));
            strings[subCount++] = sub;
            lastHit = i + 1;
        }
    }
    StringCollection data = {strings, subCount};
    return data;
}


static String concat(String s1, String s2){
    char* stringData = malloc(s1.length);
    memcpy(stringData, s1.string, s1.length);

    stringData = realloc(stringData, s1.length + s2.length);
    strcat(stringData, s2.string);

    String returnStr = stringCreate(stringData);
    free(stringData);
    return returnStr;
}


static bool contains(String s, String target){
    if(target.length > s.length){
        return false;
    }
    for(size_t i = 0; i < s.length - target.length; i++){
        String sub = s.substring(s, i, i + target.length);
        if(sub.compare(sub, target)){
            return true;
        }
    }
    return false;
}


static int indexOf(String s, String target){
    if(target.length > s.length){
        return -1;
    }
    for(size_t i = 0; i < s.length - target.length; i++){
        String sub = s.substring(s, i, i + target.length);
        if(sub.compare(sub, target)){
            return (int)i;
        }
    }
    return -1;
}

static void format(String* s) {
    size_t j = 0;  // Index for the modified string
    for (size_t i = 0; i < s->length; i++) {
        char c = s->string[i];
        if (c != '\n') {
            // Copy characters other than newline
            s->string[j++] = c;
        }
    }

    // Null-terminate the modified string
    s->string[j] = '\0';

    // Update the length of the modified string
    s->length = j;
}
