#include <iostream>
#include <string>
using namespace std;
void copy(string &s){
    string str("hello world");
    s = str;
}

int main(){
    string s;
    copy(s);
    cout << s << endl;
}