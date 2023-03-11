#include <map>
#include <string>
#include <iostream>

using namespace std;
int main(){
    map<string,int> test;
    string str("hello");
    test[str] = 2;
    str = "world";
    test[str] = 3;
    for(auto iter = test.begin();iter != test.end();iter++){
        cout << iter->first << iter->second << endl;
    }
    // test['hello'] = 2;
    // test[string('world')] = 3;
}