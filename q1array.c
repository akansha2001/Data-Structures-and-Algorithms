# include <stdio.h>
# include <stdlib.h>

#define MAX 5

//queue
struct Queue{
    int items[MAX];
    int f,r;
};

typedef struct Queue queue;

//underflow check
int isEmpty(queue *pq){

    return (pq->r==pq->f);

}

//to insert a value into the queue
void insert(queue *pq, int d){

    //update the rear pointer and then proceed to check for overflow
    if (pq->r==MAX-1)
        pq->r=0;
    else
        (pq->r)++;

    //static representation of queue: we must check for overflow

    if (pq->r==pq->f)//since conditions for underflow and overflow are identical, we deal with it by sarcrifizing one element
    {
        printf("Queue overflow\n");

        //change back the rear pointer if there is overflow
        if (pq->r==0)
            pq->r=MAX-1;
        else
            (pq->r)--;
    }
    else
        pq->items[pq->r]=d;
}

//to remove a value from the queue
int rem(queue *pq){
    if(isEmpty(pq))
    {
        printf("Queue underflow\n");
        return NULL;
    }

    else
    {
        //updating the front pointer. In this implementation, front pointer points to location before the front of the queue
        if (pq->f==MAX-1)
            pq->f=0;
        else
            pq->f++;

        return (pq->items[pq->f]);
    }
}



void main()
{
    queue q;
    q.f=q.r=MAX-1;
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
            printf("\nEmpty queue\n");
         else
        {


            int i=0;
            if (q.f==MAX-1)
                i=0;
            else
                i=q.f+1;

            while(i!=q.r)
            {

                printf("%d ->",q.items[i]);
                i++;
                if(i==MAX)
                    i=0;
            }
        printf("%d\n",q.items[i]);
        printf("**********************\n");
        }
    }
}

