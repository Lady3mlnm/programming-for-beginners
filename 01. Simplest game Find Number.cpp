/*
Одна из простейших игр "Угадай число". Программа загадывает число от 1 до 10,
циклически запрашивает у пользователя предположения и выводит подсказки "больше/меньше".
*/

#include <iostream>
#include <ctime>
using namespace std;

int request() {
    int x;
    cout << "Enter your quess: ";
    cin >> x;
    return x;
}

int main() {
    srand(time(NULL));
    int r = 1 + rand() % 10;
    int answer;

    do {
        answer = request();
        if (answer<r)
            cout << "My number is bigger." << endl;
        else if (answer > r)
            cout << "My number is smaller." << endl;
        else
            cout << endl << "You did it!" << endl;
    } while (answer!=r);

    return 0;
}
