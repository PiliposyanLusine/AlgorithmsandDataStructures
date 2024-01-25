#include <iostream>
#include <vector>

using namespace std;

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
    return result;
}

// Function to multiply two matrices using Strassen algorithm
vector<vector<int>> strassenMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B)
{
    int n = A.size();
    if(n == 1)
    {
        vector<vector<int>> result(n, vector<int>(n, 0));
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }
    int halfSize = n / 2;
    vector<vector<int>> A11(halfSize, vector<int>(halfSize, 0));   
    vector<vector<int>> A12(halfSize, vector<int>(halfSize, 0));
    vector<vector<int>> A21(halfSize, vector<int>(halfSize, 0));
    vector<vector<int>> A22(halfSize, vector<int>(halfSize, 0));

    vector<vector<int>> B11(halfSize, vector<int>(halfSize, 0));
    vector<vector<int>> B12(halfSize, vector<int>(halfSize, 0));
    vector<vector<int>> B21(halfSize, vector<int>(halfSize, 0));
    vector<vector<int>> B22(halfSize, vector<int>(halfSize, 0));

    for(int i = 0; i < halfSize; ++i)
    {
        for(int j = 0; j < halfSize; ++j)
        {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + halfSize];
            A21[i][j] = A[i + halfSize][j];
            A22[i][j] = A[i + halfSize][j + halfSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + halfSize];
            B21[i][j] = B[i + halfSize][j];
            B22[i][j] = B[i + halfSize][j + halfSize];
        }
    }
    vector<vector<int>> P1 = strassenMultiply(A11, subtractMatrices(B12, B22));
    vector<vector<int>> P2 = strassenMultiply(addMatrices(A12, A11), B22);
    vector<vector<int>> P3 = strassenMultiply(addMatrices(A21, A22), B11);
    vector<vector<int>> P4 = strassenMultiply(A22, subtractMatrices(B21, B11));
    vector<vector<int>> P5 = strassenMultiply(addMatrices(A11, A22), addMatrices(B11, B22));
    vector<vector<int>> P6 = strassenMultiply(subtractMatrices(A12, A22), addMatrices(B21, B22));
    vector<vector<int>> P7 = strassenMultiply(subtractMatrices(A11, A21), addMatrices(B11, B12));

    // Compute four submatrices of the result
    vector<vector<int>> C11 = subtractMatrices(addMatrices(addMatrices(P5, P4), P6), P2);
    vector<vector<int>> C12 = addMatrices(P1, P2);
    vector<vector<int>> C21 = addMatrices(P3, P4);
    vector<vector<int>> C22 = subtractMatrices(subtractMatrices(addMatrices(P5, P1), P3), P7);

    // Combine the four submatrices to get the result
    vector<vector<int>> result(n, vector<int>(n, 0));
    for (int i = 0; i < halfSize; ++i) 
    {
        for (int j = 0; j < halfSize; ++j) 
        {
            result[i][j] = C11[i][j];
            result[i][j + halfSize] = C12[i][j];
            result[i + halfSize][j] = C21[i][j];
            result[i + halfSize][j + halfSize] = C22[i][j];
        }
    }

    return result;
}

int main() {
    // Example usage
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};

    vector<vector<int>> result = strassenMultiply(A, B);

    // Print the result
    for (const auto& row : result) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }

    return 0;
}
