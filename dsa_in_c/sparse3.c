#include <stdio.h>
#include <stdlib.h>

// A structure to represent a single term. This is the "row" for a
// coefficient and exponent pair you described.
typedef struct {
    int coeff; // The coefficient of the term
    int exp;   // The exponent of the term
} Term;

// A structure to represent a polynomial.
// It holds the total number of non-zero terms and an array of those terms.
typedef struct {
    int num_terms; // Number of non-zero terms
    Term *terms;   // Pointer to the array of {coeff, exp} pairs
} Polynomial;

// --- Function Prototypes ---
Polynomial* create_polynomial();
void display_polynomial(const Polynomial *p);
Polynomial* add_polynomials(const Polynomial *p1, const Polynomial *p2);
Polynomial* multiply_polynomials(const Polynomial *p1, const Polynomial *p2);
void free_polynomial(Polynomial *p);
void sort_terms(Polynomial *p);

// --- Main Function ---
int main() {
    printf("--- Polynomial 1 ---\n");
    Polynomial *poly1 = create_polynomial();

    printf("\n--- Polynomial 2 ---\n");
    Polynomial *poly2 = create_polynomial();

    // Sort terms to ensure consistent processing and display
    sort_terms(poly1);
    sort_terms(poly2);

    printf("\n----------------------------------------\n");
    printf("First Polynomial:  ");
    display_polynomial(poly1);

    printf("Second Polynomial: ");
    display_polynomial(poly2);
    printf("----------------------------------------\n\n");

    // --- Addition ---
    printf("--- Addition ---\n");
    Polynomial *sum = add_polynomials(poly1, poly2);
    printf("Sum: ");
    display_polynomial(sum);
    printf("\n");

    // --- Multiplication ---
    printf("--- Multiplication (Following Your Logic) ---\n");
    Polynomial *product = multiply_polynomials(poly1, poly2);
    printf("Product: ");
    display_polynomial(product);
    printf("\n");

    // --- Clean up memory ---
    free_polynomial(poly1);
    free_polynomial(poly2);
    free_polynomial(sum);
    free_polynomial(product);

    return 0;
}

// --- Function Implementations ---

/**
 * @brief Reads polynomial terms from the user.
 */
Polynomial* create_polynomial() {
    Polynomial *p = (Polynomial*)malloc(sizeof(Polynomial));
    if (!p) { printf("Memory allocation failed!\n"); exit(1); }

    printf("Enter the number of terms: ");
    scanf("%d", &p->num_terms);

    if (p->num_terms < 0) { printf("Number of terms cannot be negative.\n"); exit(1); }
    if (p->num_terms == 0) {
        p->terms = NULL;
        return p;
    }

    p->terms = (Term*)malloc(p->num_terms * sizeof(Term));
    if (!p->terms) { printf("Memory allocation failed!\n"); free(p); exit(1); }

    for (int i = 0; i < p->num_terms; i++) {
        printf("Enter coefficient for term %d: ", i + 1);
        scanf("%d", &p->terms[i].coeff);
        printf("Enter exponent for term %d:    ", i + 1);
        scanf("%d", &p->terms[i].exp);
    }
    return p;
}

/**
 * @brief Displays a polynomial in a standard mathematical format.
 */
void display_polynomial(const Polynomial *p) {
    if (p == NULL || p->num_terms == 0) {
        printf("0\n");
        return;
    }
    for (int i = 0; i < p->num_terms; i++) {
        if (p->terms[i].coeff == 0) continue;
        if (i > 0 && p->terms[i].coeff > 0) printf(" + ");
        else if (p->terms[i].coeff < 0) (i > 0) ? printf(" - ") : printf("-");
        
        int coeff = abs(p->terms[i].coeff);
        int exp = p->terms[i].exp;

        if (coeff != 1 || exp == 0) printf("%d", coeff);
        if (exp > 0) {
            printf("x");
            if (exp > 1) printf("^%d", exp);
        }
    }
    printf("\n");
}

/**
 * @brief Adds two polynomials.
 */
Polynomial* add_polynomials(const Polynomial *p1, const Polynomial *p2) {
    Polynomial *sum = (Polynomial*)malloc(sizeof(Polynomial));
    sum->terms = (Term*)malloc((p1->num_terms + p2->num_terms) * sizeof(Term));
    if (!sum || !sum->terms) { printf("Memory allocation failed!\n"); exit(1); }

    int i = 0, j = 0, k = 0;
    while (i < p1->num_terms && j < p2->num_terms) {
        if (p1->terms[i].exp > p2->terms[j].exp) sum->terms[k++] = p1->terms[i++];
        else if (p1->terms[i].exp < p2->terms[j].exp) sum->terms[k++] = p2->terms[j++];
        else {
            int new_coeff = p1->terms[i].coeff + p2->terms[j].coeff;
            if (new_coeff != 0) {
                sum->terms[k].coeff = new_coeff;
                sum->terms[k].exp = p1->terms[i].exp;
                k++;
            }
            i++; j++;
        }
    }
    while (i < p1->num_terms) sum->terms[k++] = p1->terms[i++];
    while (j < p2->num_terms) sum->terms[k++] = p2->terms[j++];
    
    sum->num_terms = k;
    sum->terms = (Term*)realloc(sum->terms, k * sizeof(Term));
    return sum;
}

/**
 * @brief Multiplies two polynomials using the logic you described.
 */
Polynomial* multiply_polynomials(const Polynomial *p1, const Polynomial *p2) {
    if (p1->num_terms == 0 || p2->num_terms == 0) {
        Polynomial *p = (Polynomial*)malloc(sizeof(Polynomial));
        p->num_terms = 0; p->terms = NULL; return p;
    }
    
    // STEP 1: Create a temporary polynomial to store all raw product terms.
    // The maximum number of terms will be (p1->num_terms * p2->num_terms).
    Polynomial *temp_prod = (Polynomial*)malloc(sizeof(Polynomial));
    int max_terms = p1->num_terms * p2->num_terms;
    temp_prod->num_terms = max_terms;
    temp_prod->terms = (Term*)malloc(max_terms * sizeof(Term));
    if (!temp_prod || !temp_prod->terms) { printf("Memory allocation failed!\n"); exit(1); }

    // STEP 2: Generate all product terms according to your logic.
    // "for individual values we can multiply the coeff and add the exponent"
    int k = 0;
    for (int i = 0; i < p1->num_terms; i++) {
        for (int j = 0; j < p2->num_terms; j++) {
            // Multiply coefficients
            temp_prod->terms[k].coeff = p1->terms[i].coeff * p2->terms[j].coeff;
            // Add exponents
            temp_prod->terms[k].exp = p1->terms[i].exp + p2->terms[j].exp;
            k++;
        }
    }

    // STEP 3: Sort the temporary product polynomial by exponent.
    // This groups all terms with the same exponent next to each other,
    // making them easy to combine.
    sort_terms(temp_prod);

    // STEP 4: Create the final product polynomial by combining like terms.
    Polynomial *product = (Polynomial*)malloc(sizeof(Polynomial));
    product->terms = (Term*)malloc(max_terms * sizeof(Term));
    if (!product || !product->terms) { printf("Memory allocation failed!\n"); exit(1); }

    int current_term_idx = 0; // Index for the final simplified polynomial
    int i = 0;
    while (i < temp_prod->num_terms) {
        // Copy the first term of a group (e.g., the first 5x^12 term)
        product->terms[current_term_idx] = temp_prod->terms[i];
        i++;
        
        // Loop to find other terms with the same exponent and add them up.
        while (i < temp_prod->num_terms && temp_prod->terms[i].exp == product->terms[current_term_idx].exp) {
            product->terms[current_term_idx].coeff += temp_prod->terms[i].coeff;
            i++;
        }
        
        // Only move to the next term in our final result if the coefficient isn't zero.
        if (product->terms[current_term_idx].coeff != 0) {
            current_term_idx++;
        }
    }

    product->num_terms = current_term_idx;
    product->terms = (Term*)realloc(product->terms, current_term_idx * sizeof(Term));

    // STEP 5: Free the temporary polynomial that we used for calculations.
    free_polynomial(temp_prod);

    return product;
}

/**
 * @brief Frees all dynamically allocated memory for a polynomial.
 */
void free_polynomial(Polynomial *p) {
    if (p != NULL) {
        free(p->terms);
        free(p);
    }
}

/**
 * @brief Sorts polynomial terms in descending order of their exponents.
 */
void sort_terms(Polynomial *p) {
    if (p == NULL || p->num_terms < 2) return;
    for (int i = 0; i < p->num_terms - 1; i++) {
        for (int j = 0; j < p->num_terms - i - 1; j++) {
            if (p->terms[j].exp < p->terms[j + 1].exp) {
                Term temp = p->terms[j];
                p->terms[j] = p->terms[j + 1];
                p->terms[j + 1] = temp;
            }
        }
    }
}
