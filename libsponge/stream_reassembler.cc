#include "stream_reassembler.hh"
#include <limits>
#include <map>
#include <iostream>

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;



MergeString::MergeString(){
    unreassembleidbyte = 0;
    strindexmapping = std::map<size_t,std::string>();
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
    unreassembleidbyte += data.size();
    
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



StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {
    _lastbyterindex = 0;
    _lastbytesteam = std::numeric_limits<size_t>::max();
    _Merge = MergeString();
    _unreassembelebyte = _Merge.sizeofunreassemblebyte();
}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const uint64_t index, const bool eof) {
    // std::string & str = std::string("");
    std::string str;
    size_t start = static_cast<size_t>(index);
    if(eof){
        _lastbytesteam = index + data.size();
    }
    #ifdef DEBUG
    std::cout << "merge size " << _Merge.numberofmapping() << " data size is " << data.size() << " " << data << " index is " << index  << " eof is " << eof << std::endl;
    _output.Debug();
    #endif
    _Merge.merge(data,start);
    _unreassembelebyte = _Merge.sizeofunreassemblebyte();
    #ifdef DEBUG
    _Merge.debug();
    #endif
    std::cout << "Iterator " << _unreassembelebyte << endl;
    while(_unreassembelebyte){

        auto smallindex = _Merge.getsmallestindexsubstr();
        #ifdef DEBUG
        std::cout << "smallest " << smallindex.first << " str is " << smallindex.second  << " last byte index " << _lastbyterindex << std::endl;
        #endif
        if(smallindex.first <= _lastbyterindex && smallindex.first + smallindex.second.size() > _lastbyterindex){
            std::cout << "write " << smallindex.second << std::endl;
            _output.write(smallindex.second.substr(_lastbyterindex - smallindex.first));
            _lastbyterindex = _output.bytes_written() + 1;
            if(_lastbyterindex >= _lastbytesteam){
                _output.end_input();
            }
            // return ;
        }
        else if(smallindex.first > _lastbyterindex){
            // insert it into merge
            _Merge.insert(smallindex.second,smallindex.first);
            _unreassembelebyte = _Merge.sizeofunreassemblebyte();
            return ;
        }
        _unreassembelebyte = _Merge.sizeofunreassemblebyte();
        // else if(smallindex.first + smallindex.second.size() > _lastbyterindex){
        //     size_t insertsize = std::max<size_t>(_lastbyterindex - smallindex.first,0);
        //     size_t concatsize = smallindex.first + smallindex.second.size() - _lastbyterindex;
        //     _Merge.insert();
        // }
    }
    _unreassembelebyte = _Merge.sizeofunreassemblebyte();
    return;
    
    if(eof){
        _lastbytesteam = start + data.size();
    }
    // auto smallestpair = _Merge.getsmallestindexsubstr();
    while(1){
        
        if(_Merge.numberofmapping() == 0){
            return;
        }
        std::cout << "_merge size " << _Merge.numberofmapping() << endl;
        auto smallestpair = _Merge.getsmallestindexsubstr();
        #ifdef DEBUG
        std::cout << "Debug the merge object\n";
        _Merge.debug();
        
        std::cout << "iterator " << smallestpair.second.size()  << " first is " << smallestpair.first << " _last is " << _lastbyterindex << std::endl;
        #endif
        if(smallestpair.first > _lastbyterindex){
            // insert it into _Mergestr
            #ifdef DEBUG
            std::cout << "insert " << smallestpair.second.size() << std::endl;
            std::cout << "return after insert\n";
            #endif
            _Merge.insert(smallestpair.second,smallestpair.first);
            _unreassembelebyte = _Merge.sizeofunreassemblebyte();
            
            return ;
        }   
        else{
            // try to merge with Bytestream
            size_t concatsize = smallestpair.second.size() - \
                (_lastbyterindex - smallestpair.first);
            // size_t writesize;
            
            if(concatsize <= _output.remaining_capacity()){
                _output.write(smallestpair.second.substr(_lastbyterindex - smallestpair.first));
                // writesize = smallestpair.second.size() + smallestpair.first;
                // if(writesize == _lastbytesteam){
                //     _output.end_input();
                // }
                // writesize 
            }
            else{
                // Bytestream is not enough large,need to concat
                size_t startindex = _lastbyterindex - smallestpair.first + _output.remaining_capacity();
                std::string insertstring = smallestpair.second.substr(startindex);
                size_t mergesize = std::min<size_t>(_Merge.sizeofunreassemblebyte(),insertstring.size());
                insertstring = insertstring.substr(0,mergesize);
                _Merge.insert(insertstring,startindex);
                startindex = _lastbyterindex - smallestpair.first;
                _output.write(smallestpair.second.substr(_lastbyterindex - smallestpair.first,_output.remaining_capacity()));   
                // if(_Merge.sizeofunreassemblebyte() < insertstring.size()){
                    // _Merge.insert(startindex,insertstring.substr(0,))
                // }
            }
            _lastbyterindex = _output.bytes_written() + 1;
            if(_lastbyterindex >= _lastbytesteam){
                _output.end_input();
            }
        }
    }
    // d
    // DUMMY_CODE(data, index, eof);
}

size_t StreamReassembler::unassembled_bytes() const { 
    // CONST class method could only call const member
    return _unreassembelebyte + 1;
}

bool StreamReassembler::empty() const { return {_unreassembelebyte == 0}; }


