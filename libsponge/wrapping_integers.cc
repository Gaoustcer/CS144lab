#include "wrapping_integers.hh"
#include <limits>
// Dummy implementation of a 32-bit wrapping integer

// For Lab 2, please replace with a real implementation that passes the
// automated checks run by `make check_lab2`.

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

//! Transform an "absolute" 64-bit sequence number (zero-indexed) into a WrappingInt32
//! \param n The input absolute 64-bit sequence number
//! \param isn The initial sequence number
WrappingInt32 wrap(uint64_t n, WrappingInt32 isn) {
    uint32_t num = static_cast<uint32_t> (n & (UINT32_MAX));
    // DUMMY_CODE(n, isn);
    return WrappingInt32{num + isn.raw_value()};
}

//! Transform a WrappingInt32 into an "absolute" 64-bit sequence number (zero-indexed)
//! \param n The relative sequence number
//! \param isn The initial sequence number
//! \param checkpoint A recent absolute 64-bit sequence number
//! \returns the 64-bit sequence number that wraps to `n` and is closest to `checkpoint`
//!
//! \note Each of the two streams of the TCP connection has its own ISN. One stream
//! runs from the local TCPSender to the remote TCPReceiver and has one ISN,
//! and the other stream runs from the remote TCPSender to the local TCPReceiver and
//! has a different ISN.
uint64_t unwrap(WrappingInt32 n, WrappingInt32 isn, uint64_t checkpoint) {
    // seqno -> absolute seqno
    // to close to checkpoint in which range
    // DUMMY_CODE(n, isn, checkpoint);
    uint64_t index = 0;
    if(n.raw_value() < isn.raw_value()){
        index = static_cast<uint64_t>(UINT32_MAX + 1 + n.raw_value() - isn.raw_value()); 

        // There must be an index rewind
    }
    else{
        index = static_cast<uint64_t>(n.raw_value() - isn.raw_value());
    }
    uint64_t lowerbound;
    uint64_t higherbound = ((checkpoint + 1) >> 32) << 32;
    if((checkpoint >> 32) == 0){
        lowerbound = 0;
    }
    else{
        lowerbound = (((checkpoint + 1) >> 32) - 1) << 32;
    }
    if(index > (UINT32_MAX > 1)){
        return {index + lowerbound};
    }
    else{
        return {index + higherbound};
    }
}
// UINT32_MAX
