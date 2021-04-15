
// creating a n ary tree with child and sibling method ; 

typedef struct node {
	
	char* name;
	char* path;
	int  more_child;		
	struct node *child;	
	struct node *sibling;		// no more recursion after this ..
	
}node;


typedef node* tree ;


typedef struct queue{
	tree *a;
	int size;
	int rear,front,count;
}queue;

tree create_tree(char * , int , queue* q );
tree create_node(char* );
void display_tree(tree , int , char*);
int select_function(char*);
void print(tree , char*);
void integer();
void q_fy(tree , queue);

void q_init(queue*,int);
void enqueue(queue* , tree);
int q_isempty(queue);
int q_isfull(queue);
tree dequeue(queue*);

void level_order(queue * ,tree);

void b_sort(queue* , int , int);


