#include "strmerge.hh"
#include <string>
using namespace std;
int main(){
    string s;
    s += "hello world this is mess";
    string ret;
    MergeString merge;
    merge.merge(s.substr(0,10),0,ret,-1);
    merge.debug();
    merge.merge(s.substr(3,11),3,ret,-1);
    merge.debug();
}