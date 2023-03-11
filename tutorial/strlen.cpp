#include <iostream>
#include <ctime>
#include <string>
using namespace std;
int main(){
    int N = 1024 * 32;
    string str("helloworldthisismessi");
    for(int i = 0;i < N;i++){
        str.append("c");
    }
    int start = clock();
    for(int i = 0;i < N;i++){
        str.size();
    }
    int end = clock();
    cout << "size clock cost " << end - start << endl;
    start = clock();
    for(int i = 0;i < N;i++){
        // str.size();
    }
    end = clock();
    cout << "simple " << end - start << endl;
}