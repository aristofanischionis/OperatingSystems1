#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include "../HeaderFiles/FileHandling.h"

int InputManager(char *in){
    FILE* input = FileRead(in);
    int counter = 0;
    char word[255];
    char *source_id;
    char *target_id;
    int weight;
    source_id = (char *)malloc(40);
    target_id = (char *)malloc(40);
    while (fscanf(input,"%s",word)==1){
        switch(counter % 3) {
            case 0 :
                strcpy(source_id, word);
                break;
            case 1 :
                strcpy(target_id, word);
                break;
            case 2 :
                weight = atoi(word);
                break;
        }
        counter++;
        if( counter % 3 == 0) printf("exoume %s , %s, %d \n", source_id, target_id, weight);
    }
    return 0;
}

int OutputManager(char *out){
    FILE* output = FIleWrite(out);

    return 0;
}