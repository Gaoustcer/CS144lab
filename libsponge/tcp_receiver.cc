#include "tcp_receiver.hh"
#include <cstdlib>
// Dummy implementation of a TCP receiver

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;
// TCPSegment -> TCPHeader
// sport 
void TCPReceiver::segment_received(const TCPSegment &seg) {
    const TCPHeader & header = seg.header();
    const Buffer & buffer = seg.payload();
    if(header.syn && !_isn.has_value()){
        // received syn from peer and _syn status is false
        // make the connection
        _isn = static_cast<WrappingInt32>(rand());
        _checkpoint = static_cast<uint64_t>(header.seqno.raw_value()) + 1;
    }
    // else if(_isn.has_value() && header.fin){
    //     // disconnection the TCP connection
    //     _isn = nullopt;
    //     _checkpoint = 0;
    //     uint64_t index = unwrap(header.seqno,_isn.value(),_checkpoint);
    //     _reassembler.push_substring(string(),index,true);
    // }
    // else if(_isn.has_value() && !header.fin){
    //     // write object into reassemble
    //     _checkpoint += buffer.size();
    //     uint64_t index = unwrap(header.seqno,_isn.value(),_checkpoint);
    //     _reassembler.push_substring(buffer.copy(), index, false);
    // }
    // call unwrap to write into reassemble 
    // push_substring(string &,uint64_t,eof);
    // uint64_t = unwrap(WrappingInt32 n,WrappingInt32 isn,uint64_t checkpoint)
    
    DUMMY_CODE(seg);
}

optional<WrappingInt32> TCPReceiver::ackno() const {
    if(_isn.has_value() == false){
        return {nullopt};
    }
    else{
        // call wrap to get next byte
        // return {_isn.value()};
        
    }
        // return {}; 
}

size_t TCPReceiver::window_size() const { 
    return _capacity - _reassembler.firstunassemble(); }
