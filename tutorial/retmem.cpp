#include <iostream>
using namespace std;
class Test{
public:
    int x;
    Test(int _x):x(_x),value(x+1){}
    int & ref(){
        int & ref = x;
        return ref;
    }
    int detect(){
        return value;
    }
    int & retpri(){
        int & pri = value;
        return pri;
    }
private:
    int value;
};

int main(){
    Test inst(10);
    int & ref = inst.retpri();
    cout << "origin number is " << inst.detect() << endl;
    ref++;
    cout << "current number is " << inst.detect() << endl;
}