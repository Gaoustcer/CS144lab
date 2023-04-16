#include "stream_reassembler.hh"
#include <limits>
#include <map>
#include <iostream>
#include <assert.h>
#include <queue>
#define DEBUG
// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;
void print(std::deque<char> &q){
  for(auto iterator = q.begin();iterator != q.end();iterator++){
    std::cout << *iterator;
  }
  std::cout << std::endl;
}
StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {
    #ifdef DEBUG
    std::cout << "init" << capacity << endl;
    #endif
    _lastbyteassemble = 0;
    _unassemblebytecount = 0;
    _unassembleindicator = std::deque<bool>(0);
    _unassemblestr = std::deque<char>(0);
    _lasteofbyte = std::numeric_limits<size_t>::max();
}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.

void StreamReassembler::_writeintoBytestream(){
    string s;
    size_t remainsize = _output.remaining_capacity();
    while(_unassembleindicator.size()&&_unassembleindicator.front() && remainsize){
        _unassembleindicator.pop_front();
        remainsize -= 1;
        _unassemblebytecount -= 1;
        s.insert(s.end(),_unassemblestr.front());
        _unassemblestr.pop_front();
    }
    _output.write(s);
    return ;
}
size_t StreamReassembler::firstunassemble() const{
    size_t index = 0;
    while(1){
        if(index >= _unassembleindicator.size() || *(_unassembleindicator.begin() + index) == false){
            break;
        }
        index += 1;
    }
    return index;
}
void StreamReassembler::push_substring(const string &data, const uint64_t index, const bool eof) {
    // std::string & str = std::string("");
    if(eof == true){
        _lasteofbyte = data.size() + index;
    }
    // index has been record
    if(index < _lastbyteassemble && index + data.size() <= _lastbyteassemble){
        // this->_writeintoBytestream();
    }
    else if(index < _lastbyteassemble && index + data.size() > _lastbyteassemble){
        // cross
        uint64_t id = _lastbyteassemble - index;
        this->push_substring(data.substr(id),_lastbyteassemble,eof);
    }
    else if(index >= _lastbyteassemble){
        #ifdef DEBUG
        cout << "data " << data << " data size " << data.size()<< " index " << index << " eof " << eof << endl;
        #endif
        // insert
        uint64_t uncoveredsize = index - _lastbyteassemble;
        // index = 3
        // _lastbyteassemble = 1
        // data.size() = 1
        // _unassembleindictor = []
        // _unassemblestr = []
        // indictor = [false(1),false(2),false(3)]
        // str = ['c','c','c']

        while(_unassembleindicator.size() < uncoveredsize + data.size()){
            _unassembleindicator.push_back(false);
            _unassemblestr.push_back('c');
        }
        
        for(size_t id = 0;id < data.size();id++){
            // id = 0 -> indictor[2] = true,str[2] = data[0]
            if(_unassembleindicator.at(id + uncoveredsize) == false){
                _unassemblebytecount += 1;
            }
            {    _unassembleindicator.at(id + uncoveredsize) = true;
                _unassemblestr.at(id + uncoveredsize) = data[id];
                // _unassemblebytecount += 1;
            }
            
            // _unassembleindicator.assign() 
        }

    }
    this->_writeintoBytestream();
    _lastbyteassemble = _output.bytes_written();
    if(_lastbyteassemble >= _lasteofbyte){
        _output.end_input();
    }
}

size_t StreamReassembler::unassembled_bytes() const { 
    // CONST class method could only call const member
    return _unassemblebytecount;
}

bool StreamReassembler::empty() const { 
    return _unassemblebytecount == 0; 
}


