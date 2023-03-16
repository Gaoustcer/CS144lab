#include <string>
#include <map>

// #define INTERACTHEAD 1
// #define INTERACTEND 2
// #define

// class substring{
// private:
    // std::string str;
    
// };


enum INTERCONDITION{INERACTHEAD=1,INTERACTTAIL,CONTAINEDWITHIN,BECONTAINEDWITHOUT,NOTINTERACT};
// 5 condition of interaction/no interaction
class MergeString{
private:
    std::map<int,std::string> strindexmapping; // new interact with each other within the map
    size_t unreassembleidbyte;    // the size of unassembled string in the map
public:
    int numberofmapping(); // the number of integar-string pair in strindexmaping
    void debug();
    size_t sizeofunreassemblebyte() const{
        return unreassembleidbyte;
    }
    std::pair<size_t,std::string> getsmallestindexsubstr();
    // size_t howmanybyteleft() const{
    //     return unreassembleidbyte;
    // }
    void insert(std::string &str,size_t index);
    MergeString();
    
    void merge(const std::string& mergestr,int startindex);// lastbyteindex is the index of last byte which has been stored in Bytestream
};

INTERCONDITION interact(const std::string&,const std::string&,int,int);