# include <stdio.h>
# include <stdlib.h>


/*
Breadth First Search (BFS):

Given a graph G=(V,E) and a distinguished source vertex s, breadth first search explores the edges of G to find every vertex that is reachable from s

Principle: the algorithm discovers all vertices at distance k from s, before discovering any vertices at distance k+1

Strategy: BFS "colors" each vertex white, gray or black. Initially, all vertices are white. When a vertex is encountered (discovered) for the first
time, it becomes non-white. All vertices adjacent to a black vertex have been discovered, but this is not true for a gray vertex.

BFS Tree: whenever a white vertex v is discovered while scanning the adjacency list of an already discovered vertex u, the vertex v and the edge (u,v)
are added to the BFS tree. Parent of v is u.

The distance from the source to any vertex u is stored in d[u]

Complexity: O(V+E)
*/


//a series of helper functions to form the queue required to perform breadth first search on the given graph

//structure for a single node of the queue
struct node{
	int data;//data of int type to be stored in the node. This may be char / float / etc depending on user preference
	struct node *next;//pointer to the next node. Has datatype struct node as well
};
//end of struct node

typedef struct node snode;//to make declaration easier

//structure for user defined datatype: queue
struct Queue{
    snode *f,*r;//front and rear pointers of user defined datatype 'snode'
};
//end of struct Queue

typedef struct Queue queue;//to make declaration easier

//user defined data type for undirected graph
struct Graph{
    int V;//number of vertices
    int *adj;//2D (symmetrical) adjacency matrix to store the information about the edges
};

typedef struct Graph graph;//to make declaration easier

int isEmpty(queue *pq)//function to check if queue is empty. Receives pointer to the queue as parameter
{
    return ((pq->f==NULL)&&(pq->r==NULL));//if both front and rear pointers are NULL, the queue must be empty
}
//end of isEmpty()

//function that allocates a new node with the given data and sets next pointer to NULL
//returns the created node to the calling function
snode* newNode(int data)
{
    snode* node=(snode*)malloc(sizeof(snode));//memory allocation
    node->data=data;
    node->next=NULL;

    return node;
}
//end of newNode()

void enqueue(queue *pq,int d)//function for inserting data in queue. Receives pointer to the queue and data to be inserted
//as parameters
{
    snode *s=newNode(d);//creating a temporary node to link to the queue

    if(isEmpty(pq))//for empty queue, insert the node and assign 's' to front and rear
        pq->r=pq->f=s;
    else//non empty queue
    {
        pq->r->next=s;//insert at rear of queue
        pq->r=s;//update rear pointer
    }

}
//end of enqueue()

//function for removing data from queue
int dequeue(queue *pq)
{
    //underflow check: if queue is empty
    if (isEmpty(pq))
    {
        printf("Underflow\n");
        return NULL;

    }
    else//non empty queue
    {
        int d=pq->f->data;//data must be removed from front
        snode *s=pq->f;//node to be removed
        pq->f=pq->f->next;//update front pointer

        if(pq->f==NULL)//if front pointer is null, front has passed the rear pointer and
        //queue must be empty, so we set rear to NULL
            pq->r=NULL;


        free(s);//freeing the memory

        return d;
    }
}
//end of dequeue()

void display(queue *pq)//function to print the queue
{
    printf("\nDisplaying the queue\n");
     if(isEmpty(pq))
        printf("Empty queue\n");
     else
    {
        int u=0;
        snode *s=pq->f;
        while (s!=pq->r)//traversing the queue from front to rear
        {
            printf("%d->",s->data);
            s=s->next;
        }
        u=s->data;
        printf("%d\n",s->data);
    }
}
//end of display()

//end of helper functions

void BFS(graph G, int s)//function to perform breadth first search for given number of vertices V
//and edges represented by adjacency matrix adj
//s is the root or starting point
{
    //for ease of computation we assume the vertices are 0,1,2,...,V

    int *color=(int*)calloc(G.V,sizeof(int));//int array to store color of each vertex

    //white:0
    //gray:1
    //black:2

    int *d=(int*)calloc(G.V,sizeof(int));//int array to store distance of each vertex from root

    //d=0 for s, 1 for next adjacent vertex and so on

    int *parent=(int*)calloc(G.V,sizeof(int));//int array to store parent of each vertex

    int *bfs=(int*)calloc(G.V,sizeof(int));//for the final search result

    int pos=-1;//to keep track of the position till which bfs has been filled

    //initialization

    //initialization of all vertices besides the root

    for(int i=0;i<G.V;i++)
    {
        if(i!=s)
        {
            color[i]=0;//white
            d[i]=G.V+1;//initialize with a large distance which is not feasible
            parent[i]=G.V+1;//parent is not known yet, hence we assign an out of bounds value
        }
    }

    //initialize root

    color[s]=1;//gray
    d[s]=0;
    parent[s]=G.V+1;//has no parent so we store a large value- outside of array bounds- in it

    //initialize the queue

    queue Q;//declare a variable of queue type
    Q.f=Q.r=NULL;//initialize pointers

    //end of initialization

    int u=0,v=0;

    enqueue(&Q,s);//insert root into queue

    printf("\n\n");

    while(!isEmpty(&Q))
    {
        display(&Q);

        u=dequeue(&Q);

        //print the details for the vertex being explored

        printf("\nExploring vertex: %d \n",u);

        if(parent[u]==(G.V+1))
            printf("Parent: NIL\n");
        else
            printf("Parent: %d\n",parent[u]);

        printf("Distance from root: %d\n",d[u]);

        if(color[u]==0)
            printf("Color: White\n");
        else if(color[u]==1)
            printf("Color: Gray\n");
        else
            printf("Color: Black\n");

        pos+=1;
        bfs[pos]=u;

        for(v=0;v<G.V;v++)
        {
            if(*(G.adj+u*G.V+v)!=0)//edge (u,v) exists
            {
                if(color[v]==0)//if white, ie undiscovered
                {
                    color[v]=1;//assign gray
                    d[v]=d[u]+1;//distance from root
                    parent[v]=u;

                    enqueue(&Q,v);//insert into queue
                }
            }
        }

        color[u]=2;//assign black, as all adjacent vertices have now been discovered


    }

    //print the final result
    printf("\n***********************************\n");

    printf("\nFinal BFS result:\n");

    for(int i=0;i<pos;i++)
        printf("%d, ",bfs[i]);

    printf("%d\n",bfs[pos]);

    printf("\n***********************************\n");


    printf("\nBreadth first search tree:\n\n");//printing the search tree with levels to denote the parents of vertices

    for(int i=0;i<=d[u];i++)//d[u] currently stores the maximum distance from the root
    {
        printf("Level %d:  ",i);
        for(int j=0;j<=pos;j++)
        {
            if(d[bfs[j]]==i)
                printf("%d  ",bfs[j]);
        }
        printf("\n");
    }

    printf("\n***********************************\n");

}
//end of BFS()

//main for function calls
void main()
{
    graph G;//declare a variable G of user defined datatype graph

    printf("Enter number of vertices:\n");
    scanf("%d",&G.V);

    G.adj=(int*)calloc(G.V*G.V,sizeof(int));//memory allocation

    int ch=0;//user's choice for whether or not an edge will exist

    //fill in values for
    for(int i=0;i<G.V;i++)
    {
        *(G.adj+i*G.V+i)=0;//no edge from i to i th vertex
        for(int j=i+1;j<G.V;j++)
        {
            printf("Edge (%d,%d)? (Y:1/N:0)\n",i,j);
            scanf("%d",&ch);

            //ch==0 means there is no edge between i and j th vertices
            //any non zero value of ch implies that an edge exists between the i and j th vertices and it will store '1'
            //irrespective of the user entry, as shown below

            *(G.adj+i*G.V+j)=*(G.adj+i+j*G.V)=(ch!=0);//symmetrical matrix
        }
    }

    printf("\nDisplaying the adjacency matrix\n\n");
    for(int i=0;i<G.V;i++)
    {
        for(int j=0;j<G.V;j++)
            printf("%d ",*(G.adj+i*G.V+j));
        printf("\n");
    }


    int s;
    printf("\nEnter root node\n");//the starting point of the graph: take input from user
    scanf("%d",&s);

    BFS(G,s%G.V);//in case user enters a value out of bounds, we will still get a valid output if we take the remainder on dividing
    //user entry 's' by 'V'. If 0<=s<V, s%V==s

}
//end of main()



