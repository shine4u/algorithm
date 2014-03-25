#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define REP(i, n) for(int i=0; i<(n); i++)
#define RAND(a, b) (rand()%(b-a)+a)

/* statement: 
 * given a binary tree T with root R. for any node N of T, the nodes of the left subtree of 
 * N, named LS(N) are all strictly less than the nodes of the right subtree of N, named RS(N).
 * now, you are to convert the tree T to a list L with increasing order. return the head node
 * of L.
 * datarange:
 * the weight of node W(0<=W<10000)
 */

typedef struct struct_node_t {
    int w;
    struct struct_node_t *left;
    struct struct_node_t *right;
    struct struct_node_t *next;
} node_t;
typedef node_t *tree_t;

const int MAXW = 100000;

void gen_sub_node(node_t *&node, int minw, int maxw, int level) {
    if (minw >= maxw) {
        node = NULL;
        return ;
    }
    node = new node_t;
    node->w = RAND(minw, maxw);
    int partition = RAND(minw, maxw);
    gen_sub_node(node->left, minw, partition, level+1);
    gen_sub_node(node->right, partition+1, maxw, level+1);
}

tree_t gen_bin_tree() {
    node_t *root = new node_t;
    gen_sub_node(root, 0, MAXW, 0);
    return (tree_t)root;
}

void print_tree(node_t *node) {
    if (!node) return ;
    int leftw = (node->left?node->left->w:-1);
    int rightw = (node->right?node->right->w:-1);
    printf("node[%d], left[%d], right[%d]\n", node->w, leftw, rightw);
    print_tree(node->left);
    print_tree(node->right);
}

void work(node_t *node, node_t *&head, node_t *&tail) {
    if (node == NULL) {
        head = NULL;
        tail = NULL;
        return ;
    }
    node_t *lefthead, *lefttail, *righthead, *righttail;
    work(node->left, lefthead, lefttail);
    work(node->right, righthead, righttail);

    if (node->left==NULL && node->right==NULL) {
        head = node;
        tail = node;
        node->next = NULL;
    } else if (node->left == NULL) {
        node_t *p1 = NULL, *p2 = righthead;
        while (1) {
            if (p1 == NULL && node->w <= p2->w) break;
            if (p2 == NULL && p1->w <= node->w) break;
            if (p1 && p2 && p1->w <= node->w && node->w <= p2->w) break;
            p1 = p2;
            p2 = p2->next;
        }
        if (p1 == NULL) {
            node->next = p2;
            head = node;
            tail = righttail;
        } else if (p2 == NULL) {
            p1->next = node;
            node->next = NULL;
            head = righthead;
            tail = node;
        } else {
            p1->next = node;
            node->next = p2;
            head = righthead;
            tail = righttail;
        }
    } else if (node->right == NULL) {
        node_t *p1 = NULL, *p2 = lefthead;
        while (1) {
            if (p1 == NULL && node->w <= p2->w) break;
            if (p2 == NULL && p1->w <= node->w) break;
            if (p1 && p2 && p1->w <= node->w && node->w <= p2->w) break;
            p1 = p2;
            p2 = p2->next;
        }
        if (p1 == NULL) {
            node->next = p2;
            head = node;
            tail = lefttail;
        } else if (p2 == NULL) {
            p1->next = node;
            node->next = NULL;
            head = lefthead;
            tail = node;
        } else {
            p1->next = node;
            node->next = p2;
            head = lefthead;
            tail = lefttail;
        }

    } else {
        if (node->w <= lefthead->w) {
            node->next = lefthead;
            lefttail->next = righthead;
            head = node;
            tail = righttail;
        } else if (righttail->w <= node->w) {
            righttail->next = node;
            node->next = NULL;
            lefttail->next = righthead;
            head = lefthead;
            tail = node;
        } else if (lefttail->w <= node->w && node->w <= righthead->w) {
            lefttail->next = node;
            node->next = righthead;
            head = lefthead;
            tail = righttail;
        }
        else {
            node_t *head2, *tail2;
            if (node->w <= lefttail->w) {
                head2 = lefthead;
                tail2 = lefttail;
            } else {
                head2 = righthead;
                tail2 = righttail;
            }
            node_t *p1 = head2, *p2 = head2->next;
            while(1) {
                if (p1->w <= node->w && node->w <=p2->w) break;
                p1 = p2;
                p2 = p2->next;
            }
            p1->next = node;
            node->next = p2;
            lefttail->next = righthead;
            head = lefthead;
            tail = righttail;
        }
    }
}
int main(int argc, char **argv) {
    srand(11);
    REP(i, 5) {
        printf("\n\nCase %d\n", i);
        tree_t tree = gen_bin_tree();
        print_tree(tree);
        node_t *head, *tail;
        work(tree, head, tail);
        while(head) {
            printf("%d->", head->w);
            head = head->next;
        }
        printf("\n");
    }
    return 0;
}
