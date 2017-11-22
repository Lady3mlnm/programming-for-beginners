//#include "stdafx.h"  //For Visual Studio IDE
#include <iostream>
#include <ctime>     //for clock()
#include <string>
#include <sstream>   //for ostringstream
#include <iomanip>   //for setprecision() and setw()
#include <windows.h> //for Sleep()
#include <fstream>   //for file output
using namespace std;

const int ATTEMPTS = 3;       //number of measuring cycles
const string OUTPUT_FILE = "E:\\test2.txt";    //output file  -for Visual Studio (doesn't work in CodeBlocks)
//const char OUTPUT_FILE[] = "E:\\test2.txt";  //output file -for CodeBlocks & Visual Studio
const int ARRAY_SIZE = 200000;

void ShowArray(int *ar, int lng) {
    for (int i = 0; i < lng; i++) {
        cout << setw(6) << ar[i];
        if (i % 10 == 9)
            cout << endl;
    }
    cout << endl;
}

float SortingTest(int *ar, int *arOriginal, int lng) {
    copy(arOriginal, arOriginal+lng, ar);

    //ShowArray(ar, lng);                         //check

    clock_t timeStart;  //variable of measuring cycle
    //*** Global variables of code ***
    int i, j;
    timeStart = clock();

    //--- SORTING ALGORITHM (BEGIN) ---
    int key;
    for (i = 1; i < lng; ++i) {
        key = ar[i];
        j = i - 1;
        while (j > -1 && ar[j] > key) {
            ar[j + 1] = ar[j];
            j--;
        }
        ar[j + 1] = key;
    }
    //--- SORTING ALGORITHM (END) ---
    
    //ShowArray(ar, lng);                         //check
    
    return (float)(clock() - timeStart) / CLOCKS_PER_SEC;
}

//Function for converting float to numbers.
//This is more accurate path than to use to_string(float_number).
//Info from https://www.daniweb.com/programming/software-development/threads/146718/conversion-from-float-to-string
string floatToString(float number) {
    ostringstream buff;
    buff << setprecision(3) << fixed << number;  //or buff.precision(3); //without <iomanip>
                                                 //   buff << fixed << number;
    return buff.str();
}


int main() {
    //*** Variables of measuring cycle ***
    int *arTest = new int[ARRAY_SIZE];       //declaration of test array & its copy
    int *arSaving = new int[ARRAY_SIZE];

    //srand(time(NULL));       // pseudo-random number generator is not initialized
    for (int i = 0; i < ARRAY_SIZE; ++i) {   //initialization of arrays
        arTest[i] = (rand() % 1100) - 100;
    }
    copy(arTest, arTest+ARRAY_SIZE, arSaving);
    float arA[ATTEMPTS];    //array of attempt results
    ofstream myFile;
    string str;             //string for result accumulation

    //=== TEST CYCLE ===
    for (int countA = 0; countA<ATTEMPTS; countA++) {
        arA[countA] = SortingTest(arTest, arSaving, ARRAY_SIZE);
        cout << "Test #" << countA + 1 << " is complete. " <<
                "Execution time: " << floatToString(arA[countA]) << "\n\n";
        Sleep(1000);
    }

    //=== RESULTS PROCESSING ===
    float sum = 0;            //saving to string original results
    str = "Attempts: ";
    for (int countA = 0; countA<ATTEMPTS; countA++) {
        str = str + floatToString(arA[countA]) + ", ";
        sum += arA[countA];
    }
    str.resize(str.length() - 2);

    str += "\nSorted:   ";    //results sorting
    for (int i = 0; i < ATTEMPTS - 1; i++)
        for (int j = i + 1; j < ATTEMPTS; j++)
            if (arA[j] < arA[i])
                swap(arA[j], arA[i]);

    for (int countA = 0; countA<ATTEMPTS; countA++)   //saving to string sorted results
        str = str + floatToString(arA[countA]) + ", ";
    str.resize(str.length() - 2);

    str += "\nAverage:     " + floatToString(sum / ATTEMPTS) + "\n\n";

    cout << str;                                      //output results to screen and file
    myFile.open(OUTPUT_FILE, ios::app);
    myFile << str;
    myFile.close();

    delete[] arTest;
    delete[] arSaving;

    system("pause");
    return 0;
}