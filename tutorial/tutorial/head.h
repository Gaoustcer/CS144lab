#include <string>

class Test{
public:
	std::string  refstr;
	int x;
	Test();
	Test(std::string &str);
	Test(int _x):x(_x){}
	void print();
};
class substream{
public:
	int x,y;
	std::string substr;
	substream(std::string & ref,int start);
};