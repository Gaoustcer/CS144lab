#include "strmerge.hh"
#include <string>
#include <map>
#include <iostream>
#include <limits>
#include <typeinfo>
// int x;
// type(x
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

void MergeString::insert(std::string &str,size_t index){
    unreassembleidbyte += str.size();
    strindexmapping[index] = str;
    // insert a string with start index
}

int MergeString::numberofmapping(){
    return strindexmapping.size();
}


std::pair<size_t,std::string> MergeString::getsmallestindexsubstr(){
// iteration through the whole map and find the smallest <index,str> pair
    if(strindexmapping.begin() == strindexmapping.end()){
        return std::pair<size_t,std::string>(0,std::string(""));
    }
    // auto iterator = strindexmapping.begin();
    auto smallestiterator = strindexmapping.begin();
    size_t logsmallest = std::numeric_limits<size_t>::max();
    for(auto iterator = strindexmapping.begin();iterator != strindexmapping.end();iterator++){
        if(iterator->first <= logsmallest){
            smallestiterator = iterator;
            logsmallest = iterator -> first;
        }
    }
    // delete and remove the pair in the mapping
    unreassembleidbyte -= smallestiterator->second.size();
    strindexmapping.erase(smallestiterator);
    return *smallestiterator;
}
void MergeString::merge(const std::string &data,size_t startindex){
    std::string strmerge = data;
    INTERCONDITION type;
    // std::cout << "merge str " << mergestr << std::endl;
    size_t headstrcount = 0;
    // std::string & 
    for(auto iteration = strindexmapping.begin();iteration != strindexmapping.end();iteration++){
        // std::string & newstr = retstr;
        type = interact(data,iteration->second,startindex,iteration->first);
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
            // itertor string contain data from head to tail
            unreassembleidbyte -= iteration -> second.size();
            strindexmapping.erase(iteration);
            this->merge(strmerge,startindex);
            break;
        case INERACTHEAD:
            // data is in front of iterator
            headstrcount = iteration -> first - startindex;
            strmerge = data.substr(0,headstrcount) + (iteration -> second);
            unreassembleidbyte -= iteration -> second.size();
            strindexmapping.erase(iteration);
            this->merge(strmerge,startindex);
            break;
        case INTERACTTAIL:
            headstrcount = startindex - iteration -> first;
            // std:: cout << "tail length is " << headstrcount << std::endl;
            strmerge = iteration -> second.substr(0,headstrcount) + data;
            unreassembleidbyte -= iteration -> second.size();
            strindexmapping.erase(iteration);
            this -> merge(strmerge,iteration -> first);
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
    // find no interaction string
    strindexmapping[startindex] = data;
    
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