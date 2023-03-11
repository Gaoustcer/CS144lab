#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string> vec;

void remove(string &s){
    
    auto iter = vec.begin();
    s = *iter;
    vec.erase(iter);
    return ;
}

int main(){
    vec.push_back("hello");
    vec.push_back("world");
    vec.push_back("this");
    string s;
    remove(s);
    cout << s << endl;

}