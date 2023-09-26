#include <stdio.h>

int printPartition(int num[], int, int);

int main() {
    int numbers[]={1,2,3,4,5,6,7,8};
    int max = printPartition(numbers, 0, 8);

    fprintf(stdout, "%d", max);
    return 0;
}

int printPartition(int num[], int l, int r) {

    int c, m1, m2;

    if (l>=r) {return num[l];}

    c=(l+r)/2;
    //divide: sub-problems, partitions
    m1 = printPartition(num, l, c);
    m2 = printPartition(num, c+1, r);

    if (m1>m2) {return m1;}
    else return m2;

}