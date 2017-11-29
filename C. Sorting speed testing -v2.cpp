#include "stdafx.h"
#include <iostream>
#include <ctime>     //for clock()
#include <string>
#include <sstream>   //for ostringstream
#include <iomanip>   //for setprecision() and setw()
#include <windows.h> //for Sleep()
#include <fstream>   //for file output
using namespace std;

const int MAX_TESTS = 3;       //number of measuring cycles
const string OUTPUT_FILE = "E:\\test7.txt";    //output file  -for Visual Studio
//const char OUTPUT_FILE[] = "E:\\test7.txt";  //output file -for CodeBlocks
const int MAX_SIZE = 100;
const float MAX_TIME = 10;
const int START_SIZE = 10;
const int FACTOR = 10;


struct rtnResult {
	int arSize;        //size of test array
	float avTime;      //average time
	int nmbTests;      //number of tests
};


/*
Function for converting float to numbers.
This is more accurate path than to use to_string(float_number).
Info from https://www.daniweb.com/programming/software-development/threads/146718/conversion-from-float-to-string
*/
string floatToString(float number) {
	ostringstream buff;
	buff << setprecision(3) << fixed << number;
	//or buff.precision(3); buff << fixed << number; //without <iomanip>
	return buff.str();
}


/*
Optional output array to console for validation of work
*/
void ShowArray(int *ar, int lng) {
	for (int i = 0; i < lng; i++) {
		cout << setw(6) << ar[i];
		if (i % 10 == 9) cout << endl;
	}
	cout << endl;
}


/*
Result processing of each test series
*/
void ResultProcessing(int *arTest, rtnResult &crtTest, string &str1, string &str2, string &str3) {
	cout << "Size: " << crtTest.arSize
		<< ";\tav.Time: " << floatToString(crtTest.avTime)
		<< ";\tTests: " << crtTest.nmbTests << endl;

	/*cout << arTest[0] << "\t" << arTest[1] << "\t...\t"    //Show part of array
	<< arTest[crtTest.arSize / 2 - 2] << "\t" << arTest[crtTest.arSize / 2 - 1] << "\t" << arTest[crtTest.arSize / 2] << "\t" << arTest[crtTest.arSize / 2 + 1] << "\t...\t"
	<< arTest[crtTest.arSize - 2] << "\t" << arTest[crtTest.arSize - 1] << "\n\n";*/
	
	ShowArray(arTest, crtTest.arSize);                 //Show full array
	if (crtTest.avTime > 0) {
		str1 += to_string(crtTest.arSize) + "\t";
		str2 += floatToString(crtTest.avTime) + "\t";
		str3 += to_string(crtTest.nmbTests) + "\t";
	}
	else {
		str1 += "\t";
		str2 += "\t";
		str3 += "\t";
	}
}


/*
Total results are output to console and writen into the file on disk
After that strings are cleared for future use
*/
void ResultOutput(string &str1, string &str2, string &str3) {
	ofstream myFile;

	cout << endl;
	cout << str1 << endl
		<< str2 << endl
		<< str3 << endl << endl;

	myFile.open(OUTPUT_FILE, ios::app);
	myFile << str1 << endl
		<< str2 << endl
		<< str3 << endl << endl;
	myFile.close();

	str1 = "";
	str2 = "";
	str3 = "";
}


/*
Test series of 1 algorithm with permanent size of sort array
*/
void SortingTest(int *ar, int *arSaving, rtnResult &crtTest) {
	int lng = crtTest.arSize;               //length of sorting array
	clock_t timeStart, timeEnd, timeTotal;  //for time measuring
	timeTotal = 0;
	int iTest;

	for (iTest = 1; iTest <= MAX_TESTS && timeTotal <= MAX_TIME * 3 * CLOCKS_PER_SEC; iTest++) {
		copy(arSaving, arSaving + lng, ar);         //restore sorting array
		//ar[0] = 5000;                             //for check of algorithm work
		//ar[lng - 1] = -500;
		Sleep(100);

		timeStart = clock();
		//--- TEST ALGORYTHM (BEGIN)
		for (int i = 0; i<lng - 1; ++i)
			for (int j = lng - 1; j>i; --j)
				if (ar[j] < ar[j - 1])
					swap(ar[j], ar[j - 1]);
		//--- TEST ALGORYTHM (END)
		timeEnd = clock();
		Sleep(100);
		timeTotal += (timeEnd - timeStart);
	}

	iTest--;
	crtTest.nmbTests = iTest;
	crtTest.avTime = (float)timeTotal / (iTest * CLOCKS_PER_SEC);
}



int main() {
	int *arTest = new int[MAX_SIZE];         //declaration of test array & its copy
	int *arSaving = new int[MAX_SIZE];
	string str1 = "", str2 = "", str3 = "";  //strings for result accumulation
	rtnResult crtTest;                       //currentTest - structure. containting info about current test


											 /*** TEST ARRAY CREATION ***/
	srand(0);                              //arrays are always initialized by the same way
	for (int i = 0; i < MAX_SIZE; ++i) {   //initialization of arrays
		arTest[i] = (rand() % 1100) - 100;
	}
	copy(arTest, arTest + MAX_SIZE, arSaving);


	/*** ENGINE OF PROGRAM (begin) ***/
	str1 = "Test algorithm\n";
	for (crtTest.arSize = START_SIZE; crtTest.arSize <= MAX_SIZE; crtTest.arSize *= FACTOR) {

		SortingTest(arTest, arSaving, crtTest);

		ResultProcessing(arTest, crtTest, str1, str2, str3);
		if (crtTest.avTime > MAX_TIME || crtTest.nmbTests < 3)
			break;
	}

	ResultOutput(str1, str2, str3);
	/*** ENGINE OF PROGRAM (end) ***/


	delete[] arTest;
	delete[] arSaving;
	return 0;
}