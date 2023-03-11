#include <string>
#include <iostream>
using namespace std;
void call(string & ref){
    const string & newstr = ref.substr(0,10);
}
