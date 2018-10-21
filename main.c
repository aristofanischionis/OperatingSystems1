#include <stdio.h>
#include <stdlib.h> 
#include "./HeaderFiles/API.h"

int main(int argc, char *argv[]){
    system("clear");
    printf("Mygraph OS 1st Assignment Fall 2018 \n");
    if ( InputDirector(argc, argv) == 1 ) return 1;
    else return 0;
}