#include <iostream>
#include <string>
using namespace std;
int main(){
    string str("Hello world");
    string && rightref = std::move(str);
    str = "This is Messi";
    cout << str << endl;
    cout << rightref << endl;
}