typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

int recursive_tree_search(Node *root_node, int val);
void puts ( const char *str );
char *gets ( char *str );
int atoi (const char *str);
char *itoa ( int value, char *str, int base );

void exit(int code);