#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include "tree.h"

void file_properties(tree ,struct stat , char*);

#define   TRUE	1
#define   FALSE 0

int count ;		

int select_function(char* name){
	

	if(strcmp(name , "-a") == 0){
		return 0 ;
	}
	else if(strcmp(name , ".git") == 0)
		return 1 ;
		
	else if(strcmp(name , "work") == 0) 
		return 2;
	
}


struct node* create_node(char* n){

	struct node *newnode = (struct node * )malloc(sizeof(struct node ));
	if(newnode == NULL ){
		printf("failed to allocate memory . ");
		return NULL;
	}
	
	newnode->path = (char *)malloc(1000*sizeof(char));
	if(newnode->path == NULL){
		printf("try again");
	}
	newnode->name = n;
	strcpy(newnode->path,"");
	newnode->child = NULL;
	newnode->sibling = NULL;
	
	return newnode;
}



struct node* create_tree(char *root_name , int choice ) {
	
	
	
	DIR *dir = opendir(root_name);		// opening and assigning the pointer . 
	struct dirent *dr = NULL;
	
	tree root = NULL;
	tree temp = NULL;
	tree temp1 = NULL;
	
	char *name = (char *)malloc(1000*sizeof(char));
	
	
	// avoiding bus error with malloc
	

	if(dir == NULL){
	
		printf("\n failed to open the file ");
		//printf(" : %s",root_name);
		return NULL;
	}

	
	while((dr = readdir(dir)) != NULL)			// till we open the directories  .
	{		
	
			if(choice == 1){			
				
				if(strcmp((dr->d_name),".") == 0 || strcmp((dr->d_name),"..") == 0  &&  strcmp(dr->d_name , ".git") == 0) 
					temp = create_node(dr->d_name);
					
			
				else {
		
					temp = NULL;
					continue;	
			
				}
			
			}
			
				
			if(choice == 2){
				
				if(strcmp((dr->d_name),".") != 0 && strcmp((dr->d_name),"..") != 0  ||  strcmp(dr->d_name , ".git") == 0) 
					temp = create_node(dr->d_name);
			
				else {
			
					temp = NULL;
					continue;	
			
				}
			
			}	
			
			
			else if(choice == 3){
				
				if(strcmp((dr->d_name),".") != 0 && strcmp((dr->d_name),"..") != 0  &&  strcmp(dr->d_name , ".git") != 0
					&& !(isdigit(dr->d_name[0]))) {
					
					temp = create_node(dr->d_name);
					strcpy(temp->path,root_name);
					strcat(temp->path,"/");
					strcat(temp->path,dr->d_name);
					//printf("%s\n",temp->path);
					//printf("%s\n",temp->path);	
				}
			
				else {
			
					temp = NULL;
					continue;	
			
				}
			
			}
			
			if(temp1 != NULL)  
				temp1->sibling = temp;
			
			else
				root = temp;
			

			if((dr->d_type) == DT_DIR ) {			// if its a directory 
			
				temp->more_child = TRUE;
				strcpy(name,root_name);
				temp->child = create_tree((strcat((strcat(name,"/")),dr->d_name)),choice );
				strcpy(name,root_name);
			}
			
			else {
			
				temp->more_child = FALSE;
				temp->child = NULL;		
			}
		//printf("shreyas\n");
		temp1 = temp;
	}
	
	return root;
}

void display_tree(tree root  , int dep , char* opt ){
	
	
	
	char *s = "|------" ;		
	char *s1 = "|      " ;		
	
	tree temp = root;

	if(root == NULL)
		return;
	
	printf("\n");
	
	for(int i = 0;i < (count-1); i++) {
		
		printf("%s",s1);
	}
			
	if(count > 0){ 

		printf("%s",s);
	}
	

	//printf("%s",temp->name);
	if(strcmp(opt,"-l") == 0){
		if(temp->more_child == FALSE){
			int file = 0;
        		if((file = open(temp->path,O_RDONLY)) < -1)
            			return ;
 
    			struct stat fileStat;
    			if(fstat(file,&fileStat) < 0)    
        			return ;
 
    
 			printf("%s [",temp->name);
			printf("File Permissions: \t");
    			printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    			printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    			printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    			printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    			printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    			printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    			printf("]");
		}
		
		else{
			printf("%s",temp->name);
		}
	
	}		
	
	if(strcmp(opt ,"-s") == 0){
		if(temp->more_child == FALSE){
			int file = 0;
        		if((file = open(temp->path,O_RDONLY)) < -1){
            			printf("%s",temp->name);
            			return ;
            		}
 
    			struct stat fileStat;
    			if(fstat(file,&fileStat) < 0) {   
            			printf("%s",temp->name);
            			return ;
            		}
 
    
 			printf("%s  [",temp->name);
			printf(" File Size: %ld bytes",fileStat.st_size);
    			printf(" ]");
		}
		
		else{
			printf("%s",temp->name);
		}
	}
	
	if(strcmp(opt,"-t") == 0){
		
		if(temp->more_child == FALSE){
			struct stat fileStat ;
			
			if(stat(temp->path , &fileStat) >= 0){
				//******************************************************
				struct tm dt;

 	  			// Get file creation time in seconds and 
    				// convert seconds to date and time format
    				dt = *(gmtime(&fileStat.st_ctime));
    				printf("%s [ ",temp->name);
    				printf(" Created on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                              dt.tm_hour, dt.tm_min, dt.tm_sec);
                              printf(" ]");
                              

			       /* File modification time
			       dt = *(gmtime(&stats.st_mtime));
			       printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec); */
			       //******************************************************
			}
		
			else{
				printf("%s",temp->name);
			}	

		}
		
		else{
			printf("%s",temp->name);
		}
	}
	
	if(strcmp(opt,"-m") == 0){
		
		if(temp->more_child == FALSE){
			struct stat fileStat ;
			
			if(stat(temp->path , &fileStat) >= 0){
				//******************************************************
				struct tm dt;
    			/* File modification time  */
    				dt = *(gmtime(&fileStat.st_mtime));
    				printf("%s [",temp->name);
    				printf("Modified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon+1, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);
                               printf("]"); 
				//******************************************************
			}
		
			else{
				printf("%s",temp->name);
			}	

		}
		
		else{
			printf("%s",temp->name);
		}
	}
	
	if(temp->more_child == TRUE){
			
		count++;
		display_tree(temp->child , dep , opt);
		count--;
	}
	display_tree(temp->sibling , dep , opt);	

}


char* getpath(){
	
	char *buf;
	buf = (char *)malloc(100*sizeof(char));
	getcwd(buf,100);
	return buf ;
}

