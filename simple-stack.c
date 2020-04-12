#include<stdio.h>
#include<stdlib.h>
 
int n, top = -1, *stack;
 
void push(int x){
    if(top==n-1) return;
    stack[++top]=x;
    printf("push: top = %d, ", top);
}
 
int pop(){
    if(top==-1) return -1;
    printf("pop: top = %d\n", top);
    return stack[top--];
}
 
int peek(){
    if(top==-1) return -1;
    return stack[top];
}
 
void display(){
    for(int i=top ; i>-1 ; i--) printf("%d ",stack[i]);
    printf("\n\n");
}
 
int main(){
     
    n = 10;
     
    printf("Initializing the stack with size 10\n\n");
     
    stack = (int*)malloc(n*sizeof(int));
     
    printf("Pushing elements into the stack\n\n");
     
    push(1);
    push(2);
    push(3);
        push(4);
    push(5);
    push(6);
    push(7);
    push(8);
    push(9);
    push(10);
    push(11);
    push(12);
    push(13);
    push(14);
    push(15);

    
    printf("\nDisplaying elements of the stack -\n");
     
    display();
     
    printf("The top of the stack = %d\n\n",peek());
     
    printf("Pop the top of the stack = %d\n",pop());     
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());     
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());     
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());
    printf("Pop the top of the stack = %d\n",pop());


     
    printf("Displaying elements of the stack -\n");
     
    display();
     
    return 0;
}
