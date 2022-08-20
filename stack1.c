#include <stdio.h>
# include <stdlib.h>

#define MAX 10
struct Stack{
    int top, arr[];
};

typedef struct Stack stack;


//Pushing data into the stack
void push(stack *s){

    if (s->top == (MAX-1)){
        printf("\nOverflow"); //static implementation has an upper limit on number of elements it can store
    }
    else{
        int d;
        char temp;
        printf("\nEnter the data to be pushed into the stack:");
        scanf("%d", &d);
        scanf("%c",&temp);
        if(s->top == -1){
            s->arr[++(s->top)] = d;
        }
        else{


            s->top += 1;
            s->arr[s->top] = d;
        }
    printf("\nPush successful\n");
    }
    return 0;
}

//Popping data from the top of the stack
int pop(stack *s){
    int temp;
    if(s->top == -1){
        printf("\nUnderflow. Nothing to pop.\n");
        return NULL;
    }
    else{
        temp = s->arr[s->top];
        s->arr[s->top] = NULL;
        s->top -= 1;
        printf("\nPopping successful.\n");
        return temp;
    }

}

//peeking at the data at the top of the stack
void peek(stack* s){
    if(s->top==-1){
        printf("\nEmpty stack\n");
        return;
    }
    else{
        printf("%d",s->arr[s->top]);
    }

}


//Displaying the stack
int display(stack *s){
    int i;
    if(s->top == -1){
        printf("\nStack is empty. Nothing to display.\n");
    }
    else{
        printf("\n***********************************\n");

        for(int i=s->top;i>0;i--){
            printf("%d ->",s->arr[i]);

        }
        printf("%d \n",s->arr[0]);
        printf("\n***********************************\n");
    }
}

int main(){
    stack s;
    //initialization
    s.top=-1;
    s.arr[MAX];
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
    printf("\nThe length of the stack is %d", (s.top+1));
    display(&s);

    return 0;
}
