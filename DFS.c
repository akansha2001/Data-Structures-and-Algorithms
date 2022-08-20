 # include <stdio.h>
# include <stdlib.h>


/*
Depth First Search:

Given a graph G=(V,E) and a distinguished source vertex s, depth first search explores the edges of G to find every vertex that is reachable from s

Principle: the algorithm discovers edges out of most recently discovered vertex v that still has unexplored edges leaving it. When all of
v's edges have been explored, the search "backtracks" to explore edges leaving the vertex from which v was discovered. The process
continues until we have discovered all the vertices that are reachable from the original source vertex.

Timestamps: Each vertex v has two timestamps:
-the first timestamp d[v] when v is first discovered (grayed)
-the second timestamp f[v] when the search finishes examining v's adjacency list (blackened)

d[v]<f[v]

Complexity: O(V+E)

*/


//a series of helper functions to form the queue required to perform breadth first search on the given graph

//user defined data type for graph
struct Graph{
    int V;//number of vertices
    int *adj;//2D adjacency matrix to store the information about the edges
};

typedef struct Graph graph;//to make declaration easier


//end of helper functions

void DFS(graph G)//function to perform depth first search for given graph G
{
    //for ease of computation we assume the vertices are 0,1,2,...,V

    int *color=(int*)calloc(G.V,sizeof(int));//int array to store color of each vertex

    //white:0
    //gray:1
    //black:2

    int *parent=(int*)calloc(G.V,sizeof(int));//int array to store parent of each vertex

    int *d=(int*)calloc(G.V,sizeof(int));//int array to store entry time

    int *f=(int*)calloc(G.V,sizeof(int));//int array to store exit time

    //initialization

    //initialization of all vertices: initially all are white

    for(int i=0;i<G.V;i++)
    {

        color[i]=0;//white
        parent[i]=G.V+1;//parent is not known yet, hence we assign an out of bounds value

    }

    //end of initialization

    int t=0;//time of visit, to keep track of the sequence in which nodes were visited

    printf("\n");

    for(int i=0;i<G.V;i++)//scanning over all the vertices
    {
        if(color[i]==0)//if white (undiscovered)
            t=DFS_VISIT(i,color,parent,d,f,G,t);
    }
    printf("\n\n");

    //final result:

    printf("\n***********************************\n\n");

    for(int i=0;i<G.V;i++)
        printf("Vertex: %d, Entry time: %d, Exit time: %d\n",i,d[i],f[i]);

    printf("\n***********************************\n");




}
//end of DFS()

//helper function to recursively explore vertices until all vertices have been explored
int DFS_VISIT(int u, int *color, int *parent, int *d, int *f, graph G, int t)
{
    color[u]=1; //assign grey as it has been visited now
    t+=1; //increase time stamp by 1
    d[u]=t; //entry time

    printf("\nExploring vertex: %d \n",u);

    if(parent[u]==(G.V+1))
        printf("Parent: NIL\n");
    else
        printf("Parent: %d\n",parent[u]);


    if(color[u]==0)
        printf("Color: White\n");
    else if(color[u]==1)
        printf("Color: Gray\n");
    else
        printf("Color: Black\n");


    for(int v=0;v<G.V;v++)
    {
        if(*(G.adj + u*G.V + v)!=0)//edge from u to v exists
        {
            if(color[v]==0)//v has not been explored yet
            {
                parent[v]=u;
                t=DFS_VISIT(v,color,parent,d,f,G,t);//recursive call to explore the child vertex v
            }

        }
    }
    color[u]=2;//assign black: at the end of this function, all adjacent vertices to u have been visited
    f[u]=t=t+1;//increase t by 1 and assign to exit timestamp of the vertex u
    return t;//base case: return time stamp once vertex has been fully explored

}
//end of DFS_VISIT()

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

        for(int j=0;j<G.V;j++)
        {
            printf("Edge from %d to %d? (Y:1/N:0)\n",i,j);
            scanf("%d",&ch);

            //ch==0 means there is no edge from i to j th vertex
            //any non zero value of ch implies that an edge exists from the i to j th vertex and it will store '1'
            //irrespective of the user entry, as shown below

            *(G.adj+i*G.V+j)=(ch!=0);

            //adj[i][j]=1 implies there exists an edge from i to j th vertex
        }
    }

    printf("\nDisplaying the adjacency matrix\n\n");
    for(int i=0;i<G.V;i++)
    {
        for(int j=0;j<G.V;j++)
            printf("%d ",*(G.adj+i*G.V+j));
        printf("\n");
    }


    DFS(G);

}
//end of main()



