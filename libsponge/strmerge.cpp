#include "strmerge.hh"
#include <string>
#include <map>
#include <iostream>

MergeString::MergeString(){
    unreassembleidbyte = 0;
    strindexmapping = std::map<int,std::string>();
}

void MergeString::debug(){
    std::cout << "Debug" << std::endl;
    for(auto iteration = strindexmapping.begin();iteration != strindexmapping.end();iteration++){
        std::cout << iteration->first << " " << iteration -> second << std::endl;
    }
}

int MergeString::numberofmapping(){
    return strindexmapping.size();
}

void MergeString::merge(const std::string &mergestr,int startindex,std::string &retstr,int lastbyteindex){
    INTERCONDITION type;
    // std::cout << "merge str " << mergestr << std::endl;
    size_t headstrcount = 0;

    for(auto iteration = strindexmapping.begin();iteration != strindexmapping.end();iteration++){
        std::string & newstr = retstr;
        type = interact(mergestr,iteration->second,startindex,iteration->first);
        // std::cout << "type is " << type << std::endl;
        switch (type)
        {
        case NOTINTERACT /* constant-expression */:
            /* code */
            break;
        case CONTAINEDWITHIN:
            // return ;            
            break;
        case BECONTAINEDWITHOUT:
            unreassembleidbyte -= iteration -> second.size();
            strindexmapping.erase(iteration);
            this->merge(mergestr,startindex,retstr,lastbyteindex);
            break;
        case INERACTHEAD:
            headstrcount = iteration -> first - startindex;
            newstr = mergestr.substr(0,headstrcount) + iteration -> second;
            unreassembleidbyte -= iteration -> second.size();
            strindexmapping.erase(iteration);
            this->merge(newstr,startindex,retstr,lastbyteindex);
            break;
        case INTERACTTAIL:
            headstrcount = startindex - iteration -> first;
            // std:: cout << "tail length is " << headstrcount << std::endl;
            newstr = iteration -> second.substr(0,headstrcount) + mergestr;
            // std:: cout << ""
            unreassembleidbyte -= iteration -> second.size();
            // std::cout << "map size " << strindexmapping.size() << std::endl;
            strindexmapping.erase(iteration);
            // std::cout << "map size " << strindexmapping.size() << std::endl;
            // std::cout << "insert new str " << newstr << std::endl;
            this -> merge(newstr,iteration -> first,retstr,lastbyteindex);
            break;
        default:
            std::cout << "default errror\n";            
            break;
        }
        if(type != NOTINTERACT || type != CONTAINEDWITHIN){
            return ;
            // return type;
        }
    }    
    if(startindex <= lastbyteindex && startindex + mergestr.size() > lastbyteindex){
        retstr = mergestr.substr(lastbyteindex - startindex);
    }
    else if (startindex > lastbyteindex)
    {
        unreassembleidbyte += mergestr.size();
        strindexmapping[startindex] = mergestr;
        retstr = std::string();
        /* code */
    }
    else{
        retstr = std::string();
    }
    
}

INTERCONDITION interact(const std::string &insertstr,const std::string &targetstr,int insertindex,int targetindex){
    // insertstr: The str which is going to insert into mapping
    // targetstr: The str as the key of strindexmap
    // index is the start index of two string
    int maxstart = std::max(insertindex,targetindex);
    // int maxend = std::min
    int insertend = insertstr.size() + insertindex;
    int targetend = targetstr.size() + targetindex;
    int minend = std::min(insertend,targetend);
    INTERCONDITION type;
    if(minend < maxstart){
        // type = 
        type = NOTINTERACT;
    }
    else if(insertend == targetindex){
        return INTERACTTAIL;
    }
    else if(insertindex == targetend){
        return INERACTHEAD;
    }
    else{
        if(targetend >= insertend && targetindex <= insertend){
            type = CONTAINEDWITHIN;
        }// targetstr contain insertstr    
        else if (targetend < insertend && targetindex > insertindex )
        {
            type = BECONTAINEDWITHOUT;
        }// insertstr contain targetstr
        else if (insertindex < targetindex){
            type = INERACTHEAD;
        }// insert tail is in targetstr(from head concat)
        else{
            type = INTERACTTAIL;
        }// insert head is in targetstr(from tail concat)    
    }
    return type;
}