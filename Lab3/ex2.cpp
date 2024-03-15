#include <iostream>
#include <vector>

std::vector<std::vector<int>> t(const std::vector<std::vector<int>>& mat) {
    
    std::vector<std::vector<int>> temp(mat[0].size(), std::vector<int>(mat.size()));

    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            temp[j][i] = mat[i][j];
        }
    }

    return temp;
}

void printMat(const std::vector<std::vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector<std::vector<int>> mat{{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> newMat = t(mat);
    printMat(newMat);

    return 0;
}
