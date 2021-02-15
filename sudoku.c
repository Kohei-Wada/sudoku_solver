#include <stdio.h>
#include <stdlib.h>


#define STAGE_X 9
#define STAGE_Y 9

int **array = NULL;


int sudoku[STAGE_X][STAGE_Y] = {
    {0, 0, 0, 9, 0, 6, 4, 0, 0},
    {0, 7, 0, 0, 5, 0, 0, 0, 3},
    {8, 0, 0, 4, 0, 0, 0, 0, 0},
    {1, 0, 9, 0, 0, 0, 0, 7, 5},
    {0, 0, 5, 8, 0, 0, 2, 0, 0},
    {0, 4, 0, 0, 0, 0, 0, 0, 0},
    {3, 0, 0, 1, 0, 9, 0, 5, 0},
    {0, 0, 0, 0, 2, 8, 0, 9, 0},
    {5, 0, 0, 0, 0, 0, 0, 8, 0}
};


void display(int **array)
{
    int x, y;

    for (y = 0; y < STAGE_Y; ++y) {
        printf("[");
        for (x = 0; x < STAGE_X; ++x) {
            if (!array[x][y]) printf(" *");
            else printf("%2d", array[x][y]);
        }
        printf(" ]\n");
    }
    printf("\n");
}


int is_possible(int x, int y, int n)
{
    int i , j, x0, y0;

    for (i = 0; i < STAGE_X; ++i)
        if (array[i][y] == n ) return 0;

    for (j = 0; j < STAGE_Y; ++j)
        if (array[x][j] == n) return 0;

    x0 = x/3 * 3; y0 = y/3 * 3;
    for (j = 0; j < 3; ++j)
        for (i = 0; i < 3; ++i)
            if (array[x0 + i][y0 + j] == n) return 0;

    return 1;
}


void solve(void)
{
    int x, y, i;

    for (y = 0; y < STAGE_Y; ++y) {
        for (x = 0 ; x < STAGE_X; ++x) {
            if (!array[x][y]) {
                for (i = 1; i < 10 ; ++i) {
                    if (is_possible(x, y, i)) {
                        array[x][y] = i;
                        solve();
                        array[x][y] = 0;
                    }
                }
                return;
            }
        }
    }
    display(array);
}


void free_array(int **array)
{
    for (int x = 0; x < STAGE_X; ++x) free(array[x]);
    free(array);
}


int **init_array(void)
{
    int x, y;
    int **array = malloc(sizeof(int *) * STAGE_X);
    if (!array) goto fail;

    for (x = 0; x < STAGE_X; ++x) {
        array[x] = malloc(sizeof(int) * STAGE_Y);
        if (!array[x]) goto fail;
    }

    for (y = 0; y < STAGE_Y; ++y)
        for (x = 0; x < STAGE_X; ++x)
            array[x][y] = sudoku[y][x];

    return array;

  fail: perror("malloc"), exit(1);
}


int main(void)
{
    array = init_array();
    display(array);
    solve();
    free_array(array);
    return 0;
}
