#include <iostream>
#include <string>
using namespace std;

int main(){
    string str("Hello world");
    const string & ref = str;
    string leftvalue = ref;
    leftvalue[0] = 'A';
    cout << leftvalue << endl;
    // string &ref = str;
    // string * ptr = ref;

}