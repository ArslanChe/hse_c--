#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    const int row = 10;
    const int col = 10;
    int k = -1;
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    while (col * row - 1 > k) {
        while (row > x && y != -1) {
            k += 1;
            table[x][y] = k;
            x += 1;
            y -= 1;
        }
        if (col - 1 > i) {
            i += 1;
            x = 0;
            y = i;
        } else {
            j += 1;
            x = j;
            y = col - 1;
        }
    }
}
