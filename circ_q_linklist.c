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

//underflow check
int isEmpty(queue *pq){
    return ((pq->f==NULL)&&(pq->r==NULL));
}

//function for inserting data in queue
void insert(queue *pq,int d){

    //dynamic implementation does not require us to check for overflow. This is an advantage over static implementation
    snode *s=malloc(sizeof(snode*));//creating a temporary node to link to the queue
    s->data=d;
    s->next=NULL;
    if(isEmpty(pq))
    {
        pq->r=pq->f=s;
        pq->r->next=pq->f;//update rear pointer
    }
    else
    {
        pq->r->next=s;
        pq->r=s;
        pq->r->next=pq->f;//update rear pointer
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
        if(pq->f->next==pq->f)/*if front node pointer points to itself, queue must be empty after this function is executed.
            Set both pointers to NULL to denote empty queue. This condition is different from the one seen in linear queue.*/
            pq->r=pq->f=NULL;
        else
        {
            snode *s=pq->f;
            pq->f=pq->f->next;
            pq->r->next=pq->f;//update rear pointer
            free(s);//freeing the memory
        }



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
            while (s!=q.r)
            {
                printf("%d->",s->data);
                s=s->next;
            }
            printf("%d\n",q.r->data);

        }
        printf("**********************\n");
    }
}



