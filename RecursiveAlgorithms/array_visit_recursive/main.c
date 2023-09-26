#include <stdio.h>
#include <stdlib.h>

#define N 10

void array_rec(int *, int *, int *, int);

int main() {
    int v[N] = {1,3,5,7,9,11,8,6,4,2};
    int min, max;

    fprintf(stdout, "array:\t");
    array_rec(&v[0], &min, &max, 0);
    fprintf(stdout, "max %d min %d\n", max, min);

    return(EXIT_SUCCESS);
}


void array_rec(int *v, int *min, int *max, int n) {
    // termination
    if (n >= N)
        return;

    fprintf(stdout, "%d\t", *v);

    if ((*v) > (*max))
        *max = *v;
    if ((*v) < (*min))
        *min = *v;

    // recur on next element v+1 at position n+1
    array_rec(v+1, min, max, n+1);

    return;

}