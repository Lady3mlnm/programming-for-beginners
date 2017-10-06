/*
Немного более усложнённый вариант.
Калькулятор работает с вещественными числами.
В процессе ввода чисел осуществляется передача строки в функцию
*/
#include <iostream>
using namespace std;

float enterNumber(string str){  //альтернативный вариант: enterNumber(char str[])
    float x;
    cout << str;
    cin >> x;
    return x;
}

int main() {
    float x = enterNumber("Enter first number: ");
    float y = enterNumber("Enter second number: ");
    char op;
    cout << "Enter operation: ";
    cin >> op;

    switch(op) {
    case '+':
        cout << "Sum: " << x+y;
        break;
    case '-':
        cout << "Difference: " << x-y;
        break;
    case '*':
        cout << "Product: " << x*y;
        break;
    case '/':
        (y!=0) ? cout << "Fraction: " << x/y      //тернарная условная операция
               : cout << "Error. Divisor is 0";
        break;
    default:
        cout << "Unknown operation";
    }

    return 0;
}
