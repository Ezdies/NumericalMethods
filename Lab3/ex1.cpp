//Wyznacznik macierzy 

//A 1x1 = det(A) = A11
//A

//Wyznacznik może być tylko dla macierzy kwadratowej

//Dla macierzy większej niż 1 (2) Laplace

#include <iostream>
#include <vector>

void fillMatrix(std::vector<std::vector<int>> &matrix, int rows, int cols){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * cols + j; 
        }
    }
}

void printMatrix(std::vector<std::vector<int>> matrix){
    for(const auto row : matrix){
        for(const auto col : row){
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

int det2x2(std::vector<std::vector<int>> &matrix){
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

bool isMatSquare(int m, int n){
    return m == n;
}

std::vector<std::vector<int>> determinat(std::vector<std::vector<int>> &matrix, int n){
    if(n == 1){
        return matrix[0][0];
    }
    if(n == 2){
        return isMatSquare(matrix.size(), matrix[0].size());
    }
}

int main(){

    int rows = 3;
    int cols = 3;
    
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    fillMatrix(matrix, rows, cols);
    printMatrix(matrix);
}