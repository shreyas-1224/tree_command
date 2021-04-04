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
	int choice = 3 ;   // by default only working files
	
	fflush(stdin);
	
	printf("enter the choice and depth , enter 0 for no depth conditon : \n");
	printf("1)all files\t 2)git files\t 3)only work files \n");
	
	scanf("%d" , &choice);
	tree root = create_node(argv[1]); 
		
	if(root == NULL ){
		printf("failed to allocate memory.");
		return 1;
	}
	
	root->more_child = TRUE;	
	
	if(strcmp(argv[1] , "") == 0 ){
		root->child = create_tree( getcwd(0,0) , choice  ) ;
	}
	
	else{
		root->child = create_tree( argv[1] , choice ) ;
	}
	 
	display_tree(root  , choice , argv[2]);
	printf("\n");
	return 0;
	
}
