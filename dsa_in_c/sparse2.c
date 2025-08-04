#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// --- Struct Definitions ---

// Structure to represent a non-zero element (a term in the triplet)
typedef struct {
    int row;
    int col;
    int value;
} Term;

// Structure to represent the sparse matrix in triplet format
typedef struct {
    int rows;      // Total number of rows in the matrix
    int cols;      // Total number of columns in the matrix
    int num_terms; // Number of non-zero terms
    Term *terms;   // Array of non-zero terms
} SparseMatrix;

// --- Function Prototypes ---

SparseMatrix* create_random_sparse_matrix(int rows, int cols, int num_terms);
SparseMatrix* add_sparse_matrices(const SparseMatrix *m1, const SparseMatrix *m2);
SparseMatrix* transpose_sparse_matrix_fast(const SparseMatrix *matrix);
void display_sparse_matrix(const SparseMatrix *matrix);
void free_sparse_matrix(SparseMatrix *matrix);

// --- Main Function ---

int main() {
    // Seed the random number generator
    srand(time(NULL));

    int rows, cols, num_terms1, num_terms2;

    // --- Get User Input for Matrix Dimensions ---
    printf("Enter the number of rows for the matrices: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        printf("Error: Please enter a positive integer for rows.\n");
        exit(1);
    }

    printf("Enter the number of columns for the matrices: ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        printf("Error: Please enter a positive integer for columns.\n");
        exit(1);
    }
    
    printf("Enter the number of non-zero terms for Matrix 1: ");
    if (scanf("%d", &num_terms1) != 1 || num_terms1 < 0 || num_terms1 > rows * cols) {
        printf("Error: Invalid input. Number of terms cannot be negative or exceed the matrix capacity of %d.\n", rows * cols);
        exit(1);
    }

    printf("Enter the number of non-zero terms for Matrix 2: ");
    if (scanf("%d", &num_terms2) != 1 || num_terms2 < 0 || num_terms2 > rows * cols) {
        printf("Error: Invalid input. Number of terms cannot be negative or exceed the matrix capacity of %d.\n", rows * cols);
        exit(1);
    }


    // --- 1. Generate Sparse Matrices Directly ---
    printf("\n--- Generating Random Sparse Matrices ---\n");
    SparseMatrix *sparse1 = create_random_sparse_matrix(rows, cols, num_terms1);
    printf("Matrix 1 in Sparse Format:\n");
    display_sparse_matrix(sparse1);

    SparseMatrix *sparse2 = create_random_sparse_matrix(rows, cols, num_terms2);
    printf("\nMatrix 2 in Sparse Format:\n");
    display_sparse_matrix(sparse2);


    // --- 2. Add the Two Sparse Matrices ---
    printf("\n--- Adding the Two Sparse Matrices ---\n");
    SparseMatrix *sum_matrix = add_sparse_matrices(sparse1, sparse2);
    printf("Addition Result:\n");
    display_sparse_matrix(sum_matrix);


    // --- 3. Transpose a Sparse Matrix ---
    printf("\n--- Transposing Matrix 1 (Fast Transpose) ---\n");
    SparseMatrix *transposed_matrix = transpose_sparse_matrix_fast(sparse1);
    printf("Transpose Result:\n");
    display_sparse_matrix(transposed_matrix);


    // --- 4. Clean Up All Allocated Memory ---
    printf("\n--- Cleaning Up Memory ---\n");
    free_sparse_matrix(sparse1);
    free_sparse_matrix(sparse2);
    free_sparse_matrix(sum_matrix);
    free_sparse_matrix(transposed_matrix);
    printf("All memory has been freed.\n");

    return 0;
}

// --- Function Implementations ---

/**
 * @brief Creates a sparse matrix with random non-zero values directly.
 */
SparseMatrix* create_random_sparse_matrix(int rows, int cols, int num_terms) {
    // 1. Allocate memory for the SparseMatrix struct and its terms array
    SparseMatrix *matrix = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    if (!matrix) {
        printf("Error: Memory allocation failed for sparse matrix struct.\n");
        exit(1);
    }
    matrix->terms = (Term *)malloc(num_terms * sizeof(Term));
    if (!matrix->terms) {
        printf("Error: Memory allocation failed for terms array.\n");
        exit(1);
    }
    
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->num_terms = num_terms;

    // Helper array to ensure unique coordinates
    char *coord_check = (char *)calloc(rows * cols, sizeof(char));
    if (!coord_check) {
        printf("Error: Memory allocation failed for coordinate check.\n");
        exit(1);
    }

    // 2. Populate the terms with unique random coordinates and values
    for (int i = 0; i < num_terms; ++i) {
        int r, c;
        do {
            r = rand() % rows;
            c = rand() % cols;
        } while (coord_check[r * cols + c] != 0); // Keep trying until an unused coordinate is found
        
        coord_check[r * cols + c] = 1; // Mark coordinate as used

        matrix->terms[i].row = r;
        matrix->terms[i].col = c;
        matrix->terms[i].value = (rand() % 99) + 1; // Random value from 1 to 99
    }

    free(coord_check);
    // Note: The terms are not sorted. For some algorithms (like addition),
    // they should be sorted first for optimal performance.
    return matrix;
}


/**
 * @brief Adds two sparse matrices. Assumes terms are sorted by row, then column.
 */
SparseMatrix* add_sparse_matrices(const SparseMatrix *m1, const SparseMatrix *m2) {
    if (m1->rows != m2->rows || m1->cols != m2->cols) {
        printf("Error: Matrix dimensions must match for addition.\n");
        exit(1);
    }

    SparseMatrix *sum_matrix = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    sum_matrix->rows = m1->rows;
    sum_matrix->cols = m1->cols;
    // Allocate max possible size, will reallocate later
    sum_matrix->terms = (Term *)malloc((m1->num_terms + m2->num_terms) * sizeof(Term));

    int i = 0, j = 0, k = 0; // Pointers for m1, m2, and sum_matrix

    while (i < m1->num_terms && j < m2->num_terms) {
        if (m1->terms[i].row < m2->terms[j].row) {
            sum_matrix->terms[k++] = m1->terms[i++];
        } else if (m1->terms[i].row > m2->terms[j].row) {
            sum_matrix->terms[k++] = m2->terms[j++];
        } else { // Rows are equal, check columns
            if (m1->terms[i].col < m2->terms[j].col) {
                sum_matrix->terms[k++] = m1->terms[i++];
            } else if (m1->terms[i].col > m2->terms[j].col) {
                sum_matrix->terms[k++] = m2->terms[j++];
            } else { // Rows and columns are equal, add values
                sum_matrix->terms[k] = m1->terms[i];
                sum_matrix->terms[k].value += m2->terms[j].value;
                if (sum_matrix->terms[k].value != 0) k++;
                i++; j++;
            }
        }
    }
    while (i < m1->num_terms) sum_matrix->terms[k++] = m1->terms[i++];
    while (j < m2->num_terms) sum_matrix->terms[k++] = m2->terms[j++];

    sum_matrix->num_terms = k;
    // Optional: Reallocate to the actual size to save memory
    sum_matrix->terms = (Term *)realloc(sum_matrix->terms, k * sizeof(Term));
    return sum_matrix;
}

/**
 * @brief Transposes a sparse matrix using the efficient "Fast Transpose" algorithm.
 */
SparseMatrix* transpose_sparse_matrix_fast(const SparseMatrix *matrix) {
    SparseMatrix *transpose_matrix = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    if (!transpose_matrix) {
        printf("Error: Memory allocation failed for transpose matrix struct.\n");
        exit(1);
    }
    transpose_matrix->terms = (Term *)malloc(matrix->num_terms * sizeof(Term));
    if (!transpose_matrix->terms) {
        printf("Error: Memory allocation failed for transpose terms array.\n");
        exit(1);
    }

    transpose_matrix->rows = matrix->cols; // Swapped
    transpose_matrix->cols = matrix->rows; // Swapped
    transpose_matrix->num_terms = matrix->num_terms;

    if (matrix->num_terms > 0) {
        // Create helper arrays
        int *row_terms = (int *)calloc(matrix->cols, sizeof(int));
        int *start_pos = (int *)calloc(matrix->cols, sizeof(int));

        // 1. Count non-zero terms in each column of the original matrix
        for (int i = 0; i < matrix->num_terms; i++) {
            row_terms[matrix->terms[i].col]++;
        }

        // 2. Calculate the starting position for each row in the transpose
        start_pos[0] = 0;
        for (int i = 1; i < matrix->cols; i++) {
            start_pos[i] = start_pos[i - 1] + row_terms[i - 1];
        }

        // 3. Perform the transpose
        for (int i = 0; i < matrix->num_terms; i++) {
            int pos = start_pos[matrix->terms[i].col]++;
            transpose_matrix->terms[pos].row = matrix->terms[i].col;
            transpose_matrix->terms[pos].col = matrix->terms[i].row;
            transpose_matrix->terms[pos].value = matrix->terms[i].value;
        }

        free(row_terms);
        free(start_pos);
    }
    return transpose_matrix;
}


/**
 * @brief Displays the sparse matrix in a readable triplet format.
 */
void display_sparse_matrix(const SparseMatrix *matrix) {
    if (!matrix) {
        printf("Matrix is NULL.\n");
        return;
    }
    printf("Dimensions: %d rows, %d cols\n", matrix->rows, matrix->cols);
    printf("Non-zero terms: %d\n", matrix->num_terms);
    printf("Row\tCol\tValue\n");
    printf("---\t---\t-----\n");
    for (int i = 0; i < matrix->num_terms; ++i) {
        printf("%d\t%d\t%d\n", matrix->terms[i].row, matrix->terms[i].col, matrix->terms[i].value);
    }
}

/**
 * @brief Frees all dynamically allocated memory for a sparse matrix.
 */
void free_sparse_matrix(SparseMatrix *matrix) {
    if (matrix) {
        if (matrix->terms) {
            free(matrix->terms); // Free the array of terms first
        }
        free(matrix);        // Then free the structure itself
    }
}
