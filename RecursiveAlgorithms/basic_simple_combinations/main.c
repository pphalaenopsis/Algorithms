#include <stdio.h>
#include <stdlib.h>

// similar to simple arrangements, but the first element cannot be reselected
// we need a marking process to take out the elements already used -> no unmarking

int simple_combinations(char *, char *, int, int, int, int, int);

int main() {
    int n = 4; // initial size
    int k = 2; // final size

    char value[] = {'A', 'B', 'C', 'D'};
    char sol[] = {0, 0, 0};

    int pos = 0, count = 0, total;

    total = simple_combinations(value, sol, 0, n, k, pos, count);
    fprintf(stdout, "total sets of n = %d elements, simple combinations: %d", n, total);

    return(EXIT_SUCCESS);
}

int simple_combinations(char *val, char *sol, int start, int n, int k, int pos, int count) {

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
    // remember: the elements you have already taken are not to be re-used after the recursion -> arrangements
    // you can add a start index to not have to restart from zero to process the original array
    for (i = start; i<n; i++) {
        sol[pos] = val[i];
        count = simple_combinations(val, sol, i+1, n, k, pos+1, count);
    }
    return count;
}