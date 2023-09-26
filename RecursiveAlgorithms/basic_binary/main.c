#include <stdio.h>
#include <stdlib.h>

#define BASE 2

void binaryNum(int *, int, int);

int main() {
    int n;
    fprintf(stdout, "please, insert the length: \n");
    fscanf(stdin, "%d", &n);

    int *sol;
    sol = (int *)malloc(n*sizeof(int));
    binaryNum(sol, 0, n);

    return(EXIT_SUCCESS);
}

// if we want the count just insert in both return statements (count+1), (count)
void binaryNum(int *sol, int pos, int n) {
    int i;

    // termination: pos >= n == length
    if (pos >= n) {
        for (i = 0; i<n; i++) {
            fprintf(stdout, "%d", sol[i]);
        }
        fprintf(stdout, "\n");
        return;
    }

    // recursion: if the level of recursion is less than that of the required length
    for (i=0; i<BASE; i++) {
        sol[pos] = i;
        binaryNum(sol, pos+1, n);
    }

    return;
}