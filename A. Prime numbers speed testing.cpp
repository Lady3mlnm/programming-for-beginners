//#include "stdafx.h"  //For Visual Studio IDE
#include <iostream>
#include <ctime>     //for clock()
#include <string>
#include <sstream>   //for ostringstream
#include <iomanip>   //for setprecision()
#include <windows.h> //for Sleep()
#include <fstream>   //for file output
#include <vector>    //is required for std::vector
using namespace std;

const int ATTEMPTS = 3;  //number of measuring cycles
const string OUTPUT_FILE = "E:\\test3.txt";    //output file -for Visual Studio (doesn't work in CodeBlocks)
//const char OUTPUT_FILE[] = "E:\\test3.txt";  //output file -for CodeBlocks & Visual Studio

float TestedCode() {
    clock_t timeStart;  //variable of measuring cycle
    //*** Global variables of code ***
    const int NL = 1000000;  //last  number of range
    float duration;
    vector <int> primeNumbers;
    int i, j;

    timeStart = clock();

    //--- EXECUTION CODE (BEGIN) ---
    primeNumbers.push_back(2);
    for (i = 3; i <= NL; i += 2) {
        for (j = 3; j*j <= i && i%j != 0; j+=2) {
        }
        if (j*j > i)
            primeNumbers.push_back(i);
    }
    //--- EXECUTION CODE (END) ---

    duration = (float)(clock() - timeStart) / CLOCKS_PER_SEC;
    cout << "Amount: " << primeNumbers.size() <<                 //check
            ",  last prime number: " << primeNumbers.back() << endl;

    return duration;
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
    float arA[ATTEMPTS];    //array of attempt results
    float fBucket;          //for array sorting
    ofstream myFile;
    string str;             //string for result accumulation

    //=== TEST CYCLE ===
    for (int countA = 0; countA<ATTEMPTS; countA++) {
        arA[countA] = TestedCode();
        cout << "Test #" << countA + 1 << " is complete. " <<              //check
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
            {
                fBucket = arA[j]; arA[j] = arA[i]; arA[i] = fBucket;
            }

    for (int countA = 0; countA<ATTEMPTS; countA++)   //saving to string sorted results
        str = str + floatToString(arA[countA]) + ", ";
    str.resize(str.length() - 2);

    str += "\nAverage:     " + floatToString(sum / ATTEMPTS) + "\n\n";

    cout << str;                                      //output results to screen and file
    myFile.open(OUTPUT_FILE, ios::app);
    myFile << str;
    myFile.close();

    system("pause");
    return 0;
}