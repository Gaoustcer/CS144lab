#include <string>
#include <iostream>

using namespace std;

string readstr(string &str,size_t size){
    return str.substr(str.size() - size);
}

int main(){
    string str("Hello world");
    // cout << str.size() - 3 <<  endl;
    // string s = readstr(str,8);
    cout << str.substr(1) << endl;
    cout << str << endl;
    // cout << str << endl;
}