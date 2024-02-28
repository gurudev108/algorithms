#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to convert ASCII to integer (atoi)
int myAtoi(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    // Handle leading whitespaces
    while (str[i] == ' ') {
        i++;
    }

    // Handle sign
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i++] == '-') ? -1 : 1;
    }

    // Process digits
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return sign * result;
}

// Function to convert integer to ASCII (itoa)
void myItoa(int num, char str[]) {
    int i = 0;
    int sign = (num < 0) ? -1 : 1;

    if (num == 0) {
        str[i++] = '0';
    } else if (num < 0) {
        str[i++] = '-';
        num = -num;
    }

    // Process digits in reverse order
    while (num != 0) {
        str[i++] = '0' + num % 10;
        num /= 10;
    }

    str[i] = '\0';

    // Reverse the string
    int start = (sign < 0) ? 1 : 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Function to convert integer to binary (itob)
void myItob(int num, char str[]) {
    int i = 0;

    if (num == 0) {
        str[i++] = '0';
    } else {
        // Process binary digits in reverse order
        while (num != 0) {
            str[i++] = '0' + num % 2;
            num /= 2;
        }
    }

    str[i] = '\0';

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

// Function to convert ASCII to floating-point (atof)
double myAtof(const char *str) {
    double result = 0.0;
    double fraction = 0.0;
    int sign = 1;
    int i = 0;

    // Handle leading whitespaces
    while (str[i] == ' ') {
        i++;
    }

    // Handle sign
    if (str[i] == '-' || str[i] == '+') {
        sign = (str[i++] == '-') ? -1 : 1;
    }

    // Process integer part
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Process fraction part
    if (str[i] == '.') {
        i++;
        double divisor = 10.0;
        while (str[i] >= '0' && str[i] <= '9') {
            fraction += (str[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }

    return sign * (result + fraction);
}

int main() {
    // Test cases
    const char *str1 = "123";
    const char *str2 = "-456";
    const char *str3 = "   789";
    char buffer[20];

    // Testing atoi
    printf("atoi(\"%s\") = %d\n", str1, myAtoi(str1));
    printf("atoi(\"%s\") = %d\n", str2, myAtoi(str2));
    printf("atoi(\"%s\") = %d\n", str3, myAtoi(str3));

    // Testing itoa
    int num1 = 123;
    int num2 = -456;
    int num3 = 789;
    myItoa(num1, buffer);
    printf("itoa(%d) = %s\n", num1, buffer);
    myItoa(num2, buffer);
    printf("itoa(%d) = %s\n", num2, buffer);
    myItoa(num3, buffer);
    printf("itoa(%d) = %s\n", num3, buffer);

    // Testing itob
    myItob(num1, buffer);
    printf("itob(%d) = %s\n", num1, buffer);
    myItob(num2, buffer);
    printf("itob(%d) = %s\n", num2, buffer);
    myItob(num3, buffer);
    printf("itob(%d) = %s\n", num3, buffer);

    // Testing atof
    const char *str4 = "123.45";
    const char *str5 = "-67.89";
    printf("atof(\"%s\") = %lf\n", str4, myAtof(str4));
    printf("atof(\"%s\") = %lf\n", str5, myAtof(str5));

    return 0;
}

