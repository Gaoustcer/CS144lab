#include <string>
#include <iostream>
#include <vector>

using namespace std;
// vector<string> vec;
// vec.push_back("Hello world");

string generate(vector<string> &vec){
    // string str("Hello world");
    auto iter = vec.begin();
    string str = *iter;
    vec.erase(iter);
    cout << "delete string " << str << endl;
    return str;
}

int main(){
    vector<string> vec;
    vec.push_back("Hello world");
    vec.push_back("This is Messi");
    string st = generate(vec);
    cout << st << endl;
}