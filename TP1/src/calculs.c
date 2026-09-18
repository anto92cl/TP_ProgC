#include <stdio.h>

int main(void) {
    int num1 = 12;
    int num2 = 5;
    char ops[] = {'+', '-', '*', '/', '%', '&', '|', '~'};

    for (int i = 0; i < 8; i++) {
        char op = ops[i];

        switch (op) {
            case '+':
                printf("%d + %d = %d\n", num1, num2, num1 + num2);
                break;
            case '-':
                printf("%d - %d = %d\n", num1, num2, num1 - num2);
                break;
            case '*':
                printf("%d * %d = %d\n", num1, num2, num1 * num2);
                break;
            case '/':
                printf("%d / %d = %d\n", num1, num2, num1 / num2);
                break;
            case '%':
                printf("%d %% %d = %d\n", num1, num2, num1 % num2);
                break;
            case '&':
                printf("%d & %d = %d\n", num1, num2, num1 & num2);
                break;
            case '|':
                printf("%d | %d = %d\n", num1, num2, num1 | num2);
                break;
            case '~':
                printf("~%d = %d\n", num1, ~num1);
                break;
            default:
                printf("Operateur inconnu\n");
        }
    }

    return 0;
}
