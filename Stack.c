#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include<math.h>

/*
 * Item: An item that is being pushed to or popped from the stack
 *       It may be float (to be used while evaluating the postfix)
 *       It may be char* (to be used while converting infix to postfix)
 */
typedef union
{
    float fData;
    char* cpData;
} Item;
/*
 *
 */
struct Node
{
    Item data;
    struct Node * next;
};
typedef struct
{
    /* TODO: ADD YOUR CODE HERE */
    struct Node * top;
} Stack;
/*
 *
 */
void init(Stack *s)
{
    /* TODO: ADD YOUR CODE HERE */
    s->top = NULL;

}
/*
 *
 */
int isEmpty(Stack *s)
{
    /* TODO: ADD YOUR CODE HERE */

    return (s->top==NULL);
}
/*
 *
 */
Item top(Stack *s)
{
    /* TODO: ADD YOUR CODE HERE */
    if(s->top!=NULL)
        return s->top->data;
}
/*
 *
 */
Item pop(Stack *s)
{
    if(!isEmpty(s))
    {
        struct Node *oldTop = s->top;
        s->top=s->top->next;
        Item data = oldTop->data;
        free(oldTop);
        return data;
    }
    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void push(Stack *s, Item val)
{
    /* TODO: ADD YOUR CODE HERE */
    struct Node* newTop = malloc(sizeof(struct Node));
    newTop->data = val;
    newTop->next = s->top;
    s->top = newTop;
}
/*
 *
 */
void destroy(Stack *s)
{
    /* TODO: ADD YOUR CODE HERE */
    while(!isEmpty(s))
    {
        struct Node * oldTop;
        oldTop = s->top;
        s->top=s->top->next;
        free(oldTop);
    }
}
/*
 * infixToPostfix: converts an expression in infix notation to
 *					to a postfix notation (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 *					ASSUME ^*+-/ operators
 *					e.g., 2+3 --> 23+
 *					e.g., (2+3)*4 --> 23+4*
 */
int precedence(char* token,char * top)
{
    if(!strcmp(top,"+")&&!strcmp(token,"-"))
    {
        return 1;
    }
    else if(!strcmp(top,"-")&&!strcmp(token,"+"))
    {
        return 1;
    }
    else if(!strcmp(top,"*")&&(!strcmp(token,"/")||!strcmp(token,"-")||!strcmp(token,"+")))
    {
        return 1;
    }
    else if(!strcmp(top,"/")&&(!strcmp(token,"*")||!strcmp(token,"-")||!strcmp(token,"+")))
    {
        return 1;
    }
    else if(!strcmp(top,"^")&&(!strcmp(token,"^")||!strcmp(token,"*")||!strcmp(token,"-")||!strcmp(token,"+")))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void infixToPostfix(char* infix, char* postfix)
{
    strcpy(postfix,"\0");
    Stack s;
    Item out;
    init(&s);
    const char delim[2]=" ";
    char*token;
    char str[255];
    strcpy(str,"( ");
    strcat(str,infix);
    strcat(str," )");
    token = strtok(str,delim);
    while(token!= NULL)
    {
        if(!strcmp(token,"+")||!strcmp(token,"-")||!strcmp(token,"*")||!strcmp(token,"/")||!strcmp(token,"(")||!strcmp(token,"^"))
        {
            if(!isEmpty(&s))
            {
                //while((!strcmp(top(&s).cpData,"+")&&!strcmp(token,"-"))||(!strcmp(top(&s).cpData,"-")&&!strcmp(token,"+"))||(!strcmp(top(&s).cpData,"*")&&!strcmp(token,"/"))||(!strcmp(top(&s).cpData,"/")&&!strcmp(token,"*")))
                while(precedence(token,top(&s).cpData))
                {
                    out = pop(&s);
                    strcat(postfix,out.cpData);
                    strcat(postfix," \0");

                }

            }
            push(&s,(Item)token);

        }
        else if(!strcmp(token,")"))
        {

            while(strcmp(top(&s).cpData,"(")&&!isEmpty(&s))
            {
                out = pop(&s);
                strcat(postfix,out.cpData);
                strcat(postfix," \0");
            }
            out = pop(&s);
        }
        else
        {

            strcat(postfix,token);
            strcat(postfix," \0");
        }

        token = strtok(NULL," ");
        strcat(postfix,"\0");
    }

}

/*
 * evaluatePostfix: Evaluates an expression in postfix notation
 *					 (Reverse-Polish Notation)
 *					ASSUME single-digit operands
 */
float evaluatePostfix(char* postfix)
{
    /* TODO: ADD YOUR CODE HERE */
    Stack*s;
    init(s);
    float operand1=0,operand2=0,out = 0;
    Item f,fl;
    const char delim[2]=" ";
    char*token;
    token = strtok(postfix,delim);
    while(token != NULL)
    {
        if(!strcmp(token,"+")||!strcmp(token,"-")||!strcmp(token,"*")||!strcmp(token,"/")||!strcmp(token,"^"))
        {
            operand2 = pop(s).fData;
            operand1 = pop(s).fData;
            if(!strcmp(token,"+"))
            {
                f.fData = operand1+operand2;
            }
            else if(!strcmp(token,"-"))
            {
                f.fData = operand1-operand2;
            }
            else if(!strcmp(token,"*"))
            {
                f.fData = operand1*operand2;
            }
            else if(!strcmp(token,"/"))
            {
                f.fData = operand1/operand2;
            }
            else if(!strcmp(token,"^"))
            {
                f.fData = pow(operand1,operand2);
            }
            push(s,f);

        }
        else
        {
            out = atof(token);
            Item x ;
            x.fData = out;
            push(s,x);

        }

        token = strtok(NULL,delim);

    }
    fl =  pop(s);
    return fl.fData;
}
/*
 *
 */
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
 *
 */
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";

    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);

        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);

        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);

        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}

