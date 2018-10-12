#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include "API.h"


int main( int argc, char *argv[] )  {
   
   system("clear");
    printf("Mygraph OS 1st Assignment Fall 2018 \n");
   if( argc == 5 ) {
        printf("-i is-> %s\n", argv[1]);
        if(strcmp(argv[1],"-i") != 0 || strcmp(argv[3],"-o") != 0){
            printf("Expected this format ./mygraph -i inputfile -o outfile");
            printf("Please try again\n");
            return 1;
        }
        InputManager(argv[2]);
        OutputManager(argv[4]);
    //   printf("next is-> %s\n", argv[2]); // inpute file
    //   printf("next is-> %s\n", argv[4]); // output file
   }
   else {
      printf("You typed something wrong\n");
      printf("This format was expected: ./mygraph -i inputfile -o outfile\n");
      return 1;
   }
   return 0;
}