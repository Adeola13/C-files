/*
Status ; Incomplete

*/

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

struct menuOption {
    vector<string> option;
    bool selection = true;
    menuOption (string a, string b) {
        option.push_back(a);
        option.push_back(b);
    }
    
  
};

struct TextBook {
    string text;
    string upperText;
    
    TextBook (string a, string b) {
        text = a;
        upperText = b;
    }
    
};

struct SearchResult {
    string result;
    int counter;
    
    SearchResult (string a, int b) {
        result = a;
        counter = b;
    }
};



void displayMenu (vector<string>  & menu, vector<menuOption> & menuOptions) {
    for (int x =0; x < menuOptions.size(); x++) {
        cout << menu.at(x) << menuOptions.at(x).option.at(menuOptions.at(x).selection) << endl;   // based upon value of option boolean, it will display on / off   and/or,  menuOptions.at(true) = on, menuOptions.at(false) = off.
    }cout << "4- Exit" << endl;
}


bool loadFile (vector<TextBook> & textBook) {
    bool returnValue = true;
    ifstream text;
    string input, caps;
    text.open("Textbooks.txt");
    if (! text) {
        cout << "Error Opening your File, please run program again" << endl;
        returnValue = false;
    

    } else {
        returnValue = true;
        while (getline(text, input)) {
            for (int x =0; x < input.size(); x++ ) {
                caps += toupper(input.at(x));
            }
            textBook.push_back(TextBook(input, caps));
        }
        
        
    }
    
    text.close();
    
    return returnValue;
}


string upperCase (string & input) {
    string caps;
    for (int x = 0; x < input.size(); x++) {
        caps += toupper(input.at(x));
    }
    return caps;
}


void searchTermSplitter (string & input, vector<string> & searchTerms) {
    string tempWord;
        while (stringstream (input) >> tempWord) {
        searchTerms.push_back(tempWord);
        input.erase(input.find(tempWord), input.size());
        tempWord.clear();
    }
}

void searchFunction (vector<string>& searchTerms, vector<SearchResult>& searchResults, vector<TextBook>& textBook, bool upper, bool andOr, bool ranking ) {
    int searchCounter =0;
    bool inserted;
    
    for (int i = 0; i <textBook.size(); i++) {
        searchCounter = 0;
        for (int j = 0; j <searchTerms.size(); j++) {
            if (upper) {
                if (textBook.at(i).text.find(searchTerms.at(j)) != string::npos) {
                    searchCounter ++;
                }
            } else {
                if(textBook.at(i).upperText.find(searchTerms.at(j)) != string::npos) {
                    searchCounter ++;
                }
            }
        }
        
        if (andOr) {
            if(searchCounter == searchTerms.size()) {
                searchResults.push_back(SearchResult(textBook.at(i).text, 0));
            }
        } else {
            //if (ranking) {
            //searchResults.push_back(SearchResult(textBook.at(i).text, searchCounter));
               // for (int x=0; x  > searchResults.at(x).counter||  ! searchResults.empty(); x++ ){
                    inserted = false;
                //    if ( searchCounter < searchResults.at(x).counter) {
                   //     searchResults.insert(x, SearchResult(textBook.at(i).text, searchCounter));
                       // inserted = true;
                   // }
            //    }
            //}
           // if (! inserted) {
                searchResults.push_back(SearchResult(textBook.at(i).text, searchCounter));
          //  }
        }
    }
}


void displaySearchResults (vector <SearchResult> & searchResults) {
    cout <<"-----------------------------" << endl;
    for (int x = 0; x < searchResults.size(); x++ ) {
        cout << searchResults.at(x).result << endl;
    }
    cout <<"-----------------------------" << endl;
    
}


int main ()
{
    vector<string> menu = { "1- Toggle Case sensitive search (currently", "2- Toggle AND/OR search (currently",
        "3- Toggle Ranking with OR search (currently"};
    vector<menuOption> menuOptions = {menuOption(" ON)", " OFF)"), menuOption(" AND)", " OR)"), menuOption(" ON)", " OFF)")};
    string input,caps;
    
    bool caseSensitive = menuOptions.at(0).selection,
    andOr = menuOptions.at(1).selection,
    ranking = menuOptions.at(2).selection,
    program = true;
    
    
    vector<TextBook> textBook;
    vector<SearchResult> searchResults;
    vector<string> searchTerms;
    
    int choice =0;

    
    program = loadFile(textBook);
    
    while (program )   {
        displayMenu(menu, menuOptions);
        getline(cin, input);
        
        if (! isdigit(input.at(0))) {
            
            if (caseSensitive) {
                upperCase(input);
            }
            
            
            searchTermSplitter(input, searchTerms);
        
            
            searchFunction(searchTerms, searchResults, textBook, caseSensitive, andOr, ranking);
            
            displaySearchResults(searchResults);
                
        } else {
            stringstream(input) >> choice;
            if (choice != 4) {
                menuOptions.at(choice-1).selection =  ! menuOptions.at(choice-1).selection;
            } else program = false;
        }
    
    }

    
    cout << "Goodbye" << endl;
}
