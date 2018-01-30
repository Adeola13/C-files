/***************************************************************
 Problem: Lab Decissions
 Name: Adeola Morren
 ID: 1632933
 Date: 09/11/2017
 Status: (complete )
 ****************************************************************/

#include <iostream>
#include <sstream>
#include <string>
using namespace std;


char packageType;
int hourUsage, days, hourMax;
string monthName, userInput;
double monthlyBill, providedHours, monthlyPrice, overUsagePrice, extraHours, formulaA, formulaB;
int main ()
{
    cout << "Enter the type package that you have purchased? (A, B, C) pl" << endl;
    getline(cin, userInput);
    stringstream(userInput) >> packageType;
    
    cout << "How many hours were used?" << endl;
    getline(cin, userInput);
    stringstream(userInput) >> hourUsage;
    
    cout << "What is the name of the month?" << endl;
    getline(cin, monthName);

    switch (monthName.at(2)) {
        case 'r':
        case 'n':
        case 'o':
        case 'p':
        case 'v':
            
            days = 30 +(monthName.at(1) == 'a');
            break;
            
        case 'b' :
            days = 28;
            break;
            
        default: days = 31;
    }
    
    hourMax = days * 24;
    formulaA = (9.95 + (((hourUsage -10) > 0)) * ((hourUsage -10) * 2));
    formulaB = (14.95 + (((hourUsage - 20) > 0) * (hourUsage -20)));

    if (hourUsage > 0 && hourUsage <= hourMax) {
        switch (packageType)
        {
            case 'A' :   cout << endl << "Your bill due is: $" << formulaA << endl;
                if ((formulaA - formulaB) > 0) {
                    cout << "Your savings with PackageB would be: $" << (formulaA - formulaB) << endl;
                
                    if ((formulaA - 19.95) > 0) {
                        cout <<  "Your savings with PackageC would be $" << (formulaA- 19.95) << endl;
                    }
                }
                break;
            
            case 'B' : cout << endl << "Your bill amount due is $" << formulaB << endl;
                if ((formulaB - 19.95) >  0) {
                    cout << "Your savings with PackageC would be $" << (formulaB -19.95) << endl;
                }
                break;
            
            case 'C' : cout << endl << "Your bill amount due is: $" << 19.95 << endl;
                break;
        
            default : cout << "Please enter the correct type of package" << endl;
        }
    } else cout << "Please enter a valid amount of hours" << endl;
}
