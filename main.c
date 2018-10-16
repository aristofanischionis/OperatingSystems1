#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>
#include "./HeaderFiles/HashTable.h"
#include "./HeaderFiles/API.h"

int main(int argc, char *argv[]){
   
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
        printf("next is-> %s\n", argv[2]); // inpute file
        printf("next is-> %s\n", argv[4]); // output file
    }
    else {
        printf("You typed something wrong\n");
        printf("This format was expected: ./mygraph -i inputfile -o outfile\n");
        return 1;
    }
    return 0;
// keys for the hash table
    // ht_hash_table *MyHash_Table = ht_new(); //Should make a hash table;
    // node * n1 = NewNode("Name of Node111", NULL);
    // node * n2 = NewNode("SWSTOOOOOOO", NULL);
    // edge * e = InsertEdge(n1, n2,NULL, 500);
    // edge * e1 = InsertEdge(n1, n2,e, 450);
    // edge * e2 = InsertEdge(n2, n1,NULL, 10);
    // edge * e3 = InsertEdge(n2, n1,e2, 100);
    // PrintEdge(e3);
    //     // PrintEdge(e);

    // ht_insert(MyHash_Table,"THIS IS A KEY", n1);
    // ht_insert(MyHash_Table,"THIS IS A KEY11", n2);
    // node* thisnode = ht_search(MyHash_Table, "THIS IS A KEY11");
    // printf("moy gurise to %s", thisnode->_id);
    // printf("edgessssss %d", thisnode->HeadEdges->_id);
    // return 0;
}