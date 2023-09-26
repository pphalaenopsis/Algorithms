
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_s node_t;

struct node_s {
    int key;

    node_t *next;
};


FILE *fileUtility(char *);
node_t *nodeAlloc();
node_t *listLoad(char *);
void deallocateList(node_t *);
void listTraversal(node_t *);
void listTraversal2(node_t *);


int main(int argc, char **argv) {
    node_t *head;
    head = listLoad(argv[1]);

    listTraversal(head);
    listTraversal2(head);

    deallocateList(head);
    return(EXIT_SUCCESS);
}


FILE *fileUtility(char *filename) {
    FILE *fp;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

node_t *nodeAlloc() {
    node_t *node;

    node = (node_t *)malloc(sizeof(node_t));
    if (node==NULL) {
        fprintf(stderr, "error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    return node;
}

node_t *listLoad(char *filename) {
    int read;
    node_t *head, *p;
    FILE *fp;
    fp = fileUtility(filename);

    head = NULL;

    while(fscanf(fp, "%d\n", &read)!=EOF) {
        p = nodeAlloc();
        p->key = read;
        p->next = head;
        head = p;
    }

    return head;
}


void deallocateList(node_t *head) {
    node_t *p;

    while(head!=NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}

void listTraversal(node_t *head) {
    if (head == NULL) {
        fprintf(stdout, "\n");
        return;
    }

    fprintf(stdout, "%d\t", head->key);
    listTraversal(head->next);

    return;
}

void listTraversal2(node_t *head) {
    if (head==NULL) {
        return;
    }

    listTraversal2(head->next);
    fprintf(stdout, "%d\t", head->key);

    return;
}

