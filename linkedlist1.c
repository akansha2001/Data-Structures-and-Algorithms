# include <stdio.h>
# include <stdlib.h>

struct node{
	char data;
	struct node *next;
};

typedef struct node snode;

//checking for underflow
int isEmpty(snode **head_ref)
{
	if(*head_ref == NULL)
    	return 1;

	else
    	return 0;

}


//insert node at beginning
int insert_beg(snode **head_ref){

	char d,temp;
	printf("\nEnter the data to be inserted:\t");
	scanf("%c", &d);
	scanf("%c", &temp);
	snode *new_node = malloc(sizeof(snode));
	new_node->data=d;
	new_node->next=NULL;

	if(isEmpty(head_ref)){

    		*head_ref = new_node;
    		(*head_ref)->next = NULL;
	}
	else{
    		new_node->next =*head_ref;
    		(*head_ref) = new_node;


	}
	printf("\n Insertion successful" );
	return 0;
}


//inserting node at end
int insert_end(snode **head_ref){
	char d,temp;
	printf("\nEnter the data to be inserted:\t");
	scanf("%c", &d);
	scanf("%c", &temp);
    snode *new_node = malloc(sizeof(snode));
	new_node->data=d;
	new_node->next=NULL;
	if(isEmpty(head_ref)){

    		*head_ref = new_node;
    		(*head_ref)->next = NULL;
	}
	else{
            snode *s=*head_ref;
            while(s->next!=NULL){
                s=s->next;
            }
            s->next=new_node;



	}

	printf("\n Insertion successful" );

}

 //inserting at any position
int insert_pos(snode **head_ref){
	char d,temp;
    printf("\nEnter the data to be inserted:\t");
	scanf("%c", &d);
	scanf("%c", &temp);
    snode *new_node = malloc(sizeof(snode));
	new_node->data=d;
	new_node->next=NULL;

	if(isEmpty(head_ref)){
    		printf("Empty list. Creating new list and entering data at first position\n");
    		*head_ref= new_node;
    		(*head_ref)->next =NULL;
	}
	else{
    		snode *s=*head_ref;
            int pos,i=1;
            printf("Enter position to insert node at:\n");
            scanf("%d",&pos);
            scanf("%c", &temp);
            if(pos==1)
            {
                new_node->next=*head_ref;
                *head_ref=new_node;
            }
            else{

                    while( (s->next!=NULL) && (i<pos-1)){
                        s=s->next;
                        i+=1;
                    }
                    if(i==pos-1){
                        snode *t=s->next;
                        s->next=new_node;
                        s->next->next=t;
                        printf("\n Insertion successful");

                    }
                    else
                        printf("\n Position is out of bounds. Insertion failed.");
                }
            }
}
//deleting from any position
int del(snode **head_ref){
	int pos;
	char temp;
	printf("\n Enter the position of the node to be deleted:");
	scanf("%d", &pos);
	scanf("%c",&temp);
	if(isEmpty(head_ref)){
    	printf("List does not exist. Node cannot be deleted");
	}
	else{
    	if(pos==1){
    		 snode *t = *head_ref;
    		(*head_ref) = (*head_ref)->next;
    		printf("\n Deletion successful. %c deleted from position %d",t->data,pos);
    		free(t);

            }
        else{
            snode *s=*head_ref;
            int i=1;

            while( (s->next!=NULL) && (i<pos-1)){
                s=s->next;
                i+=1;
                }
            if(i==pos-1){
                snode *t=s->next;
                s->next=s->next->next;

            printf("\n Deletion successful. %c deleted from position %d",t->data,pos);
            free(t);
            }

            else
                printf("\n Position out of bounds. Deletion failed.");
        }
	}
}

//displaying the list
int display(snode **head_ref){

	if (isEmpty(head_ref)){
    	printf("\n List is empty. Nothing to display.");
	}
	else{
        printf("\n Displaying list:\n");
		printf("\n *******************************\n");
		snode *s = *head_ref;
		while(s->next!=NULL){
                printf("%c ->",s->data);
                s=s->next;
			}
        printf("%c ",s->data);

        printf("\n *******************************\n");
	}
	return 0;
}

int main(){
 	snode *head=malloc(sizeof(snode));
 	head=NULL;
    //function calls
	insert_beg(&head);
	display(&head);
	insert_beg(&head);
	display(&head);
	insert_end(&head);
	display(&head);
    insert_end(&head);
    display(&head);
    insert_pos(&head);
    display(&head);
    insert_pos(&head);
    display(&head);
    del(&head);
    display(&head);
    del(&head);
    display(&head);


	return 0;
}

