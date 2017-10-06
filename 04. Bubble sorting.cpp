/*
Сортировка массива методом пузырька с выводом промежуточных результатов
после каждого прохождения внешнего цикла.
*/

#include <iostream>
using namespace std;

void showArray(int arr[], int ar_size) {   //Функция вывода текущего состояния массива
    for (int i; i<ar_size; i++)            //В качестве параметров получает указатель на начало массива
        cout << arr[i] << '\t';            //и количество элементов в нём.
    cout << endl;
}

int main() {
    int numbers[] = {100, 5, 3, 7, -1};   //инициализация и заполнение исходного массива
    int i, j, box;
    int lng = sizeof(numbers)/sizeof(numbers[0]); //количество элементов в массиве
    cout << "initial array:" << endl;             //вывод первоначального массива
    showArray(numbers, lng);
    cout << endl;

    for (i=lng-1; i >= 1; i--) {
        for (j=0; j<i; j++)
            if(numbers[j]>numbers[j+1]) {  //если содержимое рассматриваемой ячейки больше содержимого следующей, то...
                box = numbers[j];               //помещаем содержимое текущей ячейки в коробку
                numbers[j] = numbers[j+1];      //помещаем в текущую ячейку содержимое следующей
                numbers[j+1] = box;             //присваиваем следующей ячейке содержимое коробки
            }
        showArray(numbers, lng);             //вывод состояния массива после каждого прохождения внешнего цикла
    }

    cout << endl << "result array:" << endl; //вывод отсортированного массива
    showArray(numbers, lng);

    return 0;
}
