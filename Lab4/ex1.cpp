#include <iostream>
#include <vector>
#include <cmath>

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

std::vector<float> vec_x(const std::vector<std::vector<int>>& A, const std::vector<int> &b){
    std::vector<std::vector<float>> invMatrix = invertibleMatrix(A);
    std::vector<float> vector_x(A.size(), 0);
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            vector_x[i] += invMatrix[i][j] * b[j];
        }
    }
    return vector_x;
}

void LU(const std::vector<std::vector<int>>& A, std::vector<std::vector<float>>& L, std::vector<std::vector<float>>& U) {
    int n = A.size();
    L.resize(n, std::vector<float>(n, 0));
    U.resize(n, std::vector<float>(n, 0));

    for (int i = 0; i < n; i++) {
        U[i][i] = 1;
        for (int j = 0; j <= i; j++) {
            L[i][j] = A[i][j];
            for (int k = 0; k < j; k++) {
                L[i][j] -= L[i][k] * U[k][j];
            }
        }

        for (int j = i + 1; j < n; j++) {
            U[i][j] = A[i][j];
            for (int k = 0; k < i; k++) {
                U[i][j] -= L[i][k] * U[k][j];
            }
            U[i][j] /= L[i][i];
        }
    }
}

std::vector<std::vector<float>> matrixMultiplication(const std::vector<std::vector<float>>& A, const std::vector<std::vector<float>>& B) {
    int rows_A = A.size();
    int cols_A = A[0].size();
    int cols_B = B[0].size();

    std::vector<std::vector<float>> C(rows_A, std::vector<float>(cols_B, 0));

    for (int i = 0; i < rows_A; ++i) {
        for (int j = 0; j < cols_B; ++j) {
            for (int k = 0; k < cols_A; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

std::vector<std::vector<float>> choleskyDecomposition(const std::vector<std::vector<int>>& A) {
    int n = A.size();
    std::vector<std::vector<float>> L(n, std::vector<float>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            float sum = 0;

            if (i == j) {
                for (int k = 0; k < j; ++k) {
                    sum += pow(L[j][k], 2);
                }
                L[j][j] = sqrt(A[j][j] - sum);
            } else {
                for (int k = 0; k < j; ++k) {
                    sum += (L[i][k] * L[j][k]);
                }
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }

    return L;
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

    std::vector<std::vector<int>> A = {{1, 2, 1}, {3, -7, 2}, {2, 4, 5}};
    std::vector<int> b = {-9, 61, -9};

    auto x = vec_x(A, b);
    for(int i = 0; i < x.size(); i++){
        std::cout << x[i] << " ";
    }

    std::cout << std::endl;
    std::vector<std::vector<float>> L, U;
    LU(matrix, L, U);

    std::cout << "Macierz L:\n";
    printMatrix(L);
    std::cout << "Macierz U:\n";
    printMatrix(U);

    std::cout << "Macierz L x U\n";
    auto LxU = matrixMultiplication(L, U);
    printMatrix(LxU);

    std::cout << "Rozkład Choleskiego:\n";
    std::vector<std::vector<float>> cholesky = choleskyDecomposition(matrix);
    printMatrix(cholesky);



    return 0;
}
