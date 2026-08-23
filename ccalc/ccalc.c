#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rstack[100],x,y,result = 0;
char postfix[100];
char opstack[100];
int i = 0,j = 0,rtop = -1,otop = -1;
char inp[100];
char num[] = "0123456789";
char op[] = "+-*/%^";

int precedence(char op){
    int precedence;
    switch(op){
        case '+':
        case '-':
        precedence = 1;break;
        case '*':
        case '/':
        case '%':
        precedence = 2;break;
        case '^':
        precedence = 3;break;
    }
    return precedence;
}
int push(char item,char stack[100],int top){
    top ++;
    stack[top] = item;
    return top; 
}

void rpush(int item){
    rtop++;
    rstack[rtop] = item;
}

int rpop(){
    int item = rstack[rtop];
    rtop--;
    return item;
}
int pop(char stack[100],int top){
    top--;
    return top;
}

void concatenate(char a[10],char b){
    int i = strlen(a);
    a[i] = b;
    a[i+1] = '\0';
}
int power(int a,int b){
    int result = 1;
    for(int i =0;i<b;i++){
        result*=a;
    }
    return result;
}
int operate(int a,int b,char c){
    switch(c){
        case '+':return a + b;
        case '-':return a - b;
        case '*':return a * b;
        case '/':return a / b;
        case '%':return a % b;
        case '^':return power(a,b);
    }
}
void main(){
    printf("C-Calc>>");
    scanf("%s",inp);
    while (inp[i] != '\0'){
        if (strchr(num,inp[i])!=NULL){
            concatenate(postfix,inp[i]);
        }
        else{
            char x = inp[i];
            char y = opstack[otop];
            if(strchr(op,inp[i])!=NULL && strchr(num,inp[i-1])!=NULL){
                concatenate(postfix,'x');
            }
            if (x == '('){
                otop = push(x,opstack,otop);
            }
            else if(x == ')'){
                while (opstack[otop] != '('){
                    char operator = opstack[otop];
                    concatenate(postfix,operator);
                    otop = pop(opstack,otop);
                }
                otop = pop(opstack,otop);
            }else if(precedence(x) > precedence(y)){
            otop = push(x,opstack,otop);       
            } else if(precedence(x) < precedence(y)){
                while(precedence(x) < precedence(y)){
                    char y = opstack[otop];
                    char operator = opstack[otop];
                    concatenate(postfix,operator);
                    otop = pop(opstack,otop);
                }
            }else{
                j++;
                otop = push(x,opstack,otop);
            }
        }
        i++;
        j++;
    }
    while(otop!=-1){
        char operator = opstack[otop];
        concatenate(postfix,operator);
        otop = pop(opstack,otop);
    }
    postfix[j] = '\0';
    j = 0;
    char value[10] = "";
    while(postfix[j]!='\0'){
        if (strchr(num,postfix[j])!=NULL){
            concatenate(value,postfix[j]);
        }else if (postfix[j] == 'x'){
            rpush(atoi(value));
            value[0] = '\0';
        }else{
            if (value[0]!='\0'){
                rpush(atoi(value));
            }
            value[0] = '\0';
            y = rpop();
            x = rpop();
            rpush(operate(x,y,postfix[j]));
        }
        j++;
    }

    result = rstack[rtop];
    printf("Result:\n%d\n",result);

    
}