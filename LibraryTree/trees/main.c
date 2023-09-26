#include <stdio.h>
#include <stdlib.h>

typedef struct node_s node_t;
struct node_s
{
    int val;

    node_t *right;
    node_t *left;
};

// functions
node_t *emptyTree();
node_t *nodeAlloc();
node_t *addNode(node_t *, int);
node_t *treeLoad(node_t *, FILE *);
FILE *fileUtility(char *);

void disposeTree(node_t *);
void printTree(node_t *root);
void postOrder(node_t *root);
void preOrder(node_t *root);

// more functions
int countNodes(node_t *);
int heightTree(node_t *);

void countNode(node_t *root, int *array);
int countNodeAlternative(node_t *root, int *array);

void countLevel(node_t *root, int *array, int l);
void countPath(node_t *root, int *np, int *length);
int visit(node_t *root, int key1, int key2);

// revision trees
int main(int argc, char **argv)
{
    node_t *root;
    FILE *fp;

    root = NULL;
    root = emptyTree();

    if (argc < 2)
    {
        fprintf(stdout, "Invalid number of parameters on command line.\n");
        return (EXIT_FAILURE);
    }

    fp = fileUtility(argv[1]);
    root = treeLoad(root, fp);

    // operations
    printTree(root);
    fprintf(stdout, "\n");

    postOrder(root);
    fprintf(stdout, "\n");

    preOrder(root);
    fprintf(stdout, "\n");

    int nodes, height;
    height = heightTree(root);
    fprintf(stdout, "Height: %d\n", height);
    nodes = countNodes(root);
    fprintf(stdout, "Number of nodes: %d\n", nodes);

    int array[] = {0, 0, 0, 0, 0, 0, 0};
    countLevel(root, array, height);
    fprintf(stdout, "number of children per level:\n");
    for (int i = 0; i < height; i++)
    {
        fprintf(stdout, "%d ", array[i]);
    }

    int childrenPerNode[] = {0, 0, 0};
    int childrenPerNodeAlt[] = {0, 0, 0};
    int alt = 0;
    alt = countNodeAlternative(root, childrenPerNodeAlt);
    countNode(root, childrenPerNode);
    fprintf(stdout, "\nMethod one:\n", alt);
    for (int i = 0; i < 3; i++)
    {
        fprintf(stdout, "%d ", childrenPerNode[i]);
    }
    fprintf(stdout, "\nMethod two:\n");
    for (int i = 0; i < 3; i++)
    {
        fprintf(stdout, "%d ", childrenPerNodeAlt[i]);
    }

    int paths, edges;
    countPath(root, &paths, &edges);
    fprintf(stdout, "\nNumber of paths %d\nNumber of edges %d\n", paths, edges);

    int lengthPath;
    lengthPath = visit(root, 1, 2);
    fprintf(stdout, "Distance of the two nodes: %d\n", lengthPath);

    disposeTree(root);
    fclose(fp);

    return (EXIT_SUCCESS);
}

// Stores in each element array[i] the total number of nodes of the tree at level i
void countLevel(node_t *root, int *array, int l)
{
    if (root != NULL)
    {
        array[l - 1]++;
        countLevel(root->left, array, l - 1);
        countLevel(root->right, array, l - 1);
    }
}

// Stores in the three elements of the array the number of nodes with
// no child, with one single child, and with two children, respectively
void countNode(node_t *root, int *array)
{

    // empty
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
        array[0]++;
    if ((root->left == NULL && root->right != NULL) ||
        (root->left != NULL && root->right == NULL))
        array[1]++;
    if (root->right != NULL && root->left != NULL)
        array[2]++;

    countNode(root->right, array);
    countNode(root->left, array);

    return;
}

int countNodeAlternative(node_t *root, int *array)
{
    int l, r;

    if (root == NULL)
        return 0;

    l = countNodeAlternative(root->left, array);
    r = countNodeAlternative(root->right, array);

    array[l + r]++;
    return (1);
}

// counts the number of paths ending in a leaf
// and the number of the vertices covered
void countPath(node_t *root, int *np, int *length)
{

    if (root == NULL)
        return;

    *length = *length + 1;
    if (root->left == NULL && root->right == NULL)
    {
        // on a leaf
        *np = *np + 1;
        return;
    }

    countPath(root->left, np, length);
    countPath(root->right, np, length);

    return;
}

int visitS(node_t *root, int key)
{
    int distance;

    if (root == NULL)
    {
        return (-1);
    }

    if (key < root->val)
    {
        distance = visitS(root->left, key);
        return (distance + 1);
    }

    if (key > root->val)
    {
        distance = visitS(root->right, key);
        return (distance + 1);
    }

    // if (compare (root->val, key) == 0)
    return (0);
}

// distance between two nodes in a BST
// check the respective position of the two nodes
// same subtree or different subtree
// in the second case we pass through the root

int visit(node_t *root, int key1, int key2)
{
    int length;
    int left, right;

    if (root == NULL)
        return 0;

    if (root->val < key2 && root->val < key1)
        length = visit(root->right, key1, key2);
    else
    {
        if (root->val > key1 && root->val > key2)
            length = visit(root->left, key1, key2);
        else
        {
            // different subtree
            left = visitS(root, key1);
            right = visitS(root, key2);
            length = left + right;
        }
    }

    return (length);
}

int countNodes(node_t *root)
{
    int l, r;

    if (root == NULL)
        return 0;

    r = countNodes(root->right);
    l = countNodes(root->left);
    return l + r + 1;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int heightTree(node_t *root)
{
    int l = 0, r = 0;
    if (root == NULL)
        return -1;

    l += heightTree(root->left);
    r += heightTree(root->right);

    return max(l, r) + 1;
}

node_t *emptyTree()
{
    return NULL;
}

node_t *nodeAlloc()
{
    node_t *node;
    node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        fprintf(stderr, "Error memory allocation\n");
        exit(EXIT_FAILURE);
    }

    return node;
}

node_t *addNode(node_t *root, int value)
{
    // BST: left for smaller values
    // right for bigger values
    // suppose no duplicates
    node_t *node;

    if (root == NULL)
    {
        // position found -> always insert on leaf
        node = nodeAlloc();
        node->val = value;
        node->right = node->left = NULL;
        return (node);
    }

    // else, recur respecting the property
    if (root->val < value)
        // right
        root->right = addNode(root->right, value);
    if (root->val > value)
        root->left = addNode(root->left, value);

    if (root->val == value)
        return (root); // do not consider the duplicates

    // finally
    return (root);
}

node_t *treeLoad(node_t *root, FILE *fp)
{
    // suppose one value per line in the file (credo eh)
    int key = 0;
    while (fscanf(fp, "%d", &key) != EOF)
    {
        root = addNode(root, key);
    }

    return root;
}

FILE *fileUtility(char *filename)
{
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error file opening\n");
        exit(EXIT_FAILURE);
    }
    return fp;
}

void disposeTree(node_t *root)
{
    if (root == NULL)
        return;

    disposeTree(root->left);
    disposeTree(root->right);

    free(root);
}

void printTree(node_t *root)
{
    if (root == NULL)
        return;

    printTree(root->left);
    fprintf(stdout, "%d\t", root->val);
    printTree(root->right);
}

void postOrder(node_t *root)
{

    if (root == NULL)
    {
        return; // empty tree
    }

    postOrder(root->left);
    postOrder(root->right);
    fprintf(stdout, "%d\t", root->val);
}

void preOrder(node_t *root)
{
    if (root == NULL)
        return;

    fprintf(stdout, "%d\t", root->val);
    preOrder(root->left);
    preOrder(root->right);
}