#pragma once

int** fillMatrix(int size) {
    int** matrix = new int* [size];
    for (auto i = 0; i < size; i++) {
        matrix[i] = new int[size];
        for (auto j = 0; j < size; j++)
            matrix[i][j] = 0;
    }
    return matrix;
}
