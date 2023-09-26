#include <stdio.h>
#include <stdlib.h>

int arrangements_with_repetition(int *, int *, int, int, int, int);

int main() {
    int k = 2; // subsets of 2 elements
    int n = 4; // original sets of 4 elements, distinct elements

    int value[] = {4, 9, 0, 1};
    int sol[] = {0, 0};
    int pos = 0, count = 0, total;

    total = arrangements_with_repetition(value, sol, n, k, pos, count);
    fprintf(stdout, "total subsets of k = %d elements: %d", k, total);

    return(EXIT_SUCCESS);
}


int arrangements_with_repetition(int *val, int *sol, int n, int k, int pos, int count) {
    int i;

    // termination: solution composed of k elements -> print and increment count
    if (pos >= k) {
        fprintf(stdout, "{ ");
        for (i=0; i<k; i++) {
            fprintf(stdout, "%d ", sol[i]);
        }
        fprintf(stdout, "}\n");
        return count+1;
    }


    // recur: mark the element and the go onto next level
    // use mark to avoid solutions suck as {4, 4} -> with repetition
    for (i=0; i<n; i++) {
        sol[pos] = val[i];
        count = arrangements_with_repetition(val, sol, n, k, pos+1, count);
    }

    return count;
}