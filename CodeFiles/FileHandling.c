#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 

FILE* FileRead (in){
    FILE * input;
    input = fopen (in, "r");
    if (input == NULL) {
        fprintf(stderr, "Can't open input file %s\n", in);
        exit(1);
    }
    return input;
}

FILE* FIleWrite (out){
    FILE * output; 
    output = fopen (out, "w");
    if (output == NULL) {
        fprintf(stderr, "Can't open output file %s\n", out);
        exit(1);
    }
    return output;
}