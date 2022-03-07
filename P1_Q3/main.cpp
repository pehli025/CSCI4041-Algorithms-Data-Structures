#include<iostream>
#include<fstream>
using namespace std;

int main(int argc, const char * argv[]){
    const int MAX = 100000;
    double numArr[MAX]; // holder for items in the input file
    int n = 0;
    ifstream in; // create input stream

    in.open(argv[1]); // open the 2nd argument input.txt
    
    if(in.fail()){ // file checking, if it doens't open, exit the program and return the message.
        cout << "ERROR: FILE " << argv[1] << " COULD NOT OPEN" << endl;
        return 1; 
    }

    in >> numArr[n];
    int i = numArr[0]; // 

    while(in) {
        n++;
        in >> numArr[n];
    }
    numArr[n] = '\0';
    int temp;
    for(int i =1; i < n-1; i++) {
        for (int j =1; j<n-(i+1); j++) {
            if(numArr[j] > numArr[j+1]){ // compare and swapping
                temp=numArr[j];
                numArr[j] = numArr[j+1];
                numArr[j+1] = temp;
            }
        }
    }

    ofstream out;
    out.open("output.txt"); // open or create output.txt
    out << numArr[i]; // write output
    out.close(); // close input file
    return 0;
}

