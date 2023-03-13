#include "byte_stream.hh"
#include <iostream>
using namespace std;
int main(){
    ByteStream entity(15);
    cout << entity.remaining_capacity() << endl;
}