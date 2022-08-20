

# include <stdio.h>
# include <stdlib.h>



/*
Binary Search Tree is a node-based binary tree data structure which has the following properties:

The left subtree of a node contains only nodes with data lesser than the node’s data.
The right subtree of a node contains only nodes with data greater than the node’s data.
The left and right subtree each must also be a binary search tree.
There must be no duplicate nodes.

The above properties of Binary Search Tree provides an ordering among data so that the operations like search, minimum and maximum can be done fast.
If there is no ordering, then we may have to compare every data to search for a given data.

Inorder traversal of binary search tree displays the data in ascending order
*/

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

//function to return the minimum value in the tree passed as parameter
snode* minValue(snode* node)
{
    snode* current = node;

    // loop down to find the leftmost leaf: by property of a binary search tree, the leftmost element is the minimum
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

//function to insert data 'd' into correct location in the binary search tree, such that it's property is preserved
//return type must be *snode to reflect the changes to the tree. Had we passed a pointer to the root, this would not be necessary
snode* insert_node(snode* root, int d)
{

    if (root==NULL)//base case: empty tree(/subtree): insert data at root node
    {
        root=newNode(d);
        return root;
    }
    if(d<root->data)
    //'d' is less than the data in root: must be inserted in left subtree
    //location of insertion is determined recursively by now sending left subtree as argument
        root->left= insert_node(root->left,d);
    else if(d>root->data)
    //'d' is greater than the data in root: must be inserted in right subtree
    //location of insertion is determined recursively by now sending right subtree as argument
        root->right= insert_node(root->right,d);
    else
    //the remaining case: if 'd' is equal to data in root node, duplicate condition is reached and no insertion must be performed
        return root;



}


snode* insert_node2(snode* root, int d)
{

    if (root==NULL)
    {
        root=newNode(d);
        return root;
    }
    //root is non empty
    if(d<root->data)
    {

        if (root->left==NULL)
        {
            root->left=newNode(d);
            return root;
        }
        //left was not empty. check if right was empty:
        if (root->right==NULL)
        {
            //rearrange and enter data
            int minm=root->left->data, mid=d, maxm=root->data;

            if(d<minm)
            {
                minm=d;
                mid=root->left->data;
            }
            //swap

            root->left->data=minm;
            root->data=mid;
            root->right=newNode(maxm);
            return root;
        }
        root->left=insert_node2(root->left,d);
    }
    else
    {
        if (root->right==NULL)
        {
            root->right=newNode(d);
            return;
        }
        //right was not empty. check if left was empty:
        if (root->left==NULL)
        {
            //rearrange and enter data
            int maxm=root->right->data, mid=d, minm=root->data;

            if(d>maxm)
            {
                maxm=d;
                mid=root->right->data;
            }
            //swap

            root->left=newNode(minm);
            root->data=mid;
            root->right->data=maxm;

            return root;
        }
        root->right=insert_node2(root->right,d);
    }
}

//function to delete data 'd' from the tree, if found, while maintaining the property of binary search tree
//return type must be *snode to reflect the changes to the tree. Had we passed a pointer to the root, this would not be necessary
snode* delete_node(snode* root, int d)
{
    // base case
    if (root == NULL)
    {
        printf("\ndeletion failed\n");
        return root;
    }


    // If the item to be deleted is smaller than the root's data, then it lies in left subtree
    //recursive call on the left subtree to find and delete the data from there
    if (d < root->data)
        root->left = delete_node(root->left, d);

    // If the item to be deleted is larger than the root's data, then it lies in right subtree
    //recursive call on the rught subtree to find and delete the data from there
    else if (d > root->data)
        root->right = delete_node(root->right, d);

    // if 'd' is same as root's data, then this is the node to be deleted
    else
    {
        //case 1: node with only one child or no child
        //if node has one child: it is set to that child
        //if node has no children: node is set to NULL

        if (root->left == NULL) //left is empty=> right is empty or non-empty. In any case,
        //assigning the value of right subtree to the root works
        {
            snode* temp = root->right;//NULL, if node has no children
            free(root);//free memory
            return temp;//essentially: root is now set to the root of its right subtree
        }

        else if (root->right == NULL) //in this case, left==NULL was not satisfied, so left subtree must be non empty
        {
            snode* temp = root->left;
            free(root);//free memory
            return temp;//essentially: root is now set to the root of its left subtree
        }

        //we observe that 'return' keyword terminates the if-else blocks if satisfies
        //so we do not need an 'else' block for this case

        //case 2: node with two children: Get the inorder successor (smallest in the right subtree)
        snode* temp = minValue(root->right);

        //copy the inorder successor's content to this node
        root->data = temp->data;

        //once data has been copied, delete the inorder successor by recursively calling delete_node() on the right subtree
        root->right = delete_node(root->right, temp->data);
    }
    return root;//return the modified root to the calling function
}


//function to count the number of nodes in a binary tree
unsigned int countNodes(snode* root)
{
    if (root == NULL)
        return 0;
    return (1 + countNodes(root->left) + countNodes(root->right));//recursive call to left and right subtree to count the number of nodes
}

unsigned int depth(snode* root)
{
    if (root == NULL)
        return 0;

    int m=(depth(root->left)>depth(root->right))?depth(root->left):depth(root->right);
    return 1 + m;
}




void main()
{
    snode* root = NULL;

    printf("\n");
    root=insert_node(root,10);

    root=insert_node(root,10);

    root=insert_node(root,20);

    root=insert_node(root,30);

    root=insert_node(root,40);

    root=insert_node(root,50);

    root=insert_node(root,60);

    root=insert_node(root,70);


    printf("\ninorder\n");
    inOrder(root);
    printf("\n*****************\n");
    printf("preorder\n");
    preOrder(root);
    printf("\n*****************\n");
    printf("postorder\n");
    postOrder(root);
    printf("\n*****************\n");

    root=delete_node(root,20);

    root=delete_node(root,10);

    printf("\ninorder\n");
    inOrder(root);
    printf("\n*****************\n");
    printf("preorder\n");
    preOrder(root);
    printf("\n*****************\n");
    printf("postorder\n");
    postOrder(root);
    printf("\n*****************\n");


    printf("\ndepth is %d",depth(root));



    root=NULL;
    printf("\n");
    root=insert_node2(root,10);

    root=insert_node2(root,20);

    root=insert_node2(root,30);

    root=insert_node2(root,40);

    root=insert_node2(root,50);

    root=insert_node2(root,60);

    root=insert_node2(root,70);

    printf("\ninorder\n");
    inOrder(root);
    printf("\n*****************\n");
    printf("preorder\n");
    preOrder(root);
    printf("\n*****************\n");
    printf("postorder\n");
    postOrder(root);
    printf("\n*****************\n");

    root=delete_node(root,20);

    root=delete_node(root,10);

    printf("\ninorder\n");
    inOrder(root);
    printf("\n*****************\n");
    printf("preorder\n");
    preOrder(root);
    printf("\n*****************\n");
    printf("postorder\n");
    postOrder(root);
    printf("\n*****************\n");

    printf("\ndepth is %d",depth(root));



    /*
    root->left->right->right = newNode(90);
    root->right->left->left = newNode(80);
    root->right->left->right = newNode(90);
    root->right->right->left = newNode(80);
    */



}

