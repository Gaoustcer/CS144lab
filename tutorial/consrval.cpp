#include <iostream>
#include <string>

using namespace std;

void retlocalref(string &ref){
    string str("Hello world");
    ref = str;
}

int main(){
    string voidstr;
    string &str = voidstr;
    retlocalref(str);
    cout << str << endl;
// /    const string&& s = std::move(str);
    // cout << s << endl;
    // s[0] = 'j';

}