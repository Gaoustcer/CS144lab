#include <vector>
#include <iostream>
#define N 128
using namespace std;
class T{
public:
    T(){
        cout << "create\n";
    }
    ~T(){
        cout << "delete\n";
    }
};
int main(){
    vector<int> vec;
    cout << (vec.begin() == vec.end()) << endl;
    for(int i = 0;i < N;i++){
        vec.push_back(i);
    }
    cout << vec.size() << endl;
    vec.erase(vec.begin());
    cout << vec.size() << endl;
}