/***************************************************************
 Problem: Theatre Program !
 Description:
 Name: Adeola Morren
 ID: 1632933
 Date: 10/6/17
 Status: ( complete) everything works, format used for the loadfile and save file = (row,col,price);
 only problem is with saving the file it will print every row,col,price the empty seats as well, however if you want to load that file into the program, it wont cause any errors.
 ****************************************************************/

#include<iostream>
#include<iomanip>
#include<sstream>
#include<vector>
#include<fstream>
#include<ostream>
const int ROW = 15;
const int COL = 30;
using namespace std;

void safeFile (vector<vector<char> >& theatre, vector<int>prices) {
    ofstream userOut;
    string fileName = "theatre-new.txt";
    userOut.open(fileName);
    bool sold;
    while(! userOut) {
        cout << "There was an error creating your output file, please make sure that there is enough diskspace, and that you have permissionrights to the folder" << endl;
        userOut.open(fileName);
    } cout << "your output file will be saves as \"theatre-new.txt\"." << endl;
    
    for (int i = 0; i< ROW; i++)
    {
        for (int j = 0; j< COL ; j ++) {
            sold = (theatre.at(i).at(j) == '*');
            switch (sold) {
                case 1: userOut << i +1 << "," << j +1 << "," << prices.at(i) << endl;
                    break;
                default: userOut << i+1 << "," << 0 << "," <<prices.at(i) << endl;
            }
        }
    }
    userOut.close();
}

void loadFile (vector<vector<char> >& theatre, vector<int> & prices, int & count, double & ticketSales) {
    ifstream userIn;
    string input;
    string seats;
    string inputFileName;
    int row, col;
    double price;
    char temp, temp2;
 
            cout << "Please type in the name of the file. (Example: \"myfile.txt\" )" << endl;
            getline(cin, inputFileName);
            userIn.open(inputFileName);
            while(!userIn) {
                cout << "Error opening the file. Make sure file name is typed correctly, and is in same folder as the program." << endl;
                getline(cin, inputFileName);
                userIn.open(inputFileName);
            }
            
            while(getline(userIn,seats)){
                stringstream(seats) >> row >> temp>> col >> temp2 >> price;
                prices.at(row-1) = price;
                ticketSales += price;
                if (col > 0){
                    theatre.at(row-1).at(col-1) = '*';
                    count +=1;
                }
            } userIn.close();
}

void getPrices (vector<int> & prices) {
    string input;
    for (int x = 0; x < ROW ; x++){
        cout << "Please input the price for " << x + 1 << " row: ";
        getline(cin, input);
        stringstream(input) >> prices.at(x);
    }
}

void disPlayMenu (int & user) {
    string input;
    cout << endl << endl << "Please select one of the following keys to: " << endl
    << "1 To view total ticket sales" << endl
    << "2 To view how many seats are sold in each row" << endl
    << "3 To view how many seats are available in the entire auditorium" << endl
    << "4 To purchase more tickets" << endl
    << "5 To Save the file" << endl
    << "21 to exit the program" << endl << endl;
    getline(cin, input);
    stringstream(input) >> user;
    
}
void displayChart (const vector<vector<char> >& theatre) {
    cout <<endl<< setw(23) << "SEATS" << endl<<endl;
    for (int i = 0; i < ROW; i++) {
        cout << "Row "  <<  left << setw(7) << i + 1 ;
        for (int j = 0; j < COL; j++) {
            cout<< theatre.at(i).at(j);
        }
        cout << endl;
    }
}

void getSeats (vector<vector<char> >& theatre, const vector<int>prices, int & count, double & sales) {
    string input;
    int row =0, col =0, amo =0;
    do
    {
        cout << "How many tickets do you want?" << endl;
        getline(cin, input);
        stringstream(input) >> amo;
        
        if (isdigit(amo)) {
            cout << "Error please enter a number for ticket input" << endl;
        }
    } while(!stringstream(input)>> amo);
    
    cout << "Please enter the row number followed by a space and then seat number (row, seat)" << endl;
    for (int x = 0; x< amo; x++) {
        do {
            cout << "Ticket" << x+1 << ": " << endl;
            getline(cin, input);
            stringstream(input)>>row >> col;
            if (! stringstream(input)>> row>> col || row > 15 || col > 30) {
                cout << "Error please input a whole number that is in the range of seats and rows" << endl;
            }else if(theatre.at(row-1).at(col-1) == '*') {
                cout << "That ticket has already been sold please select a seat that is available: " << endl;
            }
        } while (! stringstream(input)>> row>> col || theatre.at(row-1).at(col-1) == '*');
        theatre.at(row -1).at(col -1) = '*';
        sales += prices.at(row-1);
        count += 1;
    }
}

void viewRowSold (int& amount, const vector<vector<char> >& theatre)
{
    string input;
    int row;
    cout << endl << "Please select the row you want to view" << endl;
    getline(cin, input);
    stringstream(input) >> row;
    for (int x = 0; x <COL; x++) {
        bool sold = (theatre.at(row -1).at(x) == '*');
        amount += sold;
    } cout << endl << "The amount of seats sold in row " << row << " is: " << amount  << endl;
}

void viewTicketSales(double& sales) {
    cout << endl << "The amount of ticket sales is $" << sales << endl;
    
}
void exitContinue (int& user)
{
    string input;
    cout << "To exit the program press 21. To view the menu, press any other key to continue" << endl;
    getline(cin, input);
    stringstream(input) >> user;
}

void viewAudiAvailable (const int& seatsSold, int& available) {
    available = (ROW * COL) - seatsSold;
    cout << endl << "The amount of seats available in total auditorium is " <<  available << endl;
}

int main()
{
    string input;
    vector<vector<char>>theatre(ROW, vector<char>(COL, '#'));
    vector<int>prices(ROW);
    int totalTicketCounter =0, userChoice =0, seatInRowSold =0, availableSeats =0;
    double ticketSales;
    
    cout << "Hi welcome to the theatre" << endl;
    cout << "Would you like to load an existing file? Press 1 if you want to. Press any other key to begin empty and input prices for each row" << endl;
    getline(cin, input);
    stringstream(input) >> userChoice;
    switch(userChoice){
        case 1 :
            loadFile(theatre, prices, totalTicketCounter, ticketSales);
            displayChart(theatre);
            break;
        default : { getPrices(prices);
                    getSeats(theatre, prices, totalTicketCounter, ticketSales);
                    displayChart(theatre);
        } break;
    }

    
    do {
        disPlayMenu(userChoice);
        switch (userChoice)
        {
            case 1 : viewTicketSales(ticketSales);
                exitContinue(userChoice);
                break;
                
            case 2:  viewRowSold(seatInRowSold, theatre);
                exitContinue(userChoice);
                break;
                
            case 3: viewAudiAvailable(totalTicketCounter, availableSeats);
                exitContinue(userChoice);
                break;
            case 4: getSeats(theatre, prices, totalTicketCounter, ticketSales);
                displayChart(theatre);
                exitContinue(userChoice);
            case 5: safeFile(theatre, prices);
                
            case 21:
                break;
            default: cout << "that is not a valid option please select one of the following options " << endl;
        }
        
    }while (userChoice != 21 );
    
    

    cout << "Good Bye !" << endl;
    return 0;
}


