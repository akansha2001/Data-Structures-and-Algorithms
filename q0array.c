# include <stdio.h>
# include <stdlib.h>

#define MAX 5

//queue
struct Queue{
    int items[MAX];
    int f,r;
};

typedef struct Queue queue;

int isEmpty(queue *pq){

    return (pq->r<pq->f);

}

//function for inserting data in queue
void insert(queue *pq, int d){
    if (pq->r==MAX-1)//static implementation: overflow check
        printf("Overflow\n");
    else
        pq->items[++(pq->r)]=d;
}


//function for removing data from queue
int rem(queue *pq){
    if(isEmpty(pq))
    {
        printf("Queue underflow\n");
        return NULL;
    }

    else
        return pq->items[(pq->f)++];
}

//main for function calls
void main()
{
    queue q;
    q.f=0;
    q.r=-1;
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
         printf("\nFront:%d\n",q.f);
         printf("Rear:%d\n\n",q.r);
         if(isEmpty(&q))
            printf("Empty queue\n");
         else
        {
            int i=0;

            for( i=q.f;i<q.r;i++)
            {
                if(i==MAX)
                    i=0;
                printf("%d ->",q.items[i]);
            }
        printf("%d\n",q.items[i]);
        printf("**********************\n");
        }
    }
}

