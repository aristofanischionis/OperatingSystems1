#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 

FILE* FileRead (char *in){
    FILE * input;
    input = fopen (in, "r");
    if (input == NULL) {
        fprintf(stderr, "Can't open input file %s\n", in);
        return(NULL);
    }
    return input;
}

FILE* FIleWrite (char *out){
    FILE * output; 
    output = fopen (out, "w");
    if (output == NULL) {
        fprintf(stderr, "Can't open output file %s\n", out);
        return(NULL);
    }
    return output;
}