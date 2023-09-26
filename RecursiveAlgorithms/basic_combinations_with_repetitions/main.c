#include <stdio.h>
#include <stdlib.h>

int combinations_with_repetitions(char *, char *, int, int, int, int, int);

int main() {
    int n = 4; // initial size
    int k = 2; // final size

    char value[] = {'A', 'B', 'C', 'D'};
    char sol[] = {0, 0, 0};

    int pos = 0, count = 0, total;

    total = combinations_with_repetitions(value, sol, 0, n, k, pos, count);
    fprintf(stdout, "total sets of n = %d elements, simple combinations: %d", n, total);

    return(EXIT_SUCCESS);
}

int combinations_with_repetitions(char *val, char *sol, int start, int n, int k, int pos, int count) {
    int i;

    // final condition: we have the k elements
    if (pos >= k) {
        fprintf(stdout, "{ ");
        for (i=0; i<k; i++) {
            fprintf(stdout, "%c ", sol[i]);
        }
        fprintf(stdout, "}\n");
        return count+1;
    }

    // recursion phase
    // can re-use the element you are recurring on
    for (i = start; i<n; i++) {
        sol[pos] = val[i];
        count = combinations_with_repetitions(val, sol, i, n, k, pos+1, count);
    }
    return count;
}