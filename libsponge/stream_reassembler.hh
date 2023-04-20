#ifndef SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH
#define SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH

#include "byte_stream.hh"
#include <queue>
#include <cstdint>
#include <string>
#include <map>
#include <limits>
#include <vector>
// #include "strmerge.hh"
// #define DEBUG


void print(std::deque<char>& q);

//! \brief A class that assembles a series of excerpts from a byte stream (possibly out of order,
//! possibly overlapping) into an in-order byte stream.
class StreamReassembler {
  private:
    // Your code here -- add private members as necessary.

    ByteStream _output{ByteStream(0)};  //!< The reassembled in-order byte stream
    size_t _capacity{0};    //!< The maximum number of bytes
    std::deque<char> _unassemblestr{}; // content
    std::deque<bool> _unassembleindicator{}; 
    size_t _lasteofbyte{std::numeric_limits<size_t>::max()};
    size_t _unassemblebytecount{0}; // How many byte has not been assembled
    size_t _lastbyteassemble{0}; // How many byte has been writen into ByteStream Object
    
  public:
    //! \brief Construct a `StreamReassembler` that will store up to `capacity` bytes.
    //! \note This capacity limits both the bytes that have been reassembled,
    //! and those that have not yet been reassembled.
    size_t firstunassemble();
    StreamReassembler(const size_t capacity);
    void _writeintoBytestream();
    
    //! \brief Receive a substring and write any newly contiguous bytes into the stream.
    //!
    //! The StreamReassembler will stay within the memory limits of the `capacity`.
    //! Bytes that would exceed the capacity are silently discarded.
    //!
    //! \param data the substring
    //! \param index indicates the index (place in sequence) of the first byte in `data`
    //! \param eof the last byte of `data` will be the last byte in the entire stream
    void push_substring(const std::string &data, const uint64_t index, const bool eof);

    //! \name Access the reassembled byte stream
    //!@{
    const ByteStream &stream_out() const { return _output; }
    ByteStream &stream_out() { return _output; }
    //!@}

    //! The number of bytes in the substrings stored but not yet reassembled
    //!
    //! \note If the byte at a particular index has been pushed more than once, it
    //! should only be counted once for the purpose of this function.
    size_t unassembled_bytes() const;

    //! \brief Is the internal state empty (other than the output stream)?
    //! \returns `true` if no substrings are waiting to be assembled
    bool empty() const;
};

#endif  // SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH
