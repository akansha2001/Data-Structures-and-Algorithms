# include <stdio.h>
# include <stdlib.h>



//node
struct node{
	int data;
	struct node *next;
};
typedef struct node snode;

//stack
struct Stack{
	int len;
	snode *top;
};
typedef struct Stack stack;

stack A,B,C;

int n;


// underflow check
int isEmpty(stack* s){
	return (s->len==0);
}

//pushing data into the stack
void push(stack* s, int d){

    snode *a = malloc(sizeof(snode));
    a->data=d;
    a->next=NULL;

    if(isEmpty(s)){


        s->top = a;
        a->next = NULL;
        s->len = 1;
    }
    else{

        a->next = s->top;
        s->top = a;
        s->len++;
    }


}

//Pop data out of the stack
int pop(stack* s){
    if(isEmpty(s)){
        printf("\nStack is empty. Nothing to pop.\n");
        return NULL;
    }
    else{
        int d;
        snode *a = s->top;
        d = a->data;
        s->top = s->top->next;
        s->len--;

        return d;
    }
}


//To display stack
void display(stack* s){
    int i=1;
    if(isEmpty(s)){
        printf("Stack is empty.\n");
    }
    else{

        snode *temp=s->top;
        while(temp->next!=NULL){
            printf("%d ->",temp->data);
            temp = temp->next;
        }
        printf("%d \n",temp->data);


    }
}


void towers(int n, char frompeg, stack *f, char topeg, stack *t, char auxpeg, stack *a)
{
    if(n==1)
    {
        printf("Move disk 1 from peg %c to peg %c \n",frompeg,topeg);
        push(t,pop(f));
        printf("Stack A:\n");
        display(&A);
        printf("Stack B:\n");
        display(&B);
        printf("Stack C:\n");
        display(&C);
        printf("***************************\n");


    }
    else
    {
        towers((n-1),frompeg,f,auxpeg,a,topeg,t);
        printf("Move disk %d from peg %c to peg %c \n",n,frompeg,topeg);
        push(t,pop(f));
        printf("Stack A:\n");
        display(&A);
        printf("Stack B:\n");
        display(&B);
        printf("Stack C:\n");
        display(&C);
        printf("***************************\n");
        towers((n-1),auxpeg,a,topeg,t,frompeg,f);
    }
}
void main(){
    //initializing the stacks
    A.top=NULL;
    B.top=NULL;
    C.top=NULL;
    A.len=0;
    B.len=0;
    C.len=0;




    printf("Enter number of disks:\n");
    scanf("%d",&n);

    for (int i =n;i>=1;i--)
        push(&A,i);

    printf("\nInitial stacks:\n");
    printf("Stack A:\n");
    display(&A);
    printf("Stack B:\n");
    display(&B);
    printf("Stack C:\n");
    display(&C);
    printf("***************************\n");



    towers(n,'A',&A,'C',&C,'B',&B);


}




