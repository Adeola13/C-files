#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>



using namespace std;

struct Values {
    int number;
    int counter =0;
    
    Values (int a){
        
        number =a;
       
    }
    
};

bool fileOpen (ifstream & readFile, bool & value) {
    string fileName;
    
    
    cout << "Enter the name of the file  ";
    getline(cin, fileName);
    readFile.open(fileName);
    if (!readFile) {
        cout <<" error opening the file" << endl;
        value = false;
    }
    return value;
}




bool fileOutput (ofstream & outputFile, bool & value) {
    value = true;
    
    outputFile.open("output.txt");
    
    if(!outputFile) {
        cout << "Your file could not be created";
        value = false;
    }
 
    return value;
}


void writeFile (vector<Values> allNumbers,  ofstream & outputFile, int & counter) {
    outputFile <<"Duplicates and Stats- File: Output.txt" << endl
               << "Total values in data file: " << counter << endl
               << "Low value: " << allNumbers.at(0).number << endl
               << "High value: " << allNumbers.end().number << endl
               << "======================================" << endl
               << "Duplicated values:" << endl;
    
    for (int i =0; i < allNumbers.size(); i++) {
        if (allNumbers.at(i).counter >= 1) {
            
        
            outputFile  << dec << setw(9) << setfill(' ') << dec <<  allNumbers.at(i).number << "occured"  << allNumbers.at(i).counter << "times";
        outputFile << endl;
            
        }
    }
    
    outputFile << "======================================" << endl
    << "Non- Repeated Values:" << endl;
    
    
    for (int i =0; i < allNumbers.size(); i++) {
        
        if(allNumbers.at(i).counter < 1) {
            outputFile << allNumbers.at(i).number << endl;
        }
    }
    
}

int main ()
{
    string input;
    bool value = true;
    bool inserted = false;
    int number =0, counter =0;
    ifstream readFile;
    ofstream outputFile;
    vector <Values> allNumbers;
    vector<int> hallo;
    
    
  
    
    do  {
        fileOpen(readFile, value);
    } while (! value);
    
    
    
    while (getline(readFile, input)) {
    
        stringstream(input)>> number;
        allNumbers.push_back(Values(number));
        
        
        for (int x=0; x  > allNumbers.at(x).number||  ! allNumbers.empty(); x++ ){
            
            inserted = false;
            if ( number < allNumbers.at(x).number) {
                allNumbers.insert(x, Values(number));
                inserted = true;
            } else if(number == allNumbers.at(x).number) {
                allNumbers.at(x).counter ++;
            }
        }
        
        if (! inserted) {
            allNumbers.push_back(Values(number));
            
        }
        counter ++;

    }
    
    
    
    
    
    
    
    if(fileOutput (outputFile, value)) {
        
        writeFile(allNumbers, outputFile, counter);
        readFile.close();
        outputFile.close();
        
        cout << "Finished analyzing the file, results are found in output.txt" << endl
        << "Goodbye." << endl;
    } else cout << "File could not be created, please run the program aggain";
    
}





