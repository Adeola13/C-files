/*
This program is incomplete but the purpose of this assignment is to work with classes in c++
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
const int SRG_LEG = 1000,  SRG_ANK = 1200, SRG_KNEE = 1600, SRG_SHLDR = 1800, SRG_HSTRNG = 1700, DAY_RATE = 295;
const double MORPHINE =12.95, PARACETAMOL = 10.95, IBROPRUPHEN = 10.95, CODEINE = 19.95, ASPIRIN = 6.95;


class Item {
public:
    string name;
    double price;
    Item (string n, double p) {
        name = n;
        price = p;
    }
};

class HospitalMethods {
public:
    void display(vector<Item>);
    void setGet(vector<Item>, vector<Item>, int);
    
};


class PatientAccount {
public:
    vector<Item> ItemList;
    string name;
    string adress;
    int age;
    int SSN;
    PatientAccount (string n, string ad, int a, int s) {
        name = n;
        age = a;
        adress = ad;
        SSN = s;
    }
    double totalCost;
    int dayCount;
    double getTotalCost () ;
    void displayBill ();
};


class Surgery : HospitalMethods {
public:
    const vector <Item> SurgeryList = {{"LegSurgery", SRG_LEG}, {"AnkleSurgery",SRG_ANK}, {"KneeSurgery",SRG_KNEE}, {"ShoulderSurgery", SRG_SHLDR},{"HamstringSurgery", SRG_HSTRNG}};
};


struct Pharmacy : HospitalMethods {
public:
    const vector <Item> pharmacyList = {{"Morphine", MORPHINE}, {"Paracetamol", PARACETAMOL},{"Ibropruphen", IBROPRUPHEN},{"Codeine",CODEINE},{"Aspirin",ASPIRIN}};
};



/******************************************************************************************************/
void HospitalMethods :: display (vector<Item> itemList) {
    for (int x =0; x < itemList.size(); x ++) {
        cout << itemList.at(x).name << "   " << itemList.at(x).price << endl;
    }
    return;
}

void HospitalMethods :: setGet (vector<Item> itemIn, vector<Item> itemOut, int index) {
        itemOut.push_back(itemIn.at(index));
        return;
    }
double PatientAccount:: getTotalCost () {
    for (int i =0; i < ItemList.size(); i++) {
        totalCost += ItemList.at(i).price;
    }
    return totalCost + (dayCount * DAY_RATE);
}

void PatientAccount:: displayBill () {
    cout << "Patients Bill: " << endl << setw(15) << "ItemName " << left << setw(19) << "Price" << endl;
    for (int i = 0; i < ItemList.size() ; i++) {
        cout << setw(15) << ItemList.at(i).name << ":  $" << left << setw(19) << ItemList.at(i).price << endl;
    }
    cout << "your total cost is:  $" << getTotalCost();
    return;
}



/***********************************************************************************************/
void displayMenu (int& user) {
    string input;
    cout << "Hello Welcome to the Hospital. Please select one of the following options: " << endl
        << "1. Add a New Patient" << endl
        << "2. Display a patient’s detailed bill." << endl
        << "3. Check out a patient" << endl
        << "4. Add Surgery item to patients account." << endl
        << "5. Add Pharmacy item to patients account." << endl
        << "To end the program - Press 9" << endl;
        getline(cin, input);
        stringstream(input) >> user;
}

void addNewPatient (vector<PatientAccount> patientList) {
    string name, adress, input;
    int age, ssn;
    
    cout << "Please enter your name:  ";
    getline(cin, name);
    
    cout << endl << "Please enter your age:  ";
    getline(cin, input);
    
    stringstream(input) >> age;
    cout << endl << "Please enter your adress followed by a '.':  ";
    getline(cin, input);
    
    stringstream(input) >> adress;
    cout << endl << "Please enter your Social Security Number:  ";
    
    getline(cin, input);
    stringstream(input) >> ssn;
    
    PatientAccount Patient (name, adress, age, ssn);
    patientList.push_back(Patient);
}


int getPatientNumber (vector<PatientAccount> patientList) {
    string input;
    int number;
    for (int i =0; i < patientList.size(); i++) {
        cout << i + 1 << "    " << patientList.at(i).name << endl;
    }
    cout << "Select the patientnumber:  ";
    getline(cin, input);
    stringstream (input) >> number;
    return number - 1;
}

void displayPatient () {
    
}

void checkOutPatient () {
    
}

void addSurgeryItem () {
    
}

void addPharmacyItem () {
    
}

/*******************************************************************************************/
int main ()
{
    vector<PatientAccount> patientList;
    int userChoice;
    int patientId;
    do {
        displayMenu(userChoice);
        switch (userChoice) {
                
            case 1: addNewPatient (patientList);
                break;
                
            case 2: {
                patientId = getPatientNumber(patientList);
                patientList.at(patientId).displayBill();
                
            }
                break;
                
            case 3:
                patientId = getPatientNumber(patientList);
                patientList.erase(5);
                break;
                
            case 4: addSurgeryItem();
                break;
                
            case 5: addPharmacyItem();
                break;
        }
    } while (userChoice != 9);
    
        
}
