/***************************************************************
 Problem: Calculator
 
 Name: Adeola Morren & Mukhammadnozim Islamov
 ID: 1632933 & 1668193
 Date: 10/6/17
 Status: ( complete)
 ****************************************************************/


#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void ceasarDecrypt (const int & a, ifstream & loadFile, ofstream & decryptFile){
    string b;
    int x;
    while (getline(loadFile, b)) {
        for (int i = 0; i < b.size(); i++) {
            
            
            x = b.at(i);
            b.at(i) = isalpha(x) *   (((islower(x) *         ((x -a - 'a'+26) % 26 + 'a')) + ((!islower(x)) * ((x - a - 'A'+26) % 26 + 'A')))) +
            isdigit(x) * ((x -a - '0'+10) % 10 + '0') + (!isalnum(x) * ' ');
            
            
        }
    }
    
    cout << b << endl;
    decryptFile <<b;
    
    return;
}

void Caesar(const int & a, ifstream & loadFile, ofstream & encryptFile) {
    string b;
     char x;
    while (getline(loadFile, b)) {
        for (int i = 0; i < b.size(); i++) {
            
            
            x = b.at(i);
            b.at(i) =   isalpha(x) *   (((islower(x) *           ((x + a - 'a') % 26 + 'a'))       +     ((!islower(x)) * ((x + a - 'A') % 26 + 'A')))) +
            isdigit(x) * ((x  + a - '0') % 10 + '0') + (!isalnum(x) * '^');
            
            
        }
        cout << b << endl;
        encryptFile << b;
    }
    
    return;
    
  
    
}


void displayMenu (int & user) {
    string input;
    cout << "Welcome to the file encryptor" << endl
    << "Select one of the following options to:" << endl
    << "1 To encrypt a message" << endl
    << "2 To decrypt a message" << endl
    << "9 To exit the program" << endl << endl;
    getline(cin, input);
    stringstream(input) >> user;
}

bool openCreateFile (ifstream & loadFile, ofstream & encryptFile, string ifileName, string ofileName) {
    encryptFile.open(ofileName +".txt");
    loadFile.open(ifileName +".txt");
    if (!loadFile)
        cout << "error loading your file" << endl;
    else if (!encryptFile)
        cout << "error creating output file" << endl;
    return (loadFile && encryptFile);
}


int main ()
{
    int userChoice, key = 10;
    ifstream loadFile;
    ofstream outputFile;
    string input;
    
        displayMenu(userChoice);
        switch (userChoice) {
            case 1 :
            {
                if(openCreateFile(loadFile, outputFile, "message", "encrypted")) {
                        Caesar(key, loadFile, outputFile);
                }
                loadFile.close();
                outputFile.close();
            }
                break;
                
            case 2:
            {
                if(openCreateFile(loadFile, outputFile, "encrypted", "decrypted")) {
                    ceasarDecrypt(key, loadFile, outputFile);
                }
                loadFile.close();
                outputFile.close();
                 break;
            }
                
                
                
        }
    

return 0;

}

