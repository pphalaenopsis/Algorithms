#include <stdio.h>
#include <stdlib.h>
#define N 10

typedef struct set_s {
    int num;
    char element[N];
} value_t;

int multiplication_principle(value_t *value, char *solution, int n, int pos, int count);

int main() {
    // three structs
    value_t set[3];
    //each set has three elements due to the number of sets
    char solution[3];
    int n = 3, pos = 0, count = 0;

    set[0].num = 2;
    set[0].element[0] = 'A';
    set[0].element[1] = 'B';

    set[1].num = 2;
    set[1].element[0] = '0';
    set[1].element[1] = '1';

    set[2].num = 3;
    set[2].element[0] = 'X';
    set[2].element[1] = 'Y';
    set[2].element[2] = 'Z';

    int total;
    total = multiplication_principle(set, solution, n, pos, count);
    fprintf(stdout, "number of solution: %d", total);

    return(EXIT_SUCCESS);
}


int multiplication_principle(value_t *value, char *solution, int n, int pos, int count) {

    int i;

    // final: pos>=n
    if (pos>=n) {
        // print solution
        fprintf(stdout, "{ ");
        for (i=0; i<n; i++) {
            fprintf(stdout, "%c ", solution[i]);
        }
        fprintf(stdout, "}\n");
        return count+1;
    }

    // termination not reached, pos < n
    // recur
    for (i=0; i<value[pos].num; i++) {
        solution[pos] = value[pos].element[i];
        count = multiplication_principle(value, solution, n, pos+1, count);
    }

    return count;
}
