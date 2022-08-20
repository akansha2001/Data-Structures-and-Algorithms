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

    return (pq->r<pq->f);

}

//to obtain index of minimum element of queue
int peek(queue *pq){
    if (isEmpty(pq))
    {
        printf("Underflow\n");
        return NULL;

    }
    else
    {

        int minm=pq->items[pq->f];//initialise variable to determine minimum element of a queue

        int idx=pq->f;//to hold the index of minimum element in queue

        //to find location of minimum element by scanning the queue: complexity= O(n)
        for(int i=pq->f;i<=pq->r;i++){
            if(pq->items[i]<minm)
            {
                minm=pq->items[i];
                idx=i;
            }
        }
        return idx;

    }

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
    {
        int idx=peek(pq);//index of minimum element
        int minm=pq->items[idx];




        for(int i=idx;i>pq->f;i--)//shifting elements: complexity: O(n)
        {
            pq->items[i]=pq->items[i-1];
        }
        (pq->f)++;//update front pointer


        return minm;

    }
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

        }
        printf("**********************\n");
    }
}

