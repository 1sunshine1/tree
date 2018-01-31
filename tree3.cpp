#include <iostream>
using namespace std;
int num[10] = {0};

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node, *pNode;

Node *init_tree(char data) {
    Node *tree = (Node *)malloc(sizeof(Node));
    tree->data = data;
    tree->lchild = NULL;
    tree->rchild = NULL;
    return tree;
}

void output(Node *tree) {
    if (tree == NULL) return ;
    cout << tree->data;
    if (tree->lchild != NULL || tree->rchild != NULL) {
        cout << '(';
        if (tree->lchild != NULL) {
            output(tree->lchild);
        }
        if (tree->rchild != NULL) {
            cout << ',';
            output(tree->rchild);
        }
        cout << ')';
    }
    return ;
}
int main() {
    char ch[4];
    pNode num[26] = {0};
    pNode p, p1;
    while (scanf("%s", ch) != EOF) {
        if (ch[0] == ch[1] && ch[0] == '^') {
            break;
        }
        p = init_tree(ch[1]);
        num[ch[1] - 'A'] = p;
        if (ch[0] == '^') {
            p1 = p;  
        } else {
            if (ch[2] == 'L') {
                num[ch[0] - 'A']->lchild = p;
            } else {
                num[ch[0] - 'A']->rchild = p;
            }
        }
    }
    output(p1);
    return 0;
}
