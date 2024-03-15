#include <iostream>
#include <vector>

void fillMatrix(std::vector<std::vector<int>> &matrix, int rows, int cols)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            matrix[i][j] = i * cols + j;
        }
    }
}

template<typename T>
void printMatrix(const std::vector<std::vector<T>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (const auto &col : row)
        {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
}

int det2x2(const std::vector<std::vector<int>> &matrix)
{
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

bool isMatSquare(int m, int n)
{
    return m == n;
}

std::vector<std::vector<int>> t(const std::vector<std::vector<int>> &mat)
{

    std::vector<std::vector<int>> temp(mat[0].size(), std::vector<int>(mat.size()));

    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat[0].size(); j++)
        {
            temp[j][i] = mat[i][j];
        }
    }

    return temp;
}

std::vector<std::vector<int>> subMatrix(const std::vector<std::vector<int>> &matrix, int row, int col)
{
    std::vector<std::vector<int>> sub(matrix.size() - 1, std::vector<int>(matrix.size() - 1));
    for (int i = 0, r = 0; i < matrix.size(); ++i)
    {
        if (i == row)
            continue;
        for (int j = 0, c = 0; j < matrix[i].size(); ++j)
        {
            if (j == col)
                continue;
            sub[r][c++] = matrix[i][j];
        }
        ++r;
    }
    return sub;
}

int determinant(const std::vector<std::vector<int>> &matrix)
{
    int n = matrix.size();
    if (n == 1)
    {
        return matrix[0][0];
    }
    else if (n == 2)
    {
        return det2x2(matrix);
    }
    else
    {
        int det = 0;
        for (int i = 0; i < n; ++i)
        {
            det += ((i % 2 == 0) ? 1 : -1) * matrix[0][i] * determinant(subMatrix(matrix, 0, i));
        }
        return det;
    }
}

// macierz dopełnień algebraicznych

std::vector<std::vector<int>> cofactorMatrix(const std::vector<std::vector<int>> &matrix)
{
    int n = matrix.size();
    std::vector<std::vector<int>> cofactorMatrix(n, std::vector<int>(n));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            cofactorMatrix[i][j] = sign * determinant(subMatrix(matrix, i, j));
        }
    }

    return cofactorMatrix;
}

// macierz odwrotna

std::vector<std::vector<float>> invertibleMatrix(const std::vector<std::vector<int>>& matrix) {
    float det = 0;
    if (int det_val = determinant(matrix)) {
        det = 1.0f / det_val;
    } else {
        std::cout << "Wyznacznik macierzy == 0\n";
        exit(1);
    }

    std::vector<std::vector<int>> transposedCofactorMatrix = t(cofactorMatrix(matrix));

    std::vector<std::vector<float>> newMatrix(transposedCofactorMatrix.size(), std::vector<float>(transposedCofactorMatrix[0].size()));

    for(int i = 0; i < transposedCofactorMatrix.size(); i++){
        for(int j = 0; j < transposedCofactorMatrix[0].size(); j++){
            newMatrix[i][j] = det * transposedCofactorMatrix[i][j];
        }
    }
    return newMatrix;
}

int main()
{

    int rows = 3;
    int cols = 3;

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    matrix = {{1, 3, 7, 2}, {3, 2, -6, 1}, {1, -1, -1, 2}, {3, 8, 5, 4}};
    //  fillMatrix(matrix, rows, cols);
    std::cout << "Pierwotna macierz:\n\n";
    printMatrix(matrix);
    std::cout << std::endl;
    std::cout << "Determinant: " << determinant(matrix) << std::endl;
    std::cout << "Macierz odwrotna: \n\n";
    std::vector<std::vector<float>> invMatrix = invertibleMatrix(matrix);
    invertibleMatrix(matrix);
    printMatrix(invMatrix);

    return 0;
}
