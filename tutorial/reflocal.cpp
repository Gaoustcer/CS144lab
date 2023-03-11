#include <iostream>
#include <string>
using namespace std;
string && relocal(){
    string str("hello world");
    return std::move(str);
}
string & ret(){
    string str("Hello world");
    return str;
}

int main(){
    cout << relocal() << endl;
}
