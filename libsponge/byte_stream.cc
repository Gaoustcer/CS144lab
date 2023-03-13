#include "byte_stream.hh"
// #include <string>
#include <iostream>
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { 
    #ifdef DEBUG
    std::cout << "create byterstream entity with " << capacity << std::endl;    
    #endif
    _capacity = capacity;
    this->_eof = false;
    // this->_currentsize = 0;
    this->_error = false;
    _bytehasread = 0;
    _bytehaswriten = 0;
    storestr = std::string();
}

size_t ByteStream::write(const string &data) {
    size_t sizeofdata = data.size();
    size_t remainsize = this->remaining_capacity();
    if(sizeofdata <= remainsize){
        // this->_currentsize += sizeofdata;
        storestr += data;
    }
    else{
        // do substr from the top of string
        // this->_currentsize += remainsize;
        this->storestr += data.substr(0,remainsize);
    }
    
    size_t bytewriten = std::min<size_t>(sizeofdata,remainsize);
    _bytehaswriten += bytewriten;
    #ifdef DEBUG
    std::cout << "write string " << data << " store string " << this->storestr << std::endl;
    #endif 
    return bytewriten;
    // DUMMY_CODE(data);
    // return {};
}

//! \param[in] len bytes will be copied 
// from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    #ifdef DEBUG
    std::cout << "peak output byte size " << len << " str is " << storestr << " peek str is "<< storestr.substr(storestr.size() - len)<< std::endl;
    #endif
    return storestr.substr(0,len);
    // DUMMY_CODE(len);
    // return {};
}

//! \param[in] len bytes will be removed 
// from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    // pop need to get rid of top len str last write byte in string
    // example write cat and pop 1 char. then at should left and 'c' is get rid of
    #ifdef DEBUG
    std::cout << "Pop str " << storestr << " len is " << len << " "; 
    #endif
    storestr = storestr.substr(len);
    #ifdef DEBUG
    std::cout << "after pop" << storestr << std::endl;
    #endif
    // std::cout << "pop str " <<  << storestr << std::endl;
    _bytehasread += len;
    return;
 }

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    // DUMMY_CODE(len);
    // return {};
    // std::cout << "read len byte " << len << std::endl;
    std::string retstr = this->peek_output(len);
    this->pop_output(len);
    return retstr;
}

void ByteStream::end_input() {
    this->_eof = true;
}

bool ByteStream::input_ended() const { return {_eof}; }

size_t ByteStream::buffer_size() const { 
    // return _capacity;
    return this->storestr.size();
 }

bool ByteStream::buffer_empty() const { 
    return (this->storestr.size() == 0);
}

bool ByteStream::eof() const { 
    return (this->storestr.size() == 0) && this->_eof;
 }

size_t ByteStream::bytes_written() const { return {_bytehaswriten}; }

size_t ByteStream::bytes_read() const { return {_bytehasread}; }

size_t ByteStream::remaining_capacity() const {
    return _capacity - storestr.size();
}
