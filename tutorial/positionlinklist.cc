#include <string>
#include <map>
#include <assert.h>
#include <iostream>
#include "positionlinklist.hh"
substream::substream(){
    globalendindex = 0;
    globalstartindex = 0;
}
substream::substream(const std::string &str,int startindex){
    substr = str;
    globalstartindex = startindex;
    globalendindex = startindex + str.size();
}
void substream::merge(substream &mergestr){
    // substr += mergestr;
    // assert((mergestr.globalstartindex >= globalstartinde));
    int startindex = std::max(globalstartindex,mergestr.globalstartindex);
    int endindex = std::min(globalendindex,mergestr.globalendindex);
    assert(startindex <= endindex);
    startindex -= mergestr.globalstartindex;
    endindex -= mergestr.globalstartindex;
    substr += mergestr.substr.substr(endindex);
    globalstartindex = std::min(globalstartindex,mergestr.globalstartindex);
    globalendindex = std::max(globalendindex,mergestr.globalendindex);
    return;
    // globalendindex = 
}
bool substream::interact(substream &compare){
    return (std::max(globalstartindex,compare.globalstartindex) <= std::min(globalendindex,compare.globalendindex));
}
void substream::print(){
    std::cout << globalstartindex << " " << substr << " " << globalendindex<< std::endl;
}
int mergestream::push(substream &insertstr){
    auto iterator = vec.begin();
    while(iterator != vec.end()){
        if(insertstr.interact(*iterator)){
            insertstr.merge(*iterator);
            vec.erase(iterator);
            this->push(insertstr);
            return 1; // merge with an element in the vector
        }
        iterator++;
    }
    vec.push_back(insertstr);
    return 0; // add a new element into vec
}
bool mergestream::bytestr(std::string &s){
    for(auto iter = vec.begin();iter != vec.end();iter++){
        if(iter->globalstartindex == 0){
            s = iter -> substr;
            vec.erase(iter);
            return true; // actually a string is removed
        }
    }
    return false;
}
int main(){
    std::string str("helloworld");
    // std::cout << str.substr(0,4) << std::endl;
    substream first(str.substr(0,4),0);
    substream second(str.substr(2,4),2);
    mergestream merge;
    std::cout << merge.push(first) << std::endl;
    std::cout << merge.push(second) << std::endl;
    if(1){
        substream obj(str.substr(8),8);
        std::cout << merge.push(obj) << std::endl;
    }
    std::cout << merge.vec.size() << std::endl;
    // first.print();
    // second.print();
    // first.merge(second);
    // first.print();
    // const std::string &refstr = str.substr(0,4);
    
    // substream inst(refstr,0);

    return 0;
}