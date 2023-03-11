#include <iostream>
#include <string>
#include "head.h"
void Test::print(){
	std::cout << x << std::endl;
}
Test::Test(std::string &str){
	x = str.size();
	refstr = str;
	// refstr = ("hello world");
}
Test::Test(){
	x = 1024;
	refstr = "";
}
int main(){
	Test defaultinit;
	defaultinit.print();
	Test testinst(10);
	testinst.print();
}

substream::substream(std::string &ref,int start){
	substr = ref;
	x = start;
	y = x + substr.size();
}

