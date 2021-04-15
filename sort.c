#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include  "tree.h"

void q_fy(tree t , queue q){

	tree temp , parent;
	queue q2 ;
	q_init(&q2 , 100);
	int q_count = 0 ;
	int q_count2 = -1 ;
	while(!(q_isempty(q))){
		temp = dequeue(&q);
		printf("%s\n",temp->name);
		
		/*
		temp = dequeue(&q);
		parent = temp ;
		if(temp->more_child == 0)
			continue;
		
		else{
			
			temp = temp->child ;
			while(temp){
			
				q_count2 ++ ;
				enqueue(&q2 , temp);
				temp = temp->sibling;
			}
			
			b_sort(&q2 , 0 , q_count2);
			
			tree temp3 ;
			temp3 = dequeue(&q2);
			parent->child = temp3;
			
			int k = 0 ;
			while(!(q_isempty(q2))){
				
				temp3->sibling = dequeue(&q2);
				temp3 = temp3->sibling ;
				if(q_isempty(q2)){
					temp3->sibling = NULL ;
					break ;
				}		
			}
			
				
		}*/	
	}
	
}



void b_sort(queue *q,int a , int b){			// b is index of last element.
	
	for(int i = a ; i< b ; i++){
		int min = i;
		
		for(int j = i+1 ;j < b+1 ; j++){
			
			if(strcmp(((*q).a[j])->name , ((*q).a[min])->name) < 0)
				min = j;
		}
		
		tree temp = (*q).a[i];
		(*q).a[i] = (*q).a[min];
		(*q).a[min] = temp;
		
	}
	
	return ;
}




void level_order(queue* q , tree root){

	enqueue(q , root);
	tree temp = root ;
	tree temp2 = NULL;
	int q_count = 0 ;
	int do_return = 1;
	
	if(temp->more_child == 0)
		return ;
	
	while(q->rear >= q_count){
		
		temp2 = ((*q).a[q_count])->child; 
		q_count++ ;
		
		if(temp2 != NULL){
			//printf("%s\n",temp2->name);
			enqueue(q , temp2);	
			do_return = 1;		
		}
		
		else{
			do_return = 0;
		}
		
		if(do_return){
			if(temp2->sibling != NULL ){
			
				temp2 = temp2->sibling ;
				enqueue(q , temp2);
			}
		}
		//enqueue(q , temp);
		
	}
	
	//while(!(q_isempty(*q))){
		
		//printf("%s\n",(dequeue(q))->name);
	//}
}

















