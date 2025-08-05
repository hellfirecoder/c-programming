#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Needed for abs()

// Structure for a single term
typedef struct term{
    int coeff;
    int exp;
} term;

// Structure for a polynomial with shorter name
typedef struct Poly{
    int n;
    term* terms;
} Poly;

// --- Function Prototypes ---
void initPoly(Poly* p, int n);
Poly getPoly();
Poly addPolys(Poly p1, Poly p2);
Poly mulPolys(Poly p1, Poly p2);
void printPoly(Poly p);
void sortPoly(Poly* p);

// Initialize a polynomial
void initPoly(Poly* p, int n){
    p->n = n;
    p->terms = (term*) malloc(n*sizeof(term));
    return;
}

// Get polynomial input from the user
Poly getPoly(){
    Poly p;
    int n, i;
    printf("Enter the total no. of terms in polynomial: ");
    scanf("%d", &n);
    initPoly(&p, n);
    printf("Enter the coefficient and exponent for each term.\n");
    for(i=0; i<n; i++){ 
        printf("Term %d: \n", i+1);
        printf("Coefficient: ");
        scanf("%d", &p.terms[i].coeff);
        printf("Exponent: ");
        scanf("%d", &p.terms[i].exp);
    }
    return p;
}

// Add two polynomials
Poly addPolys(Poly p1, Poly p2){
    Poly r;
    int i=0, j=0, k=0;
    initPoly(&r, p1.n+p2.n);
    while(i<p1.n && j<p2.n){
        if(p1.terms[i].exp > p2.terms[j].exp){
            r.terms[k++] = p1.terms[i++];
        }
        else if(p1.terms[i].exp < p2.terms[j].exp){
            r.terms[k++] = p2.terms[j++];
        }
        else{ // Exponents are equal
            int sum = p1.terms[i].coeff + p2.terms[j].coeff;
            if(sum!=0){
                r.terms[k].exp = p1.terms[i].exp;
                r.terms[k].coeff = sum;
                k++;
            }
            i++;
            j++;      
        }
    }

    // Copy remaining terms
    while(i<p1.n){
        r.terms[k++] = p1.terms[i++];
    }
    while(j<p2.n){
        r.terms[k++] = p2.terms[j++];
    }
    r.n = k;
    r.terms = (term*) realloc(r.terms, k * sizeof(term));
    return r;
}

// Multiply two polynomials
Poly mulPolys(Poly p1, Poly p2){
    Poly r, temp;
    int found, i = 0, j = 0, k = 0;
    initPoly(&temp, p1.n*p2.n);
    for(i=0; i<p1.n; i++){
        for(j=0; j<p2.n; j++){
            temp.terms[k].coeff = p1.terms[i].coeff * p2.terms[j].coeff;
            temp.terms[k].exp = p1.terms[i].exp + p2.terms[j].exp;
            k++;
        }
    }
    initPoly(&r, k); 
    r.n = 0;
    for(i = 0; i < k; i++){
        found = 0;
        for(j = 0; j < r.n; j++){
            if(temp.terms[i].exp == r.terms[j].exp){
                r.terms[j].coeff += temp.terms[i].coeff;
                found = 1;
                break;
            }
        }
        if(!found){
            r.terms[r.n].coeff = temp.terms[i].coeff;
            r.terms[r.n].exp = temp.terms[i].exp;
            r.n++;
        }
    }
    free(temp.terms); // Free the temporary memory
    return r;
}

// Sort terms by exponent in descending order
void sortPoly(Poly* p) {
    if (p == NULL || p->n < 2) return;
    for (int i = 0; i < p->n - 1; i++) {
        for (int j = 0; j < p->n - i - 1; j++) {
            if (p->terms[j].exp < p->terms[j + 1].exp) {
                term temp_term = p->terms[j];
                p->terms[j] = p->terms[j + 1];
                p->terms[j + 1] = temp_term;
            }
        }
    }
}

// Print the polynomial in a standard format
void printPoly(Poly p){
    if (p.n == 0) {
        printf("0\n");
        return;
    }
    
    sortPoly(&p);

    int isFirst = 1;
    for(int i=0; i<p.n; i++){
        if (p.terms[i].coeff == 0) continue;

        if (!isFirst) {
             if (p.terms[i].coeff > 0) printf(" + ");
             else printf(" - ");
        } else {
            if (p.terms[i].coeff < 0) printf("-");
        }
        
        int coeff = abs(p.terms[i].coeff);
        int exp = p.terms[i].exp;

        if (coeff != 1 || exp == 0) {
            printf("%d", coeff);
        }

        if (exp > 0) {
            printf("x");
            if (exp > 1) {
                printf("^%d", exp);
            }
        }
        isFirst = 0;
    }
    
    if (isFirst) {
        printf("0");
    }

    printf("\n");
}

int main(){
    Poly p1, p2, sum, prod;
    p1 = getPoly();
    p2 = getPoly();

    sortPoly(&p1);
    sortPoly(&p2);

    printf("\n----------------------------------------\n");
    printf("Polynomial 1: ");
    printPoly(p1);
    printf("Polynomial 2: ");
    printPoly(p2);
    printf("----------------------------------------\n\n");

    sum = addPolys(p1, p2);
    printf("Polynomial 1 + Polynomial 2: \n");
    printPoly(sum);

    prod = mulPolys(p1, p2);
    printf("\nPolynomial 1 * Polynomial 2: \n");
    printPoly(prod);
    
    // Free the allocated memory
    free(p1.terms);
    free(p2.terms);
    free(sum.terms);
    free(prod.terms);

    return 0;
}
