/*
   Command-Line Calculator (CLC) in C
   ---------------------------------
   A menu-driven command-line calculator that supports
   binary, unary, and advanced mathematical operations.
 
 * Features:
  - Binary operations: +, -, *, /, %, power, max, min
  - Unary operations: square root, logarithm, exponential,
    ceiling, and floor
  - Variable support (a–e) for storing and reusing values
  - Advanced mode allowing operations using variables or numbers
 
 * Concepts Used:
   - Functions and modular programming
   - Arrays for variable storage
   - Conditional logic and loops
   - Math library functions
   - User input validation
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

char showMenu();
void binaryCalculation(float vars[]);
void unary();
void setVariable(float vars[]);
void advancedMathCalculation(float vars[]);
int ExitApp();

int main() {
    float vars[5] = {0,0,0,0,0};
    char pick;

    printf("Welcome to My Command-Line Calculator (CLC)\n");
    printf("------------------------------------------------------------\n");

   while (1) {
    pick = showMenu();

    switch (pick) {
        case 'B':
            binaryCalculation(vars);
            break;
        case 'U':
            unary();
            break;
        case 'V':
            setVariable(vars);
            break;
        case 'A':
            advancedMathCalculation(vars);
            break;
        case 'E':
            if (ExitApp()) return 0;
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

}
char showMenu() {
    char choiceforcalculator;
    while (1) {
        printf("\nSelect one of the following items:\n");
        printf("B) Binary Mathematical Operations\n");
        printf("U) Unary Mathematical Operations\n");
        printf("A) Advanced Mathematical Operations\n");
        printf("V) Define variables (a - e)\n");
        printf("E) Exit\n\n");
        printf("Please select your option (B, U, V, A, E): ");

        scanf(" %c", &choiceforcalculator);
        choiceforcalculator = toupper(choiceforcalculator);

        if (choiceforcalculator=='B'||choiceforcalculator=='U'||choiceforcalculator=='A'||choiceforcalculator=='V'||choiceforcalculator=='E') return choiceforcalculator;
        printf("Invalid option.\n");
    }
}

void binaryCalculation(float vars[]) {
    float a, b, answer = 0;
    char binaryOperator;

    printf("Enter first number: ");
    scanf("%f", &a);

    printf("Enter operator (+ - * / %% P X I): ");
    scanf(" %c", &binaryOperator);
    binaryOperator = toupper(binaryOperator);

    printf("Enter second number: ");
    scanf("%f", &b);

    switch (binaryOperator) {
        case '+':
            answer = a + b;
            break;
        case '-':
            answer = a - b;
            break;
        case '*':
            answer = a * b;
            break;
        case '/':
            if (b == 0) {
                printf("Error: divide-by-zero.\n");
                return;
            }
            answer = a / b;
            break;
        case '%':
            if (b == 0) {
                printf("Error: modulus zero.\n");
                return;
            }
            answer = fmod(a, b);
            break;
        case 'P':
            answer = pow(a, b);
            break;
        case 'X':
            answer = fmax(a, b);
            break;
        case 'I':
            answer = fmin(a, b);
            break;
        default:
            printf("Invalid operator.\n");
            return;
    }

    printf("Result: %.3f\n", answer);
}


void unary() {
    float x, r = 0;
    char c;

    printf("Enter number: ");
    scanf("%f", &x);

    printf("Unary op (S L E C F): ");
    scanf(" %c", &c);
    c = toupper(c);

    if (c == 'S') {
        if (x < 0) { printf("Error.\n"); return; }
        r = sqrt(x);
    }
    else if (c == 'L') {
        if (x <= 0) { printf("Error.\n"); return; }
        r = log(x);
    }
    else if (c == 'E') {r = exp(x);}
    else if (c == 'C') {r = ceil(x);}
    else if (c == 'F') {r = floor(x);}
    else { printf("Invalid.\n"); return; }

    printf("Result: %.3f\n", r);
}

void setVariable(float vars[]) {
    char v;
    float val;

    while (1) {
        printf("Variable name (a - e): ");
        scanf(" %c", &v);
        v = tolower(v);

        if (v >= 'a' && v <= 'e') break;
        printf("Invalid variable.\n");
    }

    printf("Enter value: ");
    scanf("%f", &val);

    vars[v - 'a'] = val;

    printf("%c = %.3f stored.\n", v, val);
}

void advancedMathCalculation(float vars[]) {
    char choice[10];

    while (1) {
        printf("\nAdvanced Mode (B/U/E): ");
        scanf("%s", choice);
        choice[0] = toupper(choice[0]);

        if (choice[0] == 'E') return;

        if (choice[0] == 'B') {
            char a[20], b[20], op[5];
            float x = 0, y = 0, r = 0;

            printf("Enter first operand (number or a-e): ");
            scanf("%s", a);

            if (isalpha(a[0])) {
                char v = tolower(a[0]);
                if (v >= 'a' && v <= 'e') x = vars[v - 'a'];
                else { printf("Invalid.\n"); continue; }
            }
            else scanf("%f", &x);

            printf("Enter operator (+ - * / %% P X I): ");
            scanf("%s", op);
            op[0] = toupper(op[0]);

            printf("Enter second operand (number or a-e): ");
            scanf("%s", b);

            if (isalpha(b[0])) {
                char v = tolower(b[0]);
                if (v >= 'a' && v <= 'e') {y = vars[v - 'a'];}
                else { printf("Invalid.\n"); continue; }
            }
            else scanf("%f", &y);

            if (op[0] == '+') {r = x + y;}
            else if (op[0] == '-') {r = x - y;}
            else if (op[0] == '*') {r = x * y;}
            else if (op[0] == '/') {
                if (y == 0) { printf("Error.\n"); continue; }
                r = x / y;
            }
            else if (op[0] == '%') {
                if (y == 0) { printf("Error.\n"); continue; }
                r = fmod(x, y);
            }
            else if (op[0] == 'P') {r = pow(x, y);}
            else if (op[0] == 'X') {r = fmax(x, y);}
            else if (op[0] == 'I') {r = fmin(x, y);}
            else { printf("Invalid.\n"); continue; }

            printf("Result: %.3f\n", r);
        }

        else if (choice[0] == 'U') {
            char w[20], op[5];
            float x = 0, r = 0;

            printf("Enter operand (number or a-e): ");
            scanf("%s", w);

            if (isalpha(w[0])) {
                char v = tolower(w[0]);
                if (v >= 'a' && v <= 'e') {x = vars[v - 'a'];}
                else { printf("Invalid.\n"); continue; }
            }
            else {scanf("%f", &x);}

            printf("Unary op (S L E C F): ");
            scanf("%s", op);
            op[0] = toupper(op[0]);

            if (op[0] == 'S') {
                if (x < 0) { printf("Error.\n"); continue; }
                r = sqrt(x);
            }
            else if (op[0] == 'L') {
                if (x <= 0) { printf("Error.\n"); continue; }
                r = log(x);
            }
            else if (op[0] == 'E') {r = exp(x);}
            else if (op[0] == 'C') {r = ceil(x);}
            else if (op[0] == 'F') {r = floor(x);}
            else { printf("Invalid.\n"); continue; }

            printf("Result: %.3f\n", r);
        }

        else printf("Invalid choice.\n");
    }
}

int ExitApp() {
    printf("Thank you for using My Command-Line Calculator (CLC)!\n");
    return 1;
}
