#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include <ctype.h>
#include "../HeaderFiles/FileHandling.h"

int InputManager(char *in){
    FILE* input = FileRead(in);
    if(input == NULL){
        // printf("Couldn't Load Input File\n");
        return 1;
    }
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
    if(output == NULL){
        // printf("Couldn't Load Output File\n");
        return 1;
    }
    return 0;
}

int InputDirector(int argc, char *argv[]){
    int i=1;
    char *input;
    char *output;
    char *buffer;
    size_t bufsize = 100;
    char *token;
    char **command;
    buffer = (char *)malloc(bufsize * sizeof(char));
    input = (char *)malloc(40);
    output = (char *)malloc(40);
    strcpy(input, "");
    strcpy(output, "");
    if( buffer == NULL){
        perror("Unable to allocate buffer");
        exit(1);
    }
    // check for input/ output fileNames
    while( i<argc ){
        if( strcmp(argv[i],"-i") == 0 ){
            if( i < argc -1 ){
                if(strcmp(argv[i+1], "-o") == 0){
                    printf("Input FIle Name not given after -i flag\n");
                    break; // continues to see if output file name given after -o
                }
                printf("Input File is: %s\n", argv[i+1]);
                strcpy(input, argv[i+1]);
                break;
            }
            else{
                printf("Input File Name not given after -i flag\n");
                // printf("Please Try again\n");
                // return(1); // If returned 1 , program should be terminated.
                break;
            }
            
        }
        i++;
    }
    i=1;
    while( i<argc ){
        if( strcmp(argv[i],"-o") == 0 ){
            if( i < argc -1 ){
                if(strcmp(argv[i+1], "-i") == 0){
                    printf("Output FIle Name not given after -o flag\n");
                    break; // continues without output file name
                }
                printf("Output File is: %s\n", argv[i+1]);
                strcpy(output, argv[i+1]);
                break;
            }
            else{
                printf("Output File Name not given after -o flag\n");
                // printf("Please Try again\n");
                // return(1); // If returned 1 , program should be terminated.
                break;
            }
           
        }
        i++;
    }
    // open Input Output Files and manage them
    if(strcmp(input, "") != 0){
        InputManager(input);
    }
    else printf("Input File Name for Graph not given\n");

    if(strcmp(output, "") != 0){
        OutputManager(output);
    }
    else printf("Output File Name for Printing Graph not given\n");
    
    // Managing Input from user here:
    while(1){
        printf("Type your Commands here:\n");
        i =0;
        command = (char **)malloc(10 * sizeof(char*)); // 10 words in each command allowed
        getline(&buffer,&bufsize,stdin);
        token = strtok(buffer, " ");

        while( token != NULL ) {
            command[i++] = token;
            token = strtok(NULL, " ");
        }
        
        if((strcmp(command[0], "i") == 0) || (strcmp(command[0], "insert") == 0)){
            if(i == 2){
                //insert Ni
                printf("Insert Ni-> %s,%s", command[0], command[1]);
            }
            else if(i == 4){
                //insert Ni Nj weight
                printf("Insert Ni-> %s,%s,%s,%s", command[0], command[1], command[2],command[3]);
            }
        }
        
        free(command);
    }

    //freeing out memory
    free(input);
    free(output);

    return 0;
}