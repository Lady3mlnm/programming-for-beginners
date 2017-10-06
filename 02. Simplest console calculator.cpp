/*
Простейший консольный калькулятор на 4 действия
Принимает только целые числа
*/
#include <iostream>
using namespace std;

int main() {
    int x, y;
    char op;
    cout << "Enter first number: ";
    cin >> x;

    cout << "Enter second number: ";
    cin >> y;

    cout << "Enter operation: ";
    cin >> op;

    //реализация калькулятора через if...else
    if (op=='+')
        cout << "Sum: " << x+y;
    else if (op=='-')
        cout << "Difference: " << x-y;
    else if (op=='*')
        cout << "Product: " << x*y;
    else if (op=='/')
        if (y!=0)
            cout << "Fraction: " << double(x)/y;
        else
            cout << "Error. Divisor is 0";
    else
        cout << "Unknown operation";

    //реализация калькулятора через switch
    /*
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
        (y!=0) ? cout << "Fraction: " << x/y
               : cout << "Error. Divisor is 0";
        break;
    default:
        cout << "Unknown operation";
    }
    */

    return 0;
}
