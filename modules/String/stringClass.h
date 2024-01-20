#ifndef STRINGCLASS_H
#define STRINGCLASS_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct String String;

typedef struct StringCollection{
    String* strings;
    int count;
} StringCollection;


typedef struct String{
    char* string;   
    size_t length;
    String*(*split)(String, int);
    void (*destroy)(String*);
    String(*concat)(String, String);
    bool(*compare)(String, String);
    String(*substring)(String, int, int);
    StringCollection(*slice)(String, const char);
    bool(*contains)(String, String);
    void(*format)(String*);
    int(*indexOf)(String, String);
} String;




String stringCreate(char* data);

void initThis();
//static String* split(String str, int index);



#endif //STRINGCLASS_H