#include <string>
#include <iostream>
using namespace std;
string &rets(){
    string str("Hello world");
    return str;
}

int main(){
    string & s= rets();
    cout << s << endl;
}