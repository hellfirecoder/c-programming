#include <stdio.h>
#include <stdlib.h>

// Function to print a matrix in its standard 2D format
void printStandardMatrix(int **matrix, int rows, int cols) {
    printf("\n--- Standard Matrix ---\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to print a matrix in its sparse (triplet) format
void printSparseMatrix(int **sparseMatrix) {
    if (sparseMatrix == NULL) {
        printf("Matrix is empty.\n");
        return;
    }
    // The first row stores metadata: rows, cols, number of non-zero values
    int rows = sparseMatrix[0][0];
    int cols = sparseMatrix[0][1];
    int values = sparseMatrix[0][2];

    printf("\n--- Sparse (Triplet) Matrix ---\n");
    printf("Row\tCol\tValue\n");
    printf("---------------------\n");
    printf("%d\t%d\t%d\t (Header)\n", rows, cols, values);
    for (int i = 1; i <= values; i++) {
        printf("%d\t%d\t%d\n", sparseMatrix[i][0], sparseMatrix[i][1], sparseMatrix[i][2]);
    }
}


/**
 * @brief Converts a standard 2D matrix into its sparse (triplet) representation.
 * * @param matrix The input 2D matrix.
 * @param rows The number of rows in the input matrix.
 * @param cols The number of columns in the input matrix.
 * @return A pointer to the dynamically allocated sparse matrix.
 * The sparse matrix has nonZeroCount + 1 rows and 3 columns.
 * The first row (index 0) acts as a header:
 * - sparseMatrix[0][0] = number of rows
 * - sparseMatrix[0][1] = number of columns
 * - sparseMatrix[0][2] = total number of non-zero elements
 */
int** createSparseMatrix(int **matrix, int rows, int cols) {
    // 1. Count the number of non-zero elements
    int nonZeroCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                nonZeroCount++;
            }
        }
    }

    // 2. Allocate memory for the sparse matrix
    // We need nonZeroCount + 1 rows (1 for the header) and 3 columns
    int **sparseMatrix = (int **)malloc((nonZeroCount + 1) * sizeof(int *));
    if (sparseMatrix == NULL) {
        printf("Memory allocation failed for sparse matrix rows!\n");
        return NULL;
    }
    for (int i = 0; i < nonZeroCount + 1; i++) {
        sparseMatrix[i] = (int *)malloc(3 * sizeof(int));
        if (sparseMatrix[i] == NULL) {
           printf("Memory allocation failed for sparse matrix columns!\n");
           // Free previously allocated memory before exiting
           for(int k=0; k<i; k++) free(sparseMatrix[k]);
           free(sparseMatrix);
           return NULL;
        }
    }

    // 3. Populate the header row of the sparse matrix
    sparseMatrix[0][0] = rows;
    sparseMatrix[0][1] = cols;
    sparseMatrix[0][2] = nonZeroCount;

    // 4. Populate the rest of the sparse matrix with non-zero elements
    int k = 1; // Start filling from the second row (index 1)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparseMatrix[k][0] = i;
                sparseMatrix[k][1] = j;
                sparseMatrix[k][2] = matrix[i][j];
                k++;
            }
        }
    }

    return sparseMatrix;
}

/**
 * @brief Transposes a matrix given in sparse (triplet) format.
 * * @param sparseMatrix The input sparse matrix.
 * @return A pointer to the dynamically allocated transposed sparse matrix.
 */
int** transposeSparseMatrix(int **sparseMatrix) {
    if (sparseMatrix == NULL) return NULL;

    // Extract metadata from the header row
    int rows = sparseMatrix[0][0];
    int cols = sparseMatrix[0][1];
    int nonZeroCount = sparseMatrix[0][2];

    // 1. Allocate memory for the transposed sparse matrix
    int **transposeMatrix = (int **)malloc((nonZeroCount + 1) * sizeof(int *));
     if (transposeMatrix == NULL) {
        printf("Memory allocation failed for transpose matrix rows!\n");
        return NULL;
    }
    for (int i = 0; i < nonZeroCount + 1; i++) {
        transposeMatrix[i] = (int *)malloc(3 * sizeof(int));
         if (transposeMatrix[i] == NULL) {
           printf("Memory allocation failed for transpose matrix columns!\n");
           for(int k=0; k<i; k++) free(transposeMatrix[k]);
           free(transposeMatrix);
           return NULL;
        }
    }

    // 2. Populate the header row of the transposed matrix
    // The number of rows and columns are swapped
    transposeMatrix[0][0] = cols;
    transposeMatrix[0][1] = rows;
    transposeMatrix[0][2] = nonZeroCount;

    // 3. Perform the transpose
    if (nonZeroCount > 0) {
        int q = 1; // Current row index for the transposeMatrix
        // Iterate through each column of the original matrix
        for (int i = 0; i < cols; i++) {
            // Iterate through each non-zero element of the sparse matrix
            for (int p = 1; p <= nonZeroCount; p++) {
                // If the element is in the current column 'i'
                if (sparseMatrix[p][1] == i) {
                    transposeMatrix[q][0] = sparseMatrix[p][1]; // original col -> new row
                    transposeMatrix[q][1] = sparseMatrix[p][0]; // original row -> new col
                    transposeMatrix[q][2] = sparseMatrix[p][2]; // value remains the same
                    q++;
                }
            }
        }
    }
    
    return transposeMatrix;
}


int main() {
    int rows, cols;
    
    // Get matrix dimensions from the user
    printf("Enter the number of rows for the matrix: ");
    scanf("%d", &rows);
    printf("Enter the number of columns for the matrix: ");
    scanf("%d", &cols);

    // --- Allocate memory for the standard matrix ---
    int **matrix = (int **)malloc(rows * sizeof(int *));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
    }

    // --- Get matrix elements from the user ---
    printf("Enter the elements of the matrix (%d x %d):\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Enter element at [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    printStandardMatrix(matrix, rows, cols);

    // --- Convert to Sparse Matrix ---
    int **sparseMatrix = createSparseMatrix(matrix, rows, cols);
    printSparseMatrix(sparseMatrix);

    // --- Transpose the Sparse Matrix ---
    printf("\n--- Transposing the Sparse Matrix... ---\n");
    int **transposeMatrix = transposeSparseMatrix(sparseMatrix);
    printSparseMatrix(transposeMatrix);

    // --- Free all dynamically allocated memory ---
    // Free standard matrix
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    // Free sparse matrix
    int nonZeroCount = sparseMatrix[0][2];
    for (int i = 0; i < nonZeroCount + 1; i++) {
        free(sparseMatrix[i]);
        free(transposeMatrix[i]);
    }
    free(sparseMatrix);
    free(transposeMatrix);

    return 0;
}