#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include <ctype.h>
#include "../HeaderFiles/FileHandling.h"
#include "../HeaderFiles/Repository.h"

int InputManager(ht_hash_table* ht, char *in){
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
        if( counter % 3 == 0) InsertNodesEdge(ht, source_id, target_id, weight);
    }
    fclose(input);
    return 0;
}

int OutputManager(ht_hash_table* ht, char *out){
    FILE* output = FIleWrite(out);
    if(output == NULL){
        // printf("Couldn't Load Output File\n");
        return 1;
    }
    // ht_print(ht);
    // just changed printf->fprintf
    int i =0 ;
    while(i < ht->base_size){
        if(ht->nodes[i] != NULL){
            fprintf(output,"|%s|\n", ht->nodes[i]->_id);
            edge *temp = ht->nodes[i]->HeadEdges;
            while(temp != NULL){   
                fprintf(output,"\t -%d->|%s|\n", temp->weight, temp->target->_id);
                temp = temp->next;
            }
        }
        i++;
    }
    fclose(output);
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
    char *pos;
    buffer = (char *)malloc(bufsize * sizeof(char));
    input = (char *)malloc(40);
    output = (char *)malloc(40);
    strcpy(input, "");
    strcpy(output, "");
    if( buffer == NULL){
        perror("Unable to allocate buffer\n");
        exit(1);
    }
    //setting up env here
    ht_hash_table *MyHash_Table = ht_new(); //Should make a hash table;
    if(MyHash_Table == NULL){
        perror("Unable to allocate Hash Table\n");
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
        InputManager(MyHash_Table, input);
    }
    else printf("Input File Name for Graph not given\n");

    if(strcmp(output, "") == 0) printf("Output File Name for Printing Graph not given\n");
    // if(strcmp(output, "") != 0){
    //     OutputManager(MyHash_Table, output);
    // }
    // else printf("Output File Name for Printing Graph not given\n");
    
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
        // Analyzing the command given by user
        switch(i){
            case 1:
                // one argument given
                if ((pos=strchr(command[0], '\n')) != NULL) *pos = '\0';
                if((strcmp(command[0], "e") == 0) || (strcmp(command[0], "exit") == 0)){ 
                    //exits program
                    if(strcmp(output, "") != 0) OutputManager(MyHash_Table, output);
                    // else printf("\t- No Output File Name is given\n");
                    printf("\t- exit program\n");
                    // ht_print(MyHash_Table);
                    return 0;
                }
                else fprintf(stderr, "Unknown Command Starting with:%s \n",command[0]);
                break;
            case 2:
                // two arguments given
                if((strcmp(command[0], "i") == 0) || (strcmp(command[0], "insert") == 0)){
                    //insert Ni
                    // printf("Insert Ni-> %s,%s\n", command[0], command[1]);
                    InsertNode(MyHash_Table, command[1]);
                }
                else if((strcmp(command[0], "d") == 0) || (strcmp(command[0], "delete") == 0)){
                    //Delete Ni
                    // printf("Delete Ni-> %s,%s\n", command[0], command[1]);
                    DeleteNode(MyHash_Table, command[1]);
                }
                else if((strcmp(command[0], "r") == 0) || (strcmp(command[0], "receiving") == 0)){
                    //Receiving Ni
                    printf("Receiving Ni-> %s,%s\n", command[0], command[1]);
                }
                else if((strcmp(command[0], "c") == 0) || (strcmp(command[0], "circlefind") == 0)){
                    //circlefind Ni
                    printf("circlefind Ni-> %s,%s\n", command[0], command[1]);
                }
                else fprintf(stderr, "Unknown Command Starting with: %s \n",command[0]);
                break;
            case 3:
                // three arguments given
                if((strcmp(command[0], "f") == 0) || (strcmp(command[0], "findcircles") == 0)){
                    //findcircles Ni k
                    printf("findcircles Ni k-> %s,%s,%s\n", command[0], command[1], command[2]);
                }
                else fprintf(stderr, "Unknown Command Starting with: %s \n",command[0]);
                break;
            case 4:
                //four arguments given
                if((strcmp(command[0], "n") == 0) || (strcmp(command[0], "insert") == 0)){
                    //insert Ni Nj weight
                    // printf("Insert Ni-> %s,%s,%s,%s\n", command[0], command[1], command[2],command[3]);
                    int w = atoi(command[3]);
                    InsertNodesEdge(MyHash_Table, command[1], command[2], w);
                }
                else if((strcmp(command[0], "l") == 0) || (strcmp(command[0], "delete") == 0)){
                    // Delete Ni Nj weight
                    // printf("Delete Ni-> %s,%s,%s,%s\n", command[0], command[1], command[2],command[3]);
                    int w = atoi(command[3]);
                    DeleteNodesEdge(MyHash_Table, command[1], command[2], w);
                }
                else if((strcmp(command[0], "t") == 0) || (strcmp(command[0], "traceflow") == 0)){
                    // Traceflow Ni Nj l
                    printf("Traceflow Ni-> %s,%s,%s,%s\n", command[0], command[1], command[2],command[3]);
                }
                else fprintf(stderr, "Unknown Command Starting with: %s \n",command[0]);
                break;
            case 5:
                //five arguments given
                if((strcmp(command[0], "m") == 0) || (strcmp(command[0], "modify") == 0)){
                    //Modify Ni Nj weight nweight
                    printf("Modify Ni Nj weight nweight-> %s,%s,%s,%s,%s\n", command[0], command[1], command[2],command[3],command[4]);
                }
                else fprintf(stderr, "Unknown Command Starting with: %s \n",command[0]);
                break;
            default:
                fprintf(stderr,"Unknown Command given with %d words\n", i);
               
        }
        

        free(command);
    }

    //freeing out memory
    free(input);
    free(output);

    return 0;
}