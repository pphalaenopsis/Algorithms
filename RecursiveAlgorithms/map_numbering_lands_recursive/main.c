#include <stdio.h>
#include <stdlib.h>
#define DIM 20

void mapRead(char *, int [DIM][DIM], int *, int *);
void mapWrite(char *, int [DIM][DIM], int, int, int);
void numbering(int [DIM][DIM], int, int, int);

int main(int argc, char **argv) {
    // load the map with (-1) for the lands to mark
    int map[DIM][DIM];
    int i, j, nr, nc, n=0;

    mapRead(argv[1], map, &nr, &nc);


    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            if (map[i][j] == (-1)) {
                numbering(map, i, j, ++n);
            }
        }
    }

    mapWrite(argv[2], map, nr, nc, n);
    return EXIT_SUCCESS;

}


void mapRead(char *filename, int map[DIM][DIM], int *nr, int *nc) {
    char line[DIM+2];
    int i, j;
    FILE *fp;
    fp = fopen(filename, "r");
    //check file

    i=0;
    while(fscanf(fp, "%s\n", line)!=EOF) {
        // build map
        j=0;
        while (j<DIM && (line[j]=='.' || line[j]=='*')) {
            map[i][j]=(line[j] == '*' ? 0 : -1);
            // 0 for borders, -1 for land
            j++;
        }
        i++;
    }

    fclose(fp);
    *nr = i;
    *nc = j;

    return;
}


void mapWrite(char *filename, int map[DIM][DIM], int nr, int nc, int n) {
    FILE *fp;
    int i, j;

    fp = fopen(filename, "w");
    //check file

    for (i=0; i<nr; i++) {
        for (j=0; j<nc; j++) {
            if (map[i][j] == 0) {
                fprintf(fp, "*");
            }
            else {
                fprintf(fp, "%d", map[i][j]);
            }
        }
        fprintf(fp, "\n");
    }

    fprintf(stdout, "Regions number = %d", n);
    fclose(fp);
    return;
}


// initially n=0, no number yet positioned, all land values set to (-1)
void numbering(int map[DIM][DIM], int x, int y, int n) {

    int i, xx, yy;
    const int movex[] = {0, 0, -1, 1};
    const int movey[] = {-1, 1, 0, 0};

    // termination: the position is set to a value != -1
    if (map[x][y] != -1) { return; }

    // else, set value, no backtracking, it needs to be set to
    // another fixed and sure value

    map[x][y] = n;

    for (i = 0; i<4; i++) {
        xx = x + movex[i];
        yy = y + movey[i];
        numbering(map, xx, yy, n);
    }
    return;
}