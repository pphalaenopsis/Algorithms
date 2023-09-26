#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

// anagrams having same letter only once
void simple_permutation(char *word, char *sol, int *mark, int pos, int n);

int main() {
    char word[MAX];
    int used[MAX];
    char sol[MAX];

    fprintf(stdout, "enter a word:\n");
    fscanf(stdin, "%s", word);

    int n;
    n = strlen(word);

    // array to check if the element has already been used
    for (int j = 0; j<n; j++) {
        used[j] = 0;
    }

    simple_permutation(word, sol, used, 0, n);

    return(EXIT_SUCCESS);

}

void simple_permutation(char *word, char *sol, int *mark, int pos, int n) {
   int i;

    //termination
    if (pos >= n) {
        fprintf(stdout, "%s\n", sol);
        return;
    }


    // not yet completed: take whatever letter excluding the one you recur on
    // mark and unmark after usage

    for (i=0; i<n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = word[i];
            simple_permutation(word, sol, mark, pos+1, n);
            mark[i] = 0;
        }
    }

    return;
}