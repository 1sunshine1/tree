#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ERROR 0
#define OK 1

typedef struct Node{
    char data;
    struct Node *lchild, *rchild;
}Node, *pNode;

typedef struct Stack{
    pNode *data;
    int top, size;
}Stack, *pStack;

void init_stack(Stack *s, int len){
    s->data = (pNode *)malloc(sizeof(pNode) * len);
    s->size = len;
    s->top = -1;
}

int empty_stack(Stack *s){
   return s->top == -1;
}

int push_stack(Stack *s, pNode e){
    if(s->top >= s->size - 1) {
        return ERROR;
    }
    s->data[++(s->top)] = e;
    return OK;
}
int pop_stack(Stack *s){
    if(empty_stack(s)){
        return ERROR;
    }
    --(s->top);
    return OK;
}
pNode top_stack(Stack *s){
    if(empty_stack(s)){
        return NULL;
    }
    return s->data[s->top];
}

void clear_stack(Stack *s){
    free(s->data);
    free(s);
}
pNode init(char data){
    pNode node = (pNode)malloc(sizeof(Node));
    node->lchild = NULL;
    node->rchild = NULL;
    node->data = data;
    return node;
}
void clear(pNode node) {
    if (!node) return;
    if (node->lchild != NULL) {
        clear(node->lchild);
    }
    if (node->rchild != NULL) {
        clear(node->rchild);
    }
    free(node);
}

pNode build(char *str) {
    pNode p = NULL, last_p = NULL;
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    init_stack(stack, strlen(str));
    int k = 0;
    while (str[0]) {
        switch(str[0]) {
            case'(':
                k = 0;
                push_stack(stack, p);
                p = NULL;
                break;
            case',':
                k = 1;
                p = NULL;
                break;
            case')':
                last_p = top_stack(stack);
                pop_stack(stack);
                break;
            default:
                p = init(str[0]);
                if (!empty_stack(stack) && k == 0) {
                    top_stack(stack)->lchild = p;
                } else if (!empty_stack(stack) && k == 1) {
                    top_stack(stack)->rchild = p;
                }
                break;
        }
        ++str;
    }
    if (p && !last_p) last_p = p;
    clear_stack(stack);
    return last_p;
}
void output(pNode node, char x) {
   if (node == NULL || node->data == x) return;
    printf("%c", node->data);
    if ((node->lchild == NULL || node->lchild->data == x) &&
        (node->rchild == NULL || node->rchild->data == x)) {
        return;
    }
    printf("("); 
    if (node->lchild != NULL && node->lchild->data != x) {
        output(node->lchild, x);
    }
    if (node->rchild != NULL && node->rchild->data != x) {
        printf(",");
        output(node->rchild, x);
    }
    printf(")");
    return;
}


int main() {
    char str[35], ch;
    int ind = 0;
    while(scanf("%c", &ch)) {
        if (ch == '\n') break;
        str[ind++] = ch;
        }
    str[ind] = 0;
    scanf("%c", &ch);
    pNode p = build(str);
    output(p, ch);
    clear(p);
    return 0;
}
