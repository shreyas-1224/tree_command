#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

#define TRUE 1
#define FALSE 0


int main(int argc , char * argv[])
{	

	queue q ;
	q_init(&q,500);

	int choice = 3 ;   // by default only working files
	
	fflush(stdin);
	
	printf("enter the choice and depth , enter 0 for no depth conditon : \n");
	printf("1)git files\t 2)only work files \n");
	
	scanf("%d" , &choice);
	tree root = create_node(argv[1]); 
	
	enqueue(&q , root);
	
	level_order(&q , root);
	
	if(root == NULL ){
		printf("failed to allocate memory.");
		return 1;
	}
	
	root->more_child = TRUE;	
	
	if(strcmp(argv[1] , "") == 0 ){
		root->child = create_tree( getcwd(0,0) , choice , &q ) ;
	}
	
	else{
		root->child = create_tree( argv[1] , choice , &q) ;
	}
	//level_order(&q , root); 
	display_tree(root  , choice , argv[2]);
	printf("\n\n");
	integer();
	printf("\n");
	
	return 0;
	
}
