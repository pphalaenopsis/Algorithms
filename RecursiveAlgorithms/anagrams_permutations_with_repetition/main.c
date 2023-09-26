#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define ALPHA 26

// conversion letter-position in frequency array ((int) word[i])-65

// anagrams having same letter only once
void permutations_with_repetition(char *sol, int *mark, int pos, int n);

int main() {
    char word[MAX];
    // check the frequency of each letter in the word -> mark
    int frequency[ALPHA];
    char sol[MAX];

    fprintf(stdout, "enter a word:\n");
    fscanf(stdin, "%s", word);

    int n, j;
    n = strlen(word);
    j = ((int) word[0])-65;

    // assume we use A...Z
    for (j = 0; j<ALPHA; j++) { frequency[j] = 0; }

    // array to check if the element has already been used
    for (int i = 0; i<n; i++) {
        j = ((int) word[i])-65;
        frequency[j]++;
    }

    permutations_with_repetition(sol, frequency, 0, n);

    return(EXIT_SUCCESS);
}

void permutations_with_repetition(char *sol, int *mark, int pos, int n) {
    int i;

    // termination
    if (pos >= n) {
        fprintf(stdout, "%s\n", sol);
        return;
    }

    // not termination -> recur, decrease the availability of a character, then re-increase after recursion
    for (i=0; i<ALPHA; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = (char)(i+65);
            permutations_with_repetition(sol, mark, pos+1, n);
            mark[i]++;
        }
    }

    return;
}