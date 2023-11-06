#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
typedef struct Term {
    float coeff;
    int exponent;
    struct Term* next;
} Term;
 
typedef struct Polynomial {
    Term* header;
} Polynomial;
 
Term* createTerm(float coeff, int exponent) {
    Term* term = (Term*)malloc(sizeof(Term));
    term->coeff = coeff;
    term->exponent = exponent;
    term->next = NULL;
    return term;
}
 
void initPolynomial(Polynomial* polynomial) {
    polynomial->header = createTerm(0.0, -1);
    polynomial->header->next = polynomial->header;
}
 
void addTerm(Polynomial* polynomial, float coeff, int exponent) {
    Term* newTerm = createTerm(coeff, exponent);
    Term* current = polynomial->header;
 
    while (current->next != polynomial->header && current->next->exponent > exponent) {
        current = current->next;
    }
 
    newTerm->next = current->next;
    current->next = newTerm;
}
 
Polynomial* Pread() {
    Polynomial* polynomial = (Polynomial*)malloc(sizeof(Polynomial));
    initPolynomial(polynomial);
 
    int numTerms;
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", &numTerms);
 
    for (int i = 0; i < numTerms; i++) {
        float coeff;
        int exponent;
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%f %d", &coeff, &exponent);
        addTerm(polynomial, coeff, exponent);
    }
 
    return polynomial;
}
 
void Pwrite(Polynomial* polynomial) {
    Term* current = polynomial->header->next;
    int firstTerm = 1;
 
    while (current != polynomial->header) {
        if (current->coeff != 0) {
            if (!firstTerm) {
                if (current->coeff > 0) {
                    printf(" + ");
                } else {
                    printf(" - ");
                }
            }
            if (fabs(current->coeff) != 1 || current->exponent == 0) {
                printf("%.2f", fabs(current->coeff));
            }
            if (current->exponent > 0) {
                printf("x");
                if (current->exponent > 1) {
                    printf("^%d", current->exponent);
                }
            }
            firstTerm = 0;
        }
        current = current->next;
    }
 
    if (firstTerm) {
        printf("0");
    }
    printf("\n");
}
 
Polynomial* Padd(Polynomial* a, Polynomial* b) {
    Polynomial* c = (Polynomial*)malloc(sizeof(Polynomial));
    initPolynomial(c);
 
    Term* termA = a->header->next;
    Term* termB = b->header->next;
 
    while (termA != a->header && termB != b->header) {
        if (termA->exponent > termB->exponent) {
            addTerm(c, termA->coeff, termA->exponent);
            termA = termA->next;
        } else if (termA->exponent < termB->exponent) {
            addTerm(c, termB->coeff, termB->exponent);
            termB = termB->next;
        } else {
            addTerm(c, termA->coeff + termB->coeff, termA->exponent);
            termA = termA->next;
            termB = termB->next;
        }
    }
 
    while (termA != a->header) {
        addTerm(c, termA->coeff, termA->exponent);
        termA = termA->next;
    }
    while (termB != b->header) {
        addTerm(c, termB->coeff, termB->exponent);
        termB = termB->next;
    }
 
    return c;
}
 
Polynomial* Psub(Polynomial* a, Polynomial* b) {
    Polynomial* c = (Polynomial*)malloc(sizeof(Polynomial));
    initPolynomial(c);
 
    Term* termA = a->header->next;
    Term* termB = b->header->next;
 
    while (termA != a->header && termB != b->header) {
        if (termA->exponent > termB->exponent) {
            addTerm(c, termA->coeff, termA->exponent);
            termA = termA->next;
        } else if (termA->exponent < termB->exponent) {
            addTerm(c, -termB->coeff, termB->exponent);
            termB = termB->next;
        } else {
            addTerm(c, termA->coeff - termB->coeff, termA->exponent);
            termA = termA->next;
            termB = termB->next;
        }
    }
 
    while (termA != a->header) {
        addTerm(c, termA->coeff, termA->exponent);
        termA = termA->next;
    }
    while (termB != b->header) {
        addTerm(c, -termB->coeff, termB->exponent);
        termB = termB->next;
    }
 
    return c;
}
 
 
Polynomial* Pmult(Polynomial* a, Polynomial* b) {
    Polynomial* c = (Polynomial*)malloc(sizeof(Polynomial));
    initPolynomial(c);
 
    Term* termA = a->header->next;
 
    while (termA != a->header) {
        Term* termB = b->header->next;
        while (termB != b->header) {
            addTerm(c, termA->coeff * termB->coeff, termA->exponent + termB->exponent);
            termB = termB->next;
        }
        termA = termA->next;
    }
 
    Term* current = c->header->next;
    while (current != c->header && current->next != c->header) {
        if (current->exponent == current->next->exponent) {
            current->coeff += current->next->coeff;
            Term* temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
 
    return c;
}
 
 
float Peval(Polynomial* polynomial, float x) {
    float result = 0.0;
    Term* current = polynomial->header->next;
 
    while (current != polynomial->header) {
        result += current->coeff * pow(x, current->exponent);
        current = current->next;
    }
 
    return result;
}
 
void Pearse(Polynomial* polynomial, int exponent) {
    Term* current = polynomial->header;
    while (current->next != polynomial->header) {
        if (current->next->exponent == exponent) {
            Term* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return;
        }
        current = current->next;
    }
}
 
int main() {
    printf("Enter polynomial A:\n");
    Polynomial* a = Pread();
 
    printf("\nEnter polynomial B:\n");
    Polynomial* b = Pread();
 
    printf("\nPolynomial A: ");
    Pwrite(a);
 
    printf("\nPolynomial B: ");
    Pwrite(b);
 
    int choice;
    do {
        printf("\nEnter '1' if you want to add the polynomials\n");
        printf("Enter '2' if you want to subtract the polynomials\n");
        printf("Enter '3' if you want to multiply the polynomials\n");
        printf("Enter '4' if you want to evaluate the polynomials\n");
        printf("Enter '5' if you want to erase a term from the polynomials\n");
        printf("Enter '0' if you want to exit\n");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1: {
                Polynomial* c = Padd(a, b);
                printf("\nA + B = ");
                Pwrite(c);
                break;
            }
 
            case 2: {
                Polynomial* d = Psub(a, b);
                printf("A - B = ");
                Pwrite(d);
                break;
            }
 
            case 3: {
                Polynomial* e = Pmult(a, b);
                printf("A * B = ");
                Pwrite(e);
                break;
            }
 
            case 4: {
                float x;
                printf("\nEnter the value of x for polynomial evaluation: ");
                scanf("%f", &x);
                printf("A(when x is: %.2f) = %.2f\n", x, Peval(a, x));
                printf("B(when x is: %.2f) = %.2f\n", x, Peval(b, x));
                break;
            }
 
            case 5: {
                int eraseExponent_A,eraseExponent_B;
                printf("\nEnter the exponent of the term to erase from polynomial A: ");
                scanf("%d", &eraseExponent_A);
                Pearse(a, eraseExponent_A);
                printf("Polynomial A after erasing term with exponent %d: ", eraseExponent_A);
                Pwrite(a);
printf("\nEnter the exponent of the term to erase from polynomial B: ");
scanf("%d", &eraseExponent_B);
                Pearse(b, eraseExponent_B);
                printf("Polynomial A after erasing term with exponent %d: ", eraseExponent_B);
                Pwrite(b);
                break;
            }
 
            case 0:
                printf("Exiting program.\n");
                break;
 
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);
 
    return 0;
}
