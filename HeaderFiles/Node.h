
struct node {
    char *_id;
    struct edge *HeadEdges; // head of the linked list of edges
};

struct edge {
    int weight;
    struct node *target;
    struct edge *next;
};

typedef struct node node;
typedef struct edge edge;

node *NewNode(char * );
edge *InsertEdge(node *, node *, edge *, int );
int DeleteEdge(node *, node *, int );
int GetFirstEdge(edge *);
int GetLastEdge(edge *);
int	IsMemberOfList(edge *, int );
void PrintEdge(edge *);
