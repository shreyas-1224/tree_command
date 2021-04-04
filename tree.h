
// creating a n ary tree with child and sibling method ; 

typedef struct node {
	
	char* name;
	char* path;
	int  more_child;		
	struct node *child;	
	struct node *sibling;		// no more recursion after this ..
}node;


typedef node* tree ;

tree create_tree(char * , int  );
tree create_node(char* );
void display_tree(tree , int , char*);
int select_function(char*);
void print(tree , char*);
char* getpath();
