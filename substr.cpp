#include <iostream>
#include <string>
#include <map>
using namespace std;

int main(){
	map<int,string> m;
	m[1] = "hello world";
	m[4] = "thsis";
	cout << m.upper_bound(2)->second << endl;
	// string str("Hello world");
	// cout << str.substr(0,str.size()) << endl;
	// cout << str.substr(1,4) << endl;
}

