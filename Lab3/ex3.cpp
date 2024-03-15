#include <iostream>
#include <vector>

void fillMatrix(std::vector<std::vector<int>>& matrix, int rows, int cols){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * cols + j; 
        }
    }
}

void printMatrix(const std::vector<std::vector<int>>& matrix){
    for(const auto& row : matrix){
        for(const auto& col : row){
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

int det2x2(const std::vector<std::vector<int>>& matrix){
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

bool isMatSquare(int m, int n){
    return m == n;
}

std::vector<std::vector<int>> t(const std::vector<std::vector<int>>& mat) {
    
    std::vector<std::vector<int>> temp(mat[0].size(), std::vector<int>(mat.size()));

    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            temp[j][i] = mat[i][j];
        }
    }

    return temp;
}

std::vector<std::vector<int>> subMatrix(const std::vector<std::vector<int>>& matrix, int row, int col){
    std::vector<std::vector<int>> sub(matrix.size() - 1, std::vector<int>(matrix.size() - 1));
    for (int i = 0, r = 0; i < matrix.size(); ++i) {
        if (i == row) continue;
        for (int j = 0, c = 0; j < matrix[i].size(); ++j) {
            if (j == col) continue;
            sub[r][c++] = matrix[i][j];
        }
        ++r;
    }
    return sub;
}

int determinant(const std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    if (n == 1) {
        return matrix[0][0];
    } else if (n == 2) {
        return det2x2(matrix);
    } else {
        int det = 0;
        for (int i = 0; i < n; ++i) {
            det += ((i % 2 == 0) ? 1 : -1) * matrix[0][i] * determinant(subMatrix(matrix, 0, i));
        }
        return det;
    }
}

int main(){

    int rows = 3;
    int cols = 3;

    
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    matrix = {{1, 3, 7, 2}, {3, 2, -6, 1}, {1, -1, -1, 2}, {3, 8, 5, 4} };
  //  fillMatrix(matrix, rows, cols);
    printMatrix(matrix);
    
    std::cout << "Determinant: " << determinant(matrix) << std::endl;
    
    return 0;
}
