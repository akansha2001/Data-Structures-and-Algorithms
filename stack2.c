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
void push(stack* s){
    int d;
    char temp;
    printf("\nEnter the data to be pushed into the stack:\t");
    scanf("%d", &d);
    scanf("%c",&temp);
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
	printf("\nPush operation successful\n");

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
        printf("\nPop operation successful\n");
        return d;
    }
}

//To peek at the data at the top of the stack
void peek(stack* s){
    if(isEmpty(s)){
        printf("\nEmpty stack\n");
        return;
    }
    else{
        printf("%d",s->top->data);
    }

}

//To display stack
void display(stack* s){
    int i=1;
    if(isEmpty(s)){
        printf("\nStack is empty.\n");
    }
    else{
        printf("\n***********************************\n");
        snode *temp=s->top;
        while(temp->next!=NULL){
            printf("%d ->",temp->data);
            temp = temp->next;
        }
        printf("%d \n",temp->data);
        printf("\n***********************************\n");

    }
}

int main(){

    stack s;
    s.top=NULL;
    s.len=0;
    printf("\nPushing 4 elements\n");
    push(&s);
    push(&s);
    push(&s);
    push(&s);
    printf("\nPeeking\n");
    peek(&s);
    printf("\nPushing 2 elements\n");
    push(&s);
    push(&s);
    printf("\nDisplaying the stack\n");
    display(&s);
    printf("\nPopping 2 elements\n");
    printf("Popped element %d\n",pop(&s));
    printf("Popped element %d\n",pop(&s));
    printf("\nThe length of the stack is %d", s.len);
    display(&s);

    return 0;
}







