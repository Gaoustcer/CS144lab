#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

// using namespace std;

const std::string&& StreamReassembler::merge(const std::string &str,int index){
    auto iteration = unreassemblestrings.begin();
    auto enditeration = unreassemblestrings.end();
    int strbegin = index;
    int strend = index + str.size();    
    while(iteration != enditeration){
        int iterendsize = iteration -> second.second;
        int iterstartsize = iteration -> second.first;
        int startindex = std::max(iterstartsize,strbegin);
        int endindex = std::min(iterendsize,strend);
        if(startindex <= endindex){
            _sizeofunassemblestring -= iteration -> first.size();
            // add new elementinto str
            if(iterstartsize > index){
                int addbyte = iterstartsize - index;
                std::string newstr = str.substr(0,addbyte) + iteration -> first;
                // _sizeofunassemblestring -= iteration -> first.size();
                unreassemblestrings.erase(iteration);
                // _sizeofunassemblestri
                // this->merge(newstr,index);
                if(static_cast<size_t>(index) <= lastindexofsavedoutput){
                    // return 
                    return this->merge(newstr,index);
                }
                // return string();
            }
            else{
                std::string newstr = iteration -> first + str.substr(iteration -> second.second - index);
                // _sizeofunassemblestring -= iteration -> first.size();
                unreassemblestrings.erase(iteration);
                
                return this->merge(newstr,iteration -> second.first);
                // return std::move(std::string());
            }
        }
        iteration++;
    }
    // _sizeofunassemblestring += str.size();
    if(static_cast<size_t>(index) <= lastindexofsavedoutput){
        return std::move(static_cast<const std::string &>(str));
    }
    _sizeofunassemblestring += str.size();
    // if(index <= lastindexofsavedoutput){

    // }
    unreassemblestrings[str] = std::pair<int,int>(index,index + str.size());
    std::string empty;
    return std::move(empty);
}

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity),unreassemblestrings(std::map<std::string,std::pair<int,int>>()) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const std::string &data, const size_t index, const bool eof) {
    const std::string && writestr = this -> merge(data,index);
    if(index <= lastindexofsavedoutput && (lastindexofsavedoutput - index) >= writestr.size()){
        int lastindex = lastindexofsavedoutput  - index;
        if(writestr.size() > _output.remaining_capacity()){
            // string substr = writestr
            unreassemblestrings[writestr.substr(lastindex)] = std::pair<int,int>(lastindexofsavedoutput,index + writestr.size());
            _sizeofunassemblestring += index + writestr.size() - lastindexofsavedoutput;
        }
        _output.write(writestr.substr(lastindex));
    }
    if(eof){
        int endindex = index + writestr.size();
        if (static_cast<size_t>(endindex) <= lastindexofsavedoutput){
            _output.end_input();
        }
    }
    return ;
    // DUMMY_CODE(data, index, eof);
}

size_t StreamReassembler::unassembled_bytes() const { 
    // int totalsize = 0;    
    return _sizeofunassemblestring;
    // int totalsize = 0;
    // for(auto iteration = unreassemblestrings.begin();iteration != unreassemblestrings.end();iteration++){
        // totalsize += (iteration -> second.second - iteration -> second.first);
    // }
    // return totalsize;
}

bool StreamReassembler::empty() const { 
    if(unreassemblestrings.begin() == unreassemblestrings.end()){
        return true;
    }
    else{
        return false;
    }
 }
