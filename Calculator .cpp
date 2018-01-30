/***************************************************************
 Problem: Calculator
 
 Name: Adeola Morren
 ID: 1632933
 Date: 10/6/17
 Status: ( complete)
 ****************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <bitset>


using namespace std;
void showMenu (int& user) {
    
    string input;
    cout << "Please choose one of the following options : " << endl
    << "Direct Input - Press 1" << endl
    << "File Input - Press 2" << endl
    << "To end the program - Press 9" << endl;
    getline(cin, input);
    stringstream(input) >> user;
}
void directUserInput (ofstream & user) {
    string input;
    user.open("calclog.txt", ios:: app);
    if(! user) {
        cout << "There was an error creating the output file for calculations, please make sure that there is enough diskspace, and that you have permissionrights to the folder" << endl << endl;
        
    } else cout << "Your output file was succesfully created. Lets Start Calculating !" << endl << endl;
}

void fileOpenCreate(ifstream & userIn, ofstream & userOut) {
    string input;
    string inputFileName;
    string outputFileName;
    cout << "Please type in the name of the file. (Example: \"myfile.txt\" )" << endl;
    getline(cin, inputFileName);
    
    
    userIn.open(inputFileName);  // This part is to validate user input, and give user another chance to create a file
    
    if(!userIn) {
        cout << "Error opening the file. Make sure file name is typed correctly, and is in same folder as the program." << endl;
    }
    
    outputFileName = inputFileName.insert(inputFileName.find_first_of('.'), "-calculated");
    userOut.open(outputFileName);
    if(! userOut) {
        cout << "There was an error creating your output file, please make sure that there is enough diskspace, and that you have permissionrights to the folder" << endl;
    }
    
}



void streamFunction (ostream & mystream, string clean, double result, string bin)
{
    unsigned int bitV;
    for (int x =0; (pow(2,x) <= result); x++){
        bitV = x;
    }
    cout << fixed  << setprecision(3);
    mystream  << "Result: " << clean  << right << setw(4) << setfill(' ') << " = " << left << setw(18) <<setfill(' ') << result
    << "Hex: " << setw(12) << setfill(' ') << hex  << static_cast<int>(result)
    << "Oct: " <<  setw(12) << setfill(' ') <<  oct << static_cast<int> (result)
    << "Bin: " << setw(12) << setfill(' ') << bin << endl;
    
}


string binaryConverter (const double& result)
{
    string bin;
    int n = result;
    while (n != 0) {
        bin = (n % 2 == 0 ? "0" : "1") + bin;
        n /= 2;
    }
    return bin;
}

double mathFunction (string input, string& clean)
{
    string strSquare, strChar;
    stringstream mystream;
    double intA =0, intB =0, intX =0;
    char sym;
    double total =0;
    stringstream(input) >> intA >> sym >> intB;
    mystream << intA << sym << intB;
    mystream >> strChar;    // Create formatted operation output
    mystream.clear();           // use the mystream for square root in case sqrt
    clean = strChar;    //set formatted by default to the sym
    switch (sym) {
            
        case '/' : total = intA / intB;
            break;
        case '*' : total = intA * intB;
            break;
        case '-' : total = intA -intB;
            break;
        case '+' : total = intA + intB;
            break;
        case '^' : total =  pow(intA,intB);
            break;
        default : stringstream(input) >> sym;
            switch (toupper(sym)) {
                case 'S':
                {
                    int mypos = input.find_first_of("(");
                    if (mypos != string::npos) {
                        string val = input.substr(mypos + 1);
                        stringstream(val) >> intX;
                        total = sqrt(intX);
                        mystream << "√" << intX;
                        mystream >> strSquare;
                        clean = strSquare;
                     
                    }
                    
                }break;
                case 'E':
                    break;
                default : break;
            }
    }

    return total;
}


int main ()
{
    string input, parsed, binary;
    double result;
    ofstream userOut;
    ifstream userin;
    int userChoice;
    int exit;
    do {
        showMenu(userChoice);
        switch (userChoice){
            case 1: {
                    directUserInput(userOut);
                
                do
                {
                    cout << endl << left << setw(27) << setfill(' ') << "Please input operation: ";
                    getline(cin, input);
                    
                    switch(toupper(input.at(0))) {
                        case 'E' : break;
                        default : {
                            result = mathFunction(input, parsed);
                            binary = binaryConverter(result);
                            streamFunction(cout, parsed, result, binary);
                            streamFunction(userOut, parsed, result, binary);
                        } break;
                    
                    }
                } while (toupper(input.at(0)) != 'E');
            }userOut.close();
                break;
                
                
            case 2: {
                fileOpenCreate(userin, userOut);
                while(getline(userin,input))
                {
                    result = mathFunction(input, parsed);
                    binary = binaryConverter(result);
                    streamFunction(cout, parsed, result, binary);
                    streamFunction(userOut, parsed, result, binary);
                }   userOut.close();
            } break;
                
            case 9:
            default: cout <<"that is not a correct Choice please try again" << endl;
        }
    } while(userChoice != 1 && userChoice != 2 && userChoice != 9);
    
    
    
    
    
    cout << "Good Bye !" << endl;
    return 0;
}
