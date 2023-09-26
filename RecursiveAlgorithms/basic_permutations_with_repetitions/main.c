// here from a collection of n elements, among which
// one or more elements can be repeated, we get
// the permutations by eliminating the options for which
// the same elements A1 and A2 are swapped, with the
// other elements put in the same position
// example A1 A2 B C == A2 A1 B C,
// so we need a mark array to count (== decrease and re-increase)
// the repetitions of certain letters/ values

#include <stdio.h>
#include <stdlib.h>

int permutations_with_repetition(char *, char *, int *, int, int, int, int);

int main() {
    int n_dist = 3; //number of distinct values
    int n = 4; // final size of the collection

    char value[] = {'A', 'B', 'C'};
    char sol[] = {0, 0, 0, 0};
    int mark[] = {2, 1, 1};
    int pos = 0, count = 0, total;

    total = permutations_with_repetition(value, sol, mark, n, pos, count, n_dist);
    fprintf(stdout, "total collections of n = %d elements, with first repeated twice: %d", n, total);

    return(EXIT_SUCCESS);
}


int permutations_with_repetition(char *val, char *sol, int *mark, int n, int pos, int count, int n_dist) {
    int i;

    // termination: solution composed of k elements -> print and increment count
    if (pos >= n) {
        fprintf(stdout, "{ ");
        for (i=0; i<n; i++) {
            fprintf(stdout, "%c ", sol[i]);
        }
        fprintf(stdout, "}\n");
        return count+1;
    }


    for (i=0; i<n_dist; i++) {
        if (mark[i] > 0) {
            // element can be selected
            mark[i] --;
            sol[pos] = val[i];
            count = permutations_with_repetition(val, sol, mark, n, pos+1, count, n_dist);
            mark[i] ++;
        }
    }

    return count;
}
