#include <string>
#include <map>

// #define INTERACTHEAD 1
// #define INTERACTEND 2
// #define

enum INTERCONDITION{INERACTHEAD=1,INTERACTTAIL,CONTAINEDWITHIN,BECONTAINEDWITHOUT,NOTINTERACT};
// 5 condition of interaction/no interaction
class MergeString{
private:
    std::map<int,std::string> strindexmapping;
    size_t unreassembleidbyte;    
public:
    void debug();
    MergeString();
    int merge(const std::string& mergestr,int startindex,std::string &retstr,int lastbyteindex);
};

INTERCONDITION interact(const std::string&,const std::string&,int,int);