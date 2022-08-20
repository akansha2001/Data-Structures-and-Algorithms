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
    snode* node=(snode*)malloc(sizeof(snode));
    node->data=data;
    node->left=node->right=NULL;

    return node;
}

//function to print inorder traversal of the binary tree passed as parameter
void inOrder(snode* node)
{
    /*
    Inorder traversal of a binary tree is a depth first traversal where the data is printed as
    Left subtree-Data-Right subtree
    */

    if(node==NULL)//base case: empty tree has nothing to print
        return;

    //recursion on left subtree to print inorder traversal of left subtree
    inOrder(node->left);

    //print the data in the node
    printf("%d  ",node->data);

    //recursion on right subtree to print inorder traversal of right subtree
    inOrder(node->right);

}
//end of inOrder()

//function to print preorer traversal of the binary tree passed as parameter
void preOrder(snode* node)
{
    /*
    Preorder traversal of a binary tree is a depth first traversal where the data is printed as
    Data-Left subtree-Right subtree
    */

    if(node==NULL)//base case: empty tree has nothing to print
        return;

    //print the data in the node
    printf("%d  ",node->data);

    //recursion on left subtree to print preorder traversal of left subtree
    preOrder(node->left);

    //recursion on right subtree to print preorder traversal of right subtree
    preOrder(node->right);
}
//end of preOrder()

//function to print postorder traversal of the binary tree passed as parameter
void postOrder(snode* node)
{
    /*
    Postorder traversal of a binary tree is a depth first traversal where the data is printed as
    Left subtree-Right subtree-Data
    */

    if(node==NULL)//base case: empty tree has nothing to print
        return;

    //recursion on left subtree to print postorder traversal of left subtree
    postOrder(node->left);

    //recursion on right subtree to print postorder traversal of right subtree
    postOrder(node->right);

    //print the data in the node
    printf("%d  ",node->data);

}
//end of postOrder()

//function to take input from user
snode* input(snode* root,int idx)
{
    //we index the nodes of the tree, starting from zero (root node)

    int ch;//user's choice
    printf("Will node %d have data? yes(1), no(0)?\n",idx);
    scanf("%d",&ch);

    if(ch==0)//base case. For any value of ch that is not zero, function accepts input

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


//main() to call the functions
void main()
{


    snode* root=NULL;//pointer to represent the tree

    root=input(root,0);

    //we assume user inputs a binary search tree, in which case we will obtain the nodes in ascending order for inorder traversal

    printf("\ntraversing the tree...\n");

    printf("\nPreorder traversal:\n");
    preOrder(root);

    printf("\nInorder traversal:\n");
    inOrder(root);

    printf("\nPostorder traversal:\n");
    postOrder(root);
}
