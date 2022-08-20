# include <stdio.h>
# include <stdlib.h>



//node
struct node{
	int data;
	struct node *next;
};

typedef struct node snode;

//queue
struct Queue{
    snode *f,*r;
};

typedef struct Queue queue;

int isEmpty(queue *pq){
    return ((pq->f==NULL)&&(pq->r==NULL));
}

//function for inserting data in queue
void insert(queue *pq,int d){
    snode *s=malloc(sizeof(snode*));//creating a temporary node to link to the queue
    s->data=d;
    s->next=NULL;
    if(isEmpty(pq))
        pq->r=pq->f=s;
    else
    {
        pq->r->next=s;
        pq->r=s;
    }

}

//function for removing data from queue
int rem(queue *pq){
    //underflow check
    if (isEmpty(pq))
    {
        printf("Underflow\n");
        return NULL;

    }
    else
    {
        int d=pq->f->data;
        snode *s=pq->f;
        pq->f=pq->f->next;

        if(pq->f==NULL)/*if front pointer is null, front has passed the rear pointer and
        queue must be empty, so we set rear to NULL*/
            pq->r=NULL;
        free(s);//freeing the memory

        return d;
    }
}

//main for function calls
void main()
{

    queue q;//declare a variable of queue type
    q.f=q.r=NULL;//initialize pointers

    int ch=1,d=0;
    char t='a';//temporary variable

    while (ch!=0)
    {
        printf("0. Exit\n");
        printf("1. Insert\n");
        printf("2. Remove\n");

        scanf("%d",&ch);
        scanf("%c",&t);

        switch(ch){
         case 0: continue; break;
         case 1: printf("Enter data:\n");
                scanf("%d",&d);
                scanf("%c",&t);
                insert(&q,d);
                break;
         case 2: printf("removing...\n");
                 printf("removed: %d\n",rem(&q));
                 break;
         default:printf("Invalid choice\n");break;
         };
         //displaying the queue
         printf("Displaying the queue\n");
         if(isEmpty(&q))
            printf("Empty queue\n");
         else
        {
            snode *s=q.f;
            while (s->next!=NULL)
            {
                printf("%d->",s->data);
                s=s->next;
            }
            printf("%d\n",s->data);
            printf("**********************\n");
        }
    }
}



