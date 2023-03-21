#include "stream_reassembler.hh"
#include <limits>
#include <map>
#include <iostream>
#include <queue>

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
    std::cout << "init\n";
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
    while(_unassembleindicator.size()&&_unassembleindicator.front()){
        _unassembleindicator.pop_front();
        // _lastbyteassemble++;
        s.insert(s.end(),_unassemblestr.front());
        _unassemblestr.pop_front();
    }
    std::cout << "write string is" << s << std::endl;
    _output.write(s);
    return ;
}

void StreamReassembler::push_substring(const string &data, const uint64_t index, const bool eof) {
    // std::string & str = std::string("");
    if(eof == true){
        _lasteofbyte = data.size() + index;
    }
    #ifdef DEBUG
    std::cout << "data push " << data << " index " << index << " eof " << eof << " " <<  _lastbyteassemble << std::endl;
    #endif
    if(index < _lastbyteassemble && data.size() + index > _lastbyteassemble){
        // std::cout << "cut str " << data.substr(_lasteofbyte - index) << std::endl;
        this->push_substring(data.substr(_lastbyteassemble - index),_lastbyteassemble,eof);
        return;
    }
    else if(index == _lastbyteassemble){
        // special case
        // std::cout << "insert str with same assemble " << data << std::endl;
        _output.write(data);
        size_t size = data.size();
        while(size && _unassemblestr.size()){
            if(_unassembleindicator.front()){
                _unassemblebytecount -= 1;
            }
            _unassemblestr.pop_front();
            _unassembleindicator.pop_front();
            size--;
            // _unassemblebytecount -= 1;
        }
        // _unassemblebytecount -= size;
        std::string s;
        while(_unassemblestr.size() && _unassembleindicator.front()){
            s.insert(s.end(),_unassemblestr.front());
            _unassemblestr.pop_front();
            _unassembleindicator.pop_front();
            _unassemblebytecount -= 1;
        }
        // _unassemblebytecount -= s.size();
        _output.write(s);
        _lastbyteassemble = _output.bytes_written();
        if(_lastbyteassemble >= _lasteofbyte){
            _output.end_input();
        }
        return;
    }
    else if(data.size() + index <= _lastbyteassemble){
        return;
    }
    else if(index > _lastbyteassemble){
        size_t lowerboundqueuelength = index - _lastbyteassemble;
        // at least lowerboundqueuelength byte padding false
        while(_unassembleindicator.size() < lowerboundqueuelength){
            _unassembleindicator.push_back(false);
            _unassemblestr.push_back(' ');
        }// The size of queue is at least lowerboundqueue
        // size_t upperboundqueuelength = lowerboundqueuelength + data.size();
        size_t id = 0;
        for(id = 0;id < data.size() && id + lowerboundqueuelength < _unassemblestr.size();id++){
            // if(id + lowerboundqueuelength )
            size_t dataindexhasbeeninthequeue = id + lowerboundqueuelength;
            if(_unassembleindicator.at(dataindexhasbeeninthequeue) == false){
                _unassembleindicator.at(dataindexhasbeeninthequeue) = true;
                _unassemblestr.at(dataindexhasbeeninthequeue) = data[id];
                _unassemblebytecount += 1;
            }
        }
        while(_unassemblestr.size() < lowerboundqueuelength + data.size()){
            _unassemblestr.push_back(data[id]);
            _unassembleindicator.push_back(true);
            _unassemblebytecount += 1;
            id++;
        }
    }
    // size_t startindex = std::max(index,_lastbyteassemble);
    
    // size_t qlenlow = index - _lastbyteassemble;
    // size_t qlenhigh = index + data.size() - _lastbyteassemble;
    // size_t minlength = std::min<size_t>(data.size(),_output.remaining_capacity());
    // std::cout << "size is " << minlength << " " << qlenlow << "\t" << qlenhigh << " _lastbyte " << _lastbyteassemble << std::endl;
    // while(_unassemblestr.size() < qlenlow){
    //     _unassemblestr.push_back(' ');
    //     _unassembleindicator.push_back(false);
    //     // std::cout << "padding";
    // }// extend queue into qlenlow
    // while(_unassemblestr.size() < qlenhigh){
        // _unassemblestr.push_back(data[_unassemblestr.size() - qlenlow]);
        // _unassembleindicator.push_back(true);
    // }
    // std::cout << "\n";
    // std::cout << "extend queue " << qlenlow << std::endl;
    // for(size_t id = qlenlow;id < qlenlow + minlength && id < _unassemblestr.size();id++){
    //     if(_unassembleindicator.at(id) == false){
    //         _unassembleindicator.at(id) = true;
    //         _unassemblestr.at(id) = data[id - qlenlow];
    //     }
    // }
    // while(_unassemblestr.size() < qlenhigh){   
    //     _unassemblestr.push_back(data[_unassemblestr.size() - qlenlow]);
    //     _unassembleindicator.push_back(true);
    // }
    // // std::cout << "extend queue to qlenhigh " << qlenhigh << std::endl; 
    // std::cout << "print the queue ";
    // print(_unassemblestr);
    // // this->_writeintoBytestream();
    // _writeintoBytestream();
    // _lastbyteassemble = _output.bytes_written();
    // std::cout << "_lastbyte " << _lastbyteassemble << std::endl << std::endl;
    // if(_lastbyteassemble >= _lasteofbyte){
    //     std::cout << "End input\n";
    //     _output.end_input();
    // }

}

size_t StreamReassembler::unassembled_bytes() const { 
    // CONST class method could only call const member
    // return _unreassembelebyte + 1;
    return _unassemblebytecount;
}

bool StreamReassembler::empty() const { 
    return _unassemblebytecount == 0; }


