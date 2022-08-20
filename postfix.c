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
        printf("\nStack is empty.\n");
    }
    else{
        printf("\nDisplaying stack:\n");
        snode *temp=s->top;
        while(temp->next!=NULL){
            printf("%d ->",temp->data);
            temp = temp->next;
        }
        printf("%d \n",temp->data);


    }
}

void main(){



    printf("Enter a postfix expression:\n");
    char exp[50];
    int c=0;
    char ch='a';
    while(ch!='\n')
    {
        scanf("%c",&ch);
        exp[c]=ch;
        c++;
    }



    stack opstack;
    opstack.top=NULL;
    opstack.len=0;

    int val1=0, val2=0;


    int i=0;
    while(exp[i]!='$')
    {
        // if the character is an operand ,push it to the stack
        if (isdigit(exp[i]))
            push(&opstack, exp[i]-'0' );
        else if (exp[i]==',')
        {
            i++;
            continue;
        }

        // if the character is an operator, pop two elements from stack apply the operator
        else
        {
            val1 = pop(&opstack);
            val2 = pop(&opstack);
            switch (exp[i])
            {
            case '+': push(&opstack, (val2+val1)); break;
            case '-': push(&opstack, (val2-val1)); break;
            case '*': push(&opstack, (val2*val1)); break;
            case '/': push(&opstack, (val2/val1)); break;
            case '^': push(&opstack, pow(val2,val1)); break;
            }
        }
        display(&opstack);
        i++;
    }

    printf("Result: %d \n",pop(&opstack));

}

