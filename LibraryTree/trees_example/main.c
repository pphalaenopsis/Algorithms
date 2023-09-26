#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define PREORDER (-1)
#define INORDER 0
#define POSTORDER 1
#define INSERTION 2
#define EXTRACTION (-2)

/*
 * (0. correctly implement, allocate and get values for tree
 * using a BST, preferably)
 * 1. visit the tree IN-ORDER PRE-ORDER POST-ORDER X
 * 2. compute number of nodes X
 * 3. compute the height X
 * 4. compute man, min (recursive) X
 * 5. try with n-ary tree (int degree, node_t **children)
 * 6. perform insertions X
 * 7. perform deletions X
 * 8. search X
 * 9. deallocate it X
 * 10. implement it as an interface for the user
 */

// data structure
typedef struct node_s node_t;

struct node_s
{
    int key;
    node_t *l, *r;
};

node_t *createEmptyTree();
node_t *nodeAlloc();
void treeDispose(node_t *);

FILE *fileUtility(char *);
node_t *addNode(node_t *, int); // addNode == insert operation
node_t *treeLoad(node_t *, FILE *);

int numNodes(node_t *);
int height(node_t *);
void printPreorder(node_t *);
void printInorder(node_t *);
void printPostorder(node_t *);
void printNode(node_t *);

node_t *searchNode(node_t *, int);
node_t *searchNodeIt(node_t *, int);

node_t *maxN(node_t *);
node_t *minN(node_t *);
node_t *maxNI(node_t *);
node_t *minNI(node_t *);

node_t *deleteNode(node_t *root, int key);
node_t *deletePutMax(node_t *root, int *keyVal);
node_t *deletePutMin(node_t *root, int *keyVal);

// get file for data values
int main(int argc, char **argv)
{
    node_t *root;
    FILE *fp;
    int printProcessing;
    int nodesN;
    node_t *min, *max;
    node_t *search;

    root = NULL;
    root = createEmptyTree();

    // pass the file for processing, get tree
    if (argc < 2)
    {
        fprintf(stdout, "Invalid number of parameters on command line.\n");
        return (EXIT_FAILURE);
    }
    fp = fileUtility(argv[1]);
    root = treeLoad(root, fp);

    max = maxN(root);
    min = minN(root);
    fprintf(stdout, "Max (%d) and min (%d).\n", max->key, min->key);

    // operations
    fprintf(stdout, "Enter the desired print processing:\n-1 PRE-ORDER\t0 IN-ORDER\t1 POST-ORDER\n");
    fscanf(stdin, "%d", &printProcessing);
    switch (printProcessing)
    {
    case PREORDER:
        fprintf(stdout, "PRE-ORDER: ");
        printPreorder(root);
        break;
    case INORDER:
        fprintf(stdout, "IN-ORDER: ");
        printInorder(root);
        break;
    case POSTORDER:
        fprintf(stdout, "POST-ORDER: ");
        printPostorder(root);
        break;
    default:
        fprintf(stdout, "default method IN-ORDER: ");
        printInorder(root);
        break;
    }
    fprintf(stdout, "\n");

    nodesN = numNodes(root);
    fprintf(stdout, "Number of nodes: %d\n", nodesN);
    nodesN = height(root);
    fprintf(stdout, "Height: %d\n", nodesN);

    int val2;
    fprintf(stdout, "Looking for a node? Input KEY value:\n");
    fscanf(stdin, "%d", &val2);
    while (isdigit(val2))
    {
        search = searchNode(root, val2);
        if (search != NULL)
        {
            printNode(search);
        }
        else
            fprintf(stdout, "Node not found, try again.\n");
        fscanf(stdin, "%d", &val2);
    }

    fprintf(stdout, "GOODBYE :)");
    treeDispose(root);
}

FILE *fileUtility(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stdout, "Error while opening file %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    return fp;
}

node_t *nodeAlloc()
{
    node_t *node;
    node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        fprintf(stdout, "Memory allocation fault.\n");
        exit(EXIT_FAILURE);
    }
    return (node);
}

node_t *createEmptyTree()
{
    return NULL;
}

void printNode(node_t *node)
{
    fprintf(stdout, "Node:\t%d\n", node->key);
}

node_t *addNode(node_t *root, int key)
{
    node_t *newNode;

    /*BST property: new->key < root->key element goes left
     * in all cases, in BST newNode is always inserted on a leaf
     * new->key > root->key element goes right
     * duplicates are not considered :)
     */

    // terminal condition: empty tree or leaf
    if (root == NULL)
    {
        newNode = nodeAlloc();
        newNode->key = key;
        newNode->l = newNode->r = NULL;
        return (newNode);
    }

    // else: look for position respecting the BST property, manage duplicates
    if (root->key < key)
        // right
        root->r = addNode(root->r, key);
    if (root->key > key)
        root->l = addNode(root->l, key);
    if (root->key == key)
        return (root);

    return (root);
}

node_t *treeLoad(node_t *root, FILE *fileP)
{
    int key;

    while (fscanf(fileP, "%d", &key) != EOF)
    {
        root = addNode(root, key);
    }

    return (root);
}

void printPreorder(node_t *root)
{

    if (root == NULL)
    {
        return; // empty tree
    }

    fprintf(stdout, "%d\t", root->key);
    printPreorder(root->l);
    printPreorder(root->r);
}

void printInorder(node_t *root)
{

    if (root == NULL)
    {
        return; // empty tree
    }

    printInorder(root->l);
    fprintf(stdout, "%d\t", root->key);
    printInorder(root->r);
}

void printPostorder(node_t *root)
{

    if (root == NULL)
    {
        return; // empty tree
    }

    printPostorder(root->l);
    printPostorder(root->r);
    fprintf(stdout, "%d\t", root->key);
}

void treeDispose(node_t *root)
{

    // empty
    if (root == NULL)
    {
        return;
    }

    treeDispose(root->l);
    treeDispose(root->r);
    free(root);
}

int numNodes(node_t *root)
{
    int l, r;

    if (root == NULL)
    {
        return 0;
    }
    l = numNodes(root->l);
    r = numNodes(root->r);

    return (l + r + 1);
}

int height(node_t *root)
{
    int ll, lr;

    if (root == NULL)
    {
        return (-1);
    }
    ll = height(root->l);
    lr = height(root->r);

    if (ll < lr)
    {
        return (lr + 1);
    }
    else
    {
        return (ll + 1);
    }
}

node_t *searchNode(node_t *root, int key)
{
    if (root == NULL)
    {
        return (NULL);
    } // miss

    // make use of the BST property
    if (key > root->key)
    {
        return (searchNode(root->r, key));
    }
    if (key < root->key)
    {
        return (searchNode(root->l, key));
    }
    return (root); // hit
}

node_t *searchNodeIt(node_t *root, int key)
{

    while (root != NULL)
    {
        if (key == root->key)
            return (root); // hit

        if (key < root->key)
            root = root->l;
        else
            root = root->r;
    }
    return (NULL); // miss
}

// max == rightmost leaf
node_t *maxN(node_t *root)
{
    if (root == NULL)
    {
        return NULL;
    } // empty tree

    if (root->r == NULL)
    {
        return (root);
    }
    return maxN(root->r);
}

// min == leftmost leaf
node_t *minN(node_t *root)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->l == NULL)
    {
        return (root);
    }
    return minN(root->l);
}

// iterative implementations
node_t *minNI(node_t *root)
{
    if (root == NULL)
    {
        return NULL;
    } // empty tree

    while (root->l != NULL)
    {
        root = root->l;
    }
    return (root);
}

node_t *maxNI(node_t *root)
{
    if (root == NULL)
    {
        return (NULL);
    }

    while (root->r != NULL)
    {
        root = root->r;
    }
    return (root);
}

node_t *deleteNode(node_t *root, int key)
{
    node_t *p;
    int keyVal;

    if (root == NULL)
    {
        return NULL;
    }

    if (key > root->key)
    {
        root->r = deleteNode(root, key);
    }
    if (key < root->key)
    {
        root->l = deleteNode(root, key);
    }

    // hit
    // one child: left, right
    if (root->r == NULL)
    {
        root = root->l;
        root->l = NULL;
        return (root);
    }
    if (root->l == NULL)
    {
        root = root->r;
        root->r = NULL;
        return (root);
    }
    if (root->l == NULL && root->r == NULL)
    {
        root = NULL;
        return (root);
    }

    // two children: find either max in left subtree or min in right subtree
    root->l = deletePutMax(root, &keyVal);
    root->key = keyVal;
    return (root);
}

node_t *deletePutMax(node_t *root, int *keyVal)
{
    node_t *tmp;

    if (root->r == NULL)
    {
        // copy data max and free
        *keyVal = root->key;
        tmp = root->l;
        free(root);
        // return possible left child, NULL or not
        return (tmp);
    }

    // recursion
    root->r = deletePutMax(root->r, keyVal);
    return (root);
}

node_t *deletePutMin(node_t *root, int *keyVal)
{
    node_t *tmp;

    if (root->l == NULL)
    {
        *keyVal = root->key;
        tmp = root->r;
        free(root);
        return (tmp);
    }

    root->l = deletePutMin(root->l, keyVal);
    return (root);
}