# include <stdio.h>
# include <stdlib.h>

struct node{
	char data;
	struct node *next;
	struct node *prev;
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
int insert_beg(snode **head_ref, snode **tail_ref){

	char d,temp;
	printf("\nEnter the data to be inserted:\t");
	scanf("%c", &d);
	scanf("%c", &temp);
	snode *new_node = malloc(sizeof(snode));
	new_node->data=d;
	new_node->next=new_node->prev=NULL;

	if(isEmpty(head_ref)){

    		*head_ref = new_node;
    		(*head_ref)->next =(*head_ref)->prev= *head_ref;
    		*tail_ref=*head_ref;
	}
	else{

            (*tail_ref)->next=new_node;
    		new_node->prev=(*tail_ref);
            new_node->next=*head_ref;
            (*head_ref)->prev=new_node;
            *head_ref=new_node;


	}
	printf("\n Insertion successful" );
	return 0;
}


//inserting node at end
int insert_end(snode **head_ref, snode **tail_ref){
	char d,temp;
	printf("\nEnter the data to be inserted:\t");
	scanf("%c", &d);
	scanf("%c", &temp);
    snode *new_node = malloc(sizeof(snode));
	new_node->data=d;
	new_node->next=new_node->prev=NULL;
	if(isEmpty(head_ref)){

    		*head_ref = new_node;
    		(*head_ref)->next=(*head_ref)->prev = *head_ref;
    		*tail_ref=*head_ref;
	}
	else{
            (*tail_ref)->next=new_node;
            new_node->prev=*tail_ref;
            *tail_ref=new_node;
            (*tail_ref)->next=*head_ref;
            (*head_ref)->prev=*tail_ref;


	}

	printf("\n Insertion successful" );

}

 //inserting at any position
int insert_pos(snode **head_ref,snode **tail_ref){
	char d,temp;
    printf("\nEnter the data to be inserted:\t");
	scanf("%c", &d);
	scanf("%c", &temp);
    snode *new_node = malloc(sizeof(snode));
	new_node->data=d;
	new_node->next=new_node->prev=NULL;

	if(isEmpty(head_ref)){
    		printf("Empty list. Creating new list and entering data at first position\n");
    		*head_ref= new_node;
    		(*head_ref)->next =(*head_ref)->prev=*head_ref;
    		*tail_ref=*head_ref;
	}
	else{
    		snode *s=*head_ref;
            int pos,i=1;
            printf("Enter position to insert node at:\n");
            scanf("%d",&pos);
            scanf("%c", &temp);
            if(pos==1)
            {
                snode *s=*head_ref;
                while(s->next!=*head_ref)
                {
                    s=s->next;
                }
                s->next =new_node;
                new_node->prev=s;
                new_node->next=*head_ref;
                *head_ref=new_node;
            }
            else{

                    while( (s->next!=*head_ref) && (i<pos-1)){
                        s=s->next;
                        i+=1;
                    }
                    if(i==pos-1){
                        snode *t=s->next;
                        s->next=new_node;
                        new_node->prev=s;
                        new_node->next=t;
                        t->prev=new_node;
                        printf("\n Insertion successful");

                    }
                    else
                        printf("\n Position is out of bounds. Insertion failed.");
                }
            }
}
//deleting from any position
int del(snode **head_ref,snode **tail_ref){
	int pos;
	char temp;
	printf("\n Enter the position of the node to be deleted:");
	scanf("%d", &pos);
	scanf("%c",&temp);
	if(isEmpty(head_ref)){
    	printf("List does not exist. Node cannot be deleted");
	}
	else{
    	if(pos==1)//deleting the first node requires the last node to be linked to the new first node
            {
                 snode *t = *head_ref;//to be displayed
                (*head_ref) = (*head_ref)->next;
                (*tail_ref)->next=*head_ref;
                (*head_ref)->prev=*tail_ref;
                printf("\n Deletion successful. %c deleted from position %d",t->data,pos);
                free(t);

            }
        else{
            snode *s=*head_ref;
            int i=1;

            while( (s->next!=*head_ref) && (i<pos-1)){
                s=s->next;
                i+=1;
                }
            if(i==pos-1){
                snode *t=s->next;
                snode *a=s->next->next;
                s->next=a;
                a->prev=s;


                printf("\n Deletion successful. %c deleted from position %d",t->data,pos);
                free(t);
            }

            else
                printf("\n Position out of bounds. Deletion failed.");
        }
	}
}

//displaying the list
int display(snode **head_ref,snode **tail_ref){

	if (isEmpty(head_ref)){
    	printf("\n List is empty. Nothing to display.");
	}
	else{
        printf("\n Displaying list [forward]:\n");
		printf("\n *******************************\n");
		snode *s = *head_ref;
		while(s->next!=*head_ref){
                printf("%c ->",s->data);
                s=s->next;
			}
        printf("%c ",s->data);

        printf("\n *******************************\n");
        printf("\n Displaying list [backward]:\n");
		printf("\n *******************************\n");
		s = *tail_ref;
		while(s->prev!=*tail_ref){
                printf("%c ->",s->data);
                s=s->prev;
			}
        printf("%c ",s->data);

        printf("\n *******************************\n");
	}
	return 0;
}

int main(){
 	snode *head=malloc(sizeof(snode));
 	head=NULL;
 	snode *tail=malloc(sizeof(snode));
 	tail=NULL;
    //function calls
	insert_beg(&head,&tail);
	display(&head,&tail);
	insert_beg(&head,&tail);
	display(&head,&tail);
	insert_end(&head,&tail);
	display(&head,&tail);
    insert_end(&head,&tail);
    display(&head,&tail);
    insert_pos(&head,&tail);
    display(&head,&tail);
    insert_pos(&head,&tail);
    display(&head,&tail);
    del(&head,&tail);
    display(&head,&tail);
    del(&head,&tail);
    display(&head,&tail);



	return 0;
}

