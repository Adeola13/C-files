/*
Assignment for polygraphic substitution cypher.
*/
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
#include<cctype>
using namespace std;

void createMatrix(vector<string> & vec )
{
    
    cout << "Enter key: ";
    string key;
    getline(cin, key);
    string alpha = "abcdefghiklmnopqrstuvwxyz";
    remove(key.begin(), key.end(), ' ');
    for (int i = 0, j = i +1; i < key.size() && j < key.size(); i++, j++) {                 // Finding and Deleting similar letters in key word
       
        
        if (key.at(i) == key.at(j)) {
                key.erase(j, 1);
        }
    }
    
    
    for (int i = 0; i < key.size(); i++) {				// Finding and Deleting similar letters in alphabet
        for (int j = 0; j < alpha.size(); j++) {
            if (key.at(i) == alpha.at(j)) {
                alpha.erase(j, 1);
            }
        }
    }
    string last = key + alpha;

    
    for (int i =0; i < 5; i++) {
        vec.at(i)  = last.substr((i * 5), 5);            // initalize vector
    }
    

}

void  encryptMessage (string & message, vector<string> & vec) {
    string key = vec.at(0) + vec.at (1) + vec.at(2) + vec.at(3) + vec.at(4);        // create one string with the entire vector
    
    int ax, ay, bx, by, a, b;
    remove(message.begin(), message.end(), ' ');
    
    
    for (int i =0; i + 1 < message.size(); i ++) {
        if (message.at(i) == message.at(i+1)) {
            message.at(i+1) = 'x';
        }
    }
    
    for (int k = 0; k + 1 <message.size(); k = k + 2) {
        a = key.find(message.at(k));                                        //position of letter 1 message in the vector<entirestring>
        b = key.find(message.at(k+1));                                      // position letter 2
        
        ay = a/5 ;                                                          // gives us the row number of the vector of letter 1
        ax = a%5 ;                                                          // gives us collumn number of the vector of letter 1
        
        by = b/5;                                                           // same here for letter 2
        bx = b%5 ;
        
        
      
        if (ay == by) {                       // if letters are in the same row  + 1, making it that if (position +1 > 5) it goes to beginning of the row
            message.at(k) = vec.at(by).at(((ax + 5) % 5) + 1 );
            message.at(k + 1) = vec.at(by).at(((bx + 5) % 5)  + 1);
        } else if (ax == bx) {                                          // same principle applied but for the collumns
            message.at(k) = vec.at(((ay + 5) % 5) + 1).at(ax);
            message.at(k + 1) = vec.at(((by + 5) % 5) +1).at(bx);
        } else {                                                         //speaks for itself..
            message.at(k) = vec.at(ay).at(bx);
            message.at(k+1) = vec.at(by).at(ax);
        };
    }
    
    cout << "Encrypted message: "  << message << endl;
    
    
}

void  decryptMessage (string & message, vector<string> & vec) {
    string key = vec.at(0) + vec.at (1) + vec.at(2) + vec.at(3) + vec.at(4);
    int ax, ay, bx, by, a, b;                                                               //same principle as encrypt but reversed.
    
    
    
    for (int k = 0; k + 1 <message.size(); k = k + 2) {
        a = key.find(message.at(k));
        b = key.find(message.at(k+1));
        
        ay = a/5 ;
        ax = a%5 ;
        by = b/5;
        bx = b%5 ;
        
        
        
        if (ay == by) {
            message.at(k) = vec.at(by).at(((ax + 5) % 5) - 1 );
            message.at(k + 1) = vec.at(by).at(((bx + 5) % 5)  - 1);
        } else if (ax == bx) {
            message.at(k) = vec.at(((ay + 5) % 5) - 1).at(ax);
            message.at(k + 1) = vec.at(((by + 5) % 5) - 1).at(bx);
        } else {
            message.at(k) = vec.at(ay).at(bx);
            
            message.at(k+1) = vec.at(by).at(ax);
        };
    }
    
    for (int i =0; i < message.size(); i++) {
        if (message.at(i) == 'x') {
            message.at(i) = message.at(i-1);
        }
    }
    
    cout << endl << "Decypted Message: " << message << endl;
    
    
}

int main()
{	
    vector <string> vec (5);
    createMatrix(vec);
    
    string message;
    
    cout << "Please enter your message " << endl;
    getline(cin, message);
    
    
    for (int i = 0; i < 5; i ++) {
        cout << vec.at(i) << endl;
    }
    
    cout << endl;
    
    encryptMessage(message, vec);
    
    decryptMessage(message, vec);
    
    return 0;
}


/* 

- best known multiple letter polygraphic substitution cipher
- encrypts pair of letters (disgraphs), instead of single letters.
- based on the use of a 5 x 5 matrix of letters constructed using a keyword
- invented by britisch Scientists sir Charles Wheatstone in 1854
- used as the standard field system in WW2 by the us, britisch and australians armies to protect important secrets during actual combat.

 
 ask user for passwords & message
 fill in matrix accordingly
 encrypt then decrypt message
 
 

*/