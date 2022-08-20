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

//function for inserting data in queue: same as linear queue
void insert(queue *pq,int d){
    snode *s=malloc(sizeof(snode*));//creating a temporary node to link to the queue
    s->data=d;
    s->next=NULL;
    if(isEmpty(pq))
        pq->r=pq->f=s;
    else
    {
        pq->r->next=s;
        pq->r=pq->r->next;//update rear pointer
    }

}

snode* peek(queue *pq)//returns pointer to minimum element of queue
{
    if (isEmpty(pq))
    {
        printf("Underflow\n");
        return NULL;

    }
    else
    {

        int minm=pq->f->data;//initialise variable to determine minimum element of a queue
        snode *s=pq->f;//node pointer to traverse the queue
        snode *p=s;//to hold the location of minimum element in queue

        //to find location of minimum element by scanning the queue: complexity= O(n)
        while(s!=NULL){
                if(s->data<minm)//new minimum was found
                {
                    //update
                    minm=s->data;
                    p=s;
                }

                s=s->next;//update
        }
        return p;

    }

}

//function for removing data from queue: violates FIFO property of linear queue as it removes elements on basis of priority
int rem(queue *pq){
    //underflow check
    if (isEmpty(pq))
    {
        printf("Underflow\n");
        return NULL;

    }
    else
    {

        snode *p=peek(pq);
        int minm=p->data;

        snode *s=pq->f;// for traversing the queue
        //to delete minimum element found in last step: complexity= O(n)
        //traversing the queue

        if(s==p)//first element of queue is the minimum element
        {
            pq->f=pq->f->next;//update the front pointer

        }
        else if(p==pq->r)//last element of queue is minimum element
        {
            while(s->next!=p)
            {
                s=s->next;
            }
            pq->r=s;//update rear pointer
            s->next=NULL;
        }
        else
        {
            while(s->next!=p)
            {
                s=s->next;
            }
            s->next=s->next->next;//updating the queue
        }

        if(pq->f==NULL)/*if front pointer is null, front has passed the rear pointer and
        queue must be empty, so we set rear to NULL*/
            pq->r=NULL;

        free(p);//freeing the memory

        return minm;
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



