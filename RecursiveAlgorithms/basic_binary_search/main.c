#include <stdio.h>
#include <stdlib.h>
#define N 20

int binary_search(int *,int, int, int);

int main () {
    //take the array from stdin
    int v[N], i=0, pos, num;

    fprintf(stdout, "insert elements of array one by one, ENTER to stop.\n");
    for (i=0; i<N; i++) {
        scanf("%d", &v[i]);

    }
    fprintf(stdout, "available number of elements: %d\n", i);
    fprintf(stdout, "Number to be searched:\n");
    fscanf(stdin, "%d", &num);
    pos = binary_search(&v[0],0, i, num);


    // found or not
    if (pos >= 0) {
        fprintf(stdout, "value %d found in position %d\n", num, pos);
    }
    else { fprintf(stdout, "value %d not found.\n", num); }

    return(EXIT_SUCCESS);
}

int binary_search(int *v,int left, int right, int num) {
    int c; //define the center and recursively compare with the element

    // termination: all array visited, number not found
    if (left > right) {
        return (-1);
    }

    c = (left + right) / 2;
    if (num > v[c]) {
        return binary_search(v, c+1, right, num);
    }
    if (num < v[c]) {
        return binary_search(v, left, c, num);
    }
    //found
    return c;
}
