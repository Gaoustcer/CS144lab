#include <map>
#include <string>
#include <vector>
// class range

class substream{
public:
    int globalstartindex,globalendindex;
    std::string substr;
    substream();
    void merge(substream &mergestr);
    void print();
    substream(const std::string &str,int startindex);
    bool interact(substream &compare);
};
class mergestream{
public:
    std::vector<substream> vec;
    int push(substream & insertstr);
    bool bytestr(std::string &s); 
};
class unmergedsubstream{

};