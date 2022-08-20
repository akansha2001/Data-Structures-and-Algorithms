
# include <stdio.h>
# include <stdlib.h>


//a structure 'node' is defined for a binary tree: a binary tree node has data, a pointer to left child and a pointer to right child
struct node
{
  int data;
  struct node* left;
  struct node* right;
};

typedef struct node snode;//making variable declaration easier

//function that allocates a new node with the given data and sets left and right pointers to NULL
//returns the created node to the calling function
snode* newNode(int data)
{
    snode* node=(snode*)malloc(sizeof(snode));//memory allocation

    node->data=data;
    node->left=NULL;
    node->right=NULL;

    return node;
}
//end of newNode()

//function to check whether the binary tree is strict or not
int isStrict(snode* root)
{
    /*
    A strict binary tree is one where every node has either two or zero number of children
    This function recursively checks whether the given binary tree is strict or not
    */


    //case 1: empty tree is strictly binary (base case 1)
    if (root==NULL)
        return 1;

    //case 2: leaf node is strictly binary (base case 2)
    if (root->right==NULL && root->left==NULL)
        return 1;

    //case 3: if both left and right are non empty, recursive call on the left and right subtrees
    //to ensure they are BOTH strict binary trees
    if ((root->left) && (root->right))
        return (isStrict(root->left) && isStrict(root->right));

    //none of the above are satisfied: i.e. the node has one child
    return 0;

}
//end of isStrict()

//helper function to determine the depth of the binary tree passed as parameter
unsigned int depth(snode* root)
{
    if (root == NULL)//empty tree: depth is 0
        return 0;


    //'1' is added for the present level
    //recursive call on the left and right subtrees of the tree to find and compare their depths(using ternary operator :?)
    //whichever subtree is "deeper" determines the final depth of the tree
    unsigned int m=(depth(root->left)>depth(root->right))?depth(root->left):depth(root->right);
    return 1 + m;
}
//end of depth()

//helper function to count the number of nodes in a binary tree
unsigned int countNodes(snode* root)
{
    if (root == NULL)//empty tree: not a node, does not increase count
        return 0;

    //'1' is added for the current, non empty node (checked by the 'if' statement earlier)
    //recursive call on the left and right subtrees to count their respective number of nodes
    return (1 + countNodes(root->left) + countNodes(root->right));

}
//end of countNodes()

//function to check whether binary tree is complete
int isComplete (snode* root)
{
    /*
    A complete binary tree is one where the tree is at "full capacity"
    Every node except the nodes on the last level has exactly two children
    Every node on the last level is a leaf node (zero children)

    Every complete binary tree is a strict binary tree but every strict binary tree is not necessarily complete
    */

    //we use unsigned int as number of nodes and depth can never be negative integers

    unsigned int no_nodes=countNodes(root);//number of nodes in the tree

    unsigned int d = depth(root);//depth of the tree

    int maxnodes=pow(2,d)-1;//maximum number of nodes in a tree of depth 'd'

    printf("\nDepth of tree is %d, thus maximum nodes %d\n",d,maxnodes);

    printf("\nNumber of nodes in the tree: %d\n",no_nodes);

    //if number of nodes in the tree = maximum number of nodes the tree can accommodate, with it's depth
    //i.e. the tree is at "full capacity", it is said to be complete
    return (no_nodes==maxnodes);
}
//end of isComplete()

//function to take input from user
snode* input(snode* root,int idx)
{
    //we index the nodes of the tree, starting from zero (root node)

    int ch;//user's choice
    printf("Will node %d have data? yes(1), no(0)?\n",idx);
    scanf("%d",&ch);

    if(ch==0)//base case
        return root;


    int d;//variable for data entered by user
    printf("Enter data for node %d \n",idx);
    scanf("%d",&d);
    root=newNode(d);

    //left subtree of node at idx
    printf("For left subtree..\n");
    root->left=input(root->left,2*idx+1);//recursive call on left subtree with indexed nodes for user's convenience

    //right subtree of node at idx
    printf("For right subtree..\n");
    root->right=input(root->right,2*idx+2);//recursive call on right subtree with indexed nodes for user's convenience

}
//end of input()

//main() to call the functions
void main()
{
    snode* root = NULL;//pointer to represent the tree

    root=input(root,0);

    printf("\n************************************\n");

    if (isComplete(root))
        printf("\nComplete Binary Tree\n");
    else
        printf("\nNot a Complete Binary Tree\n");

    if (isStrict(root))
        printf("\nStrict Binary Tree\n");
    else
        printf("\nNot a Strict Binary Tree\n");

    printf("\n************************************\n");

}
//end of main()

