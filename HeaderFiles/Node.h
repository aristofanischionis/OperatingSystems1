
struct node {
    char *_id;
    struct edge *HeadEdges; // head of the linked list of edges make sure to give &HeadofEdges
};

struct edge {
    int weight;
    struct node *target;
    struct edge *next;
    struct edge *prev;
}; // this is a Double Linked List

typedef struct node node;
typedef struct edge edge;

node *NewNode(char * );
int InsertEdge(edge** head_ref, int w, node *t); // place the edge in the linked list
edge *UpdateEdge(node *s, node *t, int w, int nw);
edge *SearchEdge(node *s, node *t, int w);
edge *SearchEdgeNoWeight(node *s, node *t);
edge *DeleteEdge(edge **head_ref, edge *del);
int DeleteEdges(edge** head_ref);
int DeleteEdgesFrom(node *n1, node *n2);
