#include <iostream>
#include <vector>

using namespace std;


bool primeFunction (int number) {
    

    bool isPrime = true;
    for (int i = 1; i < number && isPrime; i+=2 ) {
        isPrime = (number % i != 0);
    }
    
    return isPrime;
}
int main ()
{
    
    vector<int> prime100;
    
    
    for (int x=0; x < 10000; x++) {
        if (primeFunction(x)) {
            prime100.push_back(x);
        }
    }
    
    for(int x =0; x< prime100.size(); x++) {
        cout << prime100.at(x) << endl;
    }
    
    
    
}


