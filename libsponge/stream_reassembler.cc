#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {
    _lastbyterindex = 0;
    _lastbytesteam = 0;
    _Merge = MergeString();
    _unreassembelebyte = _Merge.sizeofunreassemblebyte();
}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const uint64_t index, const bool eof) {
    // std::string & str = std::string("");
    std::string str;
    _Merge.merge(data,index);
    if(eof){
        _lastbytesteam = index + data.size();
    }
    // auto smallestpair = _Merge.getsmallestindexsubstr();
    while(1){
        auto smallestpair = _Merge.getsmallestindexsubstr();
        if(smallestpair.first > _lastbyterindex){
            // insert it into _Mergestr
            _Merge.insert(smallestpair.second,smallestpair.first);
            return ;
        }   
        else{
            // try to merge with Bytestream
            size_t concatsize = smallestpair.second.size() - \
                (_lastbyterindex - smallestpair.first);
            size_t writesize;
            if(concatsize <= _output.remaining_capacity()){
                _output.write(smallestpair.second.substr(_lastbyterindex - smallestpair.first));
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
        }
    }
    // d
    // DUMMY_CODE(data, index, eof);
}

size_t StreamReassembler::unassembled_bytes() const { 
    // CONST class method could only call const member
    return _unreassembelebyte;
}

bool StreamReassembler::empty() const { return {}; }
