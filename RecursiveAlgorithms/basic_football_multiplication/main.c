#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void football_multiplication(char **, char *, int, int, FILE *);
char **fileRead(int *dim, char *filename);


int main(int argc, char **argv) {
    char **schema;
    char *sol;
    int n;
    FILE *fp;
    schema = fileRead(&n, argv[1]);
    sol = (char *)malloc(n * sizeof(char));

    fp = fopen(argv[2], "w");
    if (fp == NULL) {
        fprintf(stderr, "error while opening the file!\n");
        exit(EXIT_FAILURE);
    }
    football_multiplication(schema, sol, 0, n, fp);


}

char **fileRead(int *dim, char *filename) {
    FILE *fp;
    char line[10];
    char **schema;
    int i;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error while opening the file!\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%s", line) != EOF) { i++; }
    *dim = i;
    fclose(fp);

    //allocate schema and put the lines inside
    schema = (char **)malloc(i * sizeof(char *));
    if (schema == NULL) {
        fprintf(stderr, "memory allocation fault!\n");
        exit(EXIT_FAILURE);
    }

    fp = fopen(filename, "r");
    for (i=0; i< (*dim); i++) {
        fscanf(fp, "%s", line);
        schema[i] = strdup(line);
    }
    fclose(fp);

    return schema;
}

void football_multiplication(char **schema, char *sol, int pos, int n, FILE *fp) {
    int i;

    // termination: solution has reached the right length == n == number of matches == pos
    if (pos >= n) {
        for(i=0; i<n; i++) {
            fprintf(fp, "%c", sol[i]);
        }
        fprintf(fp, "\n");
        return;
    }

    // still matches to be inserted following multiplication principle
    // one element per set == one element per row
    // recursion level given by row == pos

    for (i=0; i<(strlen(schema[pos])); i++) {
        sol[pos] = schema[pos][i];
        football_multiplication(schema, sol, pos+1, n, fp);
    }

    return;
}
