#include <stdio.h>
#include <stdlib.h>

int simple_permutations(int *, int *, int *, int, int, int);

int main() {
    int n = 4; // orignal sets of 4 elements, distinct elements
    int k = n; // subsets of 4 elements, simple permutations

    int value[] = {4, 9, 0, 1};
    int sol[] = {0, 0, 0, 0};
    int mark[] = {0, 0, 0, 0};
    int pos = 0, count = 0, total;

    total = simple_permutations(value, sol, mark, n, pos, count);
    fprintf(stdout, "total subsets of k = n = %d elements: %d", k, total);

    return(EXIT_SUCCESS);
}


int simple_permutations(int *val, int *sol, int *mark, int n, int pos, int count) {
    int i;

    // termination: solution composed of k elements -> print and increment count
    if (pos >= n) {
        fprintf(stdout, "{ ");
        for (i=0; i<n; i++) {
            fprintf(stdout, "%d ", sol[i]);
        }
        fprintf(stdout, "}\n");
        return count+1;
    }


    // recur: mark the element and the go onto next level
    // here k = n, take subsets of n elements, where the elements are just shuffled
    for (i=0; i<n; i++) {
        if (mark[i] == 0) {
            // element can be selected
            mark[i] = 1;
            sol[pos] = val[i];
            count = simple_permutations(val, sol, mark, n, pos+1, count);
            mark[i] = 0;
        }
    }

    return count;
}