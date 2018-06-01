/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: admin
 *
 * Created on May 28, 2018, 11:24 AM
 */

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*
 * 
 */
const int cols = 3; //set array columns is 3

struct computer {
    int ID;

};
void prntary(int [][cols], int);
int getrow(int);
int getcol(int cols);
bool ispostionhasnum(int [][cols], int, int);
void getnumber(int [][cols], int, int);
bool isnumberrepeat(int [][cols], int, int, int);
void clearposition(int [][cols], int, int, int);
bool infinish(int [][cols], int);
bool issuccess(int [][cols], int);
bool isperfect(int [][cols], int);
void dualsort(vector<int>&, string*, int);
int binarysearch(vector<int>&, int, int);
void displaymessage(string);

int main(int argc, char** argv) {
    //random number
    srand(static_cast<unsigned int> (time(0)));
    //set the name
    const int rows = 3;
    int x;
    int y;
    int Name;
    char choice;
    char choose;
    int round = 1;
    ofstream outfile;
    ifstream infile;
    const int num = 10;
    vector<int>idnum(num);

    computer tester;
    int position;

    outfile.open("records.txt");
    infile.open("ID.txt");

    if (!infile) {
        cout << "Open file failed!" << endl;
        exit(0);
    } else {
        for (int i = 0; i < num; i++) {
            infile >> idnum[i];
        }
    }
    infile.close();
    //before start the game
    cout << "Welcome play the soduka game" << endl;
    cout << "Please enter the name before your start game" << endl;
    cin>>Name;
    cout << "Please enter the password : ";
    cin >> tester.ID;

    while (tester.ID < 100 || tester.ID > 999) {
        cout << "Wrong ID, it must between 100 to 999, re-enter : ";
        cin >> tester.ID;
    }
    while (binarysearch(idnum, num, tester.ID) == -1) {
        cout << "The ID is incalid, please check ID in 'ID.txt'. Re-turn : ";
        cin >> tester.ID;
    }
    position = binarysearch(idnum, num, tester.ID);
    //process here
    do {
        int array[rows][cols] = {};
        int x1;
        int y1;
        //random number
        x1 = rand() % 3;
        y1 = rand() % 3;

        array[x1][y1] = rand() % 9 + 1;
        do {
            prntary(array, rows);
            cout << "Which number do you want to put in ?" << endl;
            x = getrow(rows);
            cout << "Which number do you want to put in ?" << endl;
            y = getcol(cols);
            while (ispostionhasnum(array, x, y)) {
                cout << "This position (" << x << "," << y << ") already has a number " << endl;
                x = getrow(rows);
                y = getcol(cols);
            }
            //Put the number
            getnumber(array, x, y);
            prntary(array, rows);
            //Check the number
            while (isnumberrepeat(array, rows, x, y)) {
                cout << "You only can use this number once " << endl;
                array[x - 1][y - 1] = 0;
                prntary(array, rows);
                getnumber(array, x, y);
                prntary(array, rows);
            }
            cout << "Type Y to clear one position, or any key to continue :";
            cin>>choice;
            while (choice == 'Y' || choice == 'y') {
                clearposition(array, rows, x1, y1);
                cout << "Type Y to clear one position " << endl;
                cin>>choice;
            }
        } while (infinish(array, rows));
        //check win or not
        if (issuccess(array, rows)) {
            if (!outfile) {
                cout << "open file failed!" << endl;
                exit(0);
            } else {
                outfile << "***round" << round << "***" << endl;
                outfile << "-------" << endl;
                for (int i = 0; i < rows; i++) {
                    if (1 != 0) outfile << "|    |    |" << endl;
                    for (int j = 0; j < cols; j++) {
                        outfile << "| " << array[i][j] << " ";
                        if (j % 3 == 2) outfile << "|" << endl;
                    }
                }
                outfile << "-------" << endl;
            }
            //check answer
            if (isperfect(array, rows)) {
                cout << endl;
                cout << "You have done this!" << endl;
                outfile << "Perfect solution" << endl;
                outfile << endl;
            } else {
                cout << endl;
                cout << "Congraduations!!! You won the game!" << endl;
                outfile << "Basic solution!" << endl;
                outfile << endl;
            }
            cout << "Type N to start a new a new round, or q to quit this game: " << endl;
            cin>>choose;
            switch (choose) {
                case 'n':
                case 'N': choose = 'N';
                    break;
                default: choose = 'Q';
            }
        } else {
            cout << endl;
            cout << "You didn't win this game!" << endl;
            cout << "Type Y to clear one position, or not N to start a new round, or Q to quit this game";
            cin>>choose;
            switch (choose) {
                case 'y':
                case 'Y': choose = 'Y';
                    break;
                case 'n':
                case 'N': choose = 'N';
                    break;
                default: choose = 'Q';
            }
            while (choose == 'Y') {
                clearposition(array, rows, x1, y1);
                cout << "Type Y to clear one positon, or any key to continue: ";
                cin>>choose;
            }
        }
        round++;
    } while (choose == 'N');
    return 0;
}

void displaymessage(string name) {
    cout << "welcome " << name << " join the game world !" << endl;
    cout << "1. You will get a 3*3 chart which already had a random " << endl;
    cout << "2. You need to use 1-9(each number only can use once) fill out" << endl;
    cout << "3. You must make it to the sum of each row and each column" << endl;
    cout << "   equal to 15 to get basic win, and if you can make a perfect" << endl;
    cout << "   answer which the sum of each slash equal 15 also. " << endl;
    cout << "4. You can clear the position(except original one)" << endl;
    cout << "Enter any key to go!" << endl;
    cin.ignore();
    cin.get();
    cout << "Problem challenge: " << endl;
}

int binarysearch(vector<int>&id, int size, int value) {
    int first = 0;
    int last = size - 1;
    int middle;
    int position = -1;
    bool found = false;
    do {
        middle = (first + last) / 2;
        if (id[middle] == value) {
            found = true;
            position = middle;
        } else if (id[middle] > value) last = middle - 1;
        else first = middle + 1;
    } while (!found && first <= last);
    return position;
}

void dualsort(vector<int>&ID, string *name, int size) {
    int startscan, minindex, minvalue;
    string tempname;
    for (startscan = 0; startscan < (size - 1); startscan++) {
        minindex = startscan;
        minvalue = ID[startscan];
        tempname = *(name + startscan);
        for (int index = startscan + 1; index < size; index++) {
            if (ID[index] < minvalue) {
                minvalue = ID[index];
                tempname = *(name + index);
                minindex = index;
            }
        }
        ID[minindex] = ID[startscan];
        *(name + minindex) = *(name + startscan);
        ID[startscan] = minvalue;
        *(name + startscan) = tempname;
    }
}

bool isperfect(int a[][cols], int rows) {
    bool flag = false;
    if (issuccess(a, rows)) {
        if ((a[0][0] + a[1][1] + a[2][2]) == 15 && (a[0][2] + a[1][1] + a[2][0]) == 15)
            flag = true;
    }
    return flag;
}

bool issuccess(int a[][cols], int rows) {
    bool flag = false;
    int sumr1 = 0, sumr2 = 0, sumr3 = 0;
    int sumc1 = 0, sumc2 = 0, sumc3 = 0;
    for (int j = 0; j < cols; j++) {
        sumr1 += a[0][j];
        sumr2 += a[1][j];
        sumr3 += a[2][j];
    }
    for (int i = 0; i < rows; i++) {
        sumc1 += a[i][0];
        sumc2 += a[i][1];
        sumc3 += a[i][2];
    }
    if (sumr1 == 15 && sumr2 == 15 && sumr3 == 15 && sumc1 == 15 && sumc2 == 15 && sumc3 == 15)
        flag = true;
    return flag;
}

bool isfinish(int a[][cols], int rows) {
    bool flag = false;
    int times = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (a[i][j] == 0)times++;
        }
    }
    if (times != 0)flag = true;
    return flag;
}

void clearposition(int a[][cols], int rows, int x1, int y1) {
    int x;
    int y;
    x = getrow(rows);
    y = getcol(cols);
    while (x - 1 == x1 && y - 1 == y1) {
        cout << "The question number can not be cleared" << endl;
        cout << "Please re-enter in the position." << endl;
        x = getrow(rows);
        y = getcol(cols);
    }
    while (!ispostionhasnum(a, x, y)) {
        cout << "This position (" << x << "," << y << ") does not have a number need to clear." << endl;
        cout << "Please re-enter the position you want to clear." << endl;
        x = getrow(rows);
        y = getcol(cols);
    }
    a[x - 1][y - 1] = 0;
    prntary(a, rows);
}

bool isnumberrepeat(int a[][cols], int rows, int x, int y) {
    int times = 0;
    bool found = false;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (a[x - 1][y - 1] == a[i][j]) {
                times++;
            }
        }
    }
    if (times != 1) found = true;
    return found;
}

void getnumber(int a[][cols], int x, int y) {
    cout << "please enter in a number you want put in (" << x << "," << y << ") :";
    cin >> a[x - 1][y - 1];
    while (a[x - 1][y - 1] <= 0 || a[x - 1][y - 1] > 9) {
        cout << "Wrong number, re-enter : ";
        cin >> a[x - 1][y - 1];
    }
}

bool ispositionhasnum(int a[][cols], int x, int y) {
    bool flag = false;
    if (a[x - 1][y - 1] != 0)flag = true;
    return flag;
}

int getcol(int cols) {
    int col;
    cout << "Please enter in the number of column : ";
    cin>>col;
    while (col < 1 || col > cols) {
        cout << "Wrong number for column, re-enter in number (1,2,3) : ";
        cin>>col;
    }
    return col;
}

int getrow(int rows) {
    int row;
    cout << "Please enter in the number of row : ";
    cin>>row;
    while (row < 1 || row > rows) {

    }
}

void prntary(int a[][cols], int row) {
    cout << "-------" << endl;
    for (int i = 0; i < row; i++) {
        if (i != 0)cout << "|  |  |  |" << endl;
        for (int j = 0; j < cols; j++) {
            if (a[i][j] == 0)cout << "| ";
            else cout << "| " << a[i][j] << " ";
        }
    }
    cout << "-------" << endl;
    cout << endl;
}