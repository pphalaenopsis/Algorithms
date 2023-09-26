#include <stdio.h>
#include <stdlib.h>

int *arrayRead(int *);
void merge(int *v, int left, int c, int right, int *aux);
void mergeSortR(int *v, int left, int right, int *aux);
void writeResult(int [], int );

int main() {
    int n, *v, *aux;

    v = arrayRead(&n); //return array, get dimension
    aux = (int *)malloc(n * sizeof(int));
    if (aux==NULL) {
        fprintf(stdout, "memory allocation fault!\n");
        exit(EXIT_FAILURE);
    }

    // call the merge sort recursive, from there the merge on left and right
    mergeSortR(v, 0, n-1, aux);
    writeResult(&v[0], n);

    free(v);
    free(aux);

    return(EXIT_SUCCESS);
}


int *arrayRead(int *n) {
    int i, *v;

    fprintf(stdout, "size: ");
    fscanf(stdin, "%d", &n);
    v = (int *)malloc((*n) * sizeof(int));

    for (i=0; i< *n; i++) {
        fprintf(stdout, "v[&d] = ", i);
        fscanf(stdin, "%d", &v[i]);
    }

    return v;
}

void merge(int *v, int left, int c, int right, int *aux) {
    int i, j, k;

    // i moves on left subarray
    // j moves on right subarray
    // k moves on the auxiliary one

    for (i = left, j=c+1, k=left; i<=c && j<=right;) {
        // <= to make the sorting stable
        if (v[i] <= v[j]) {
            aux[k++] = v[i++];
        }
        else {
            aux[k++] = v[j++];
        }
    }

    // tails
    while(i <= c) {
        aux[k++] = v[i++];
    }
    while(j<=right) {
        aux[k++] = v[j++];
    }

    // copy into the original array
    for (i=left; i<=right; i++) {
        v[i] = aux[i];
    }

    return;
}


void mergeSortR(int *v, int left, int right, int *aux) {
    int c;

    if (left < right) {
        //apply recursion
        c = (left + right) / 2;
        // partition
        mergeSortR(v, left, c, aux);
        mergeSortR(v, c+1, right, aux);
        // sort
        merge(v, left, c, right, aux);
    }

    return;
}


void writeResult(int v[], int length) {

    fprintf(stdout, "Ordered array:\n");
    for (int i=0; i<length; i++) {
        fprintf(stdout, "%d\t", v[i]);
    }

    return;
}