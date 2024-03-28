#include "variable_diagonal.h"

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** array = nullptr;
    array = new int*[lines];
    int col = static_cast<int>(columns);
    int row = static_cast<int>(lines);
    for (int i = 0; i < row; ++i) {
        array[i] = new int[columns];
    }
    int k = -1;
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;

    while (col * row - 1 > k) {
        while (row > x && y != -1) {
            k += 1;
            array[x][y] = k;
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

    return array;
}