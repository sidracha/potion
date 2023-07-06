#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include <map>

#include <boost/json.hpp>

#include "tcpserver_unix.hpp"

namespace json = boost::json;


class Request {
  private:
    receive_struct_t receiveStruct;

    std::map<std::string, std::string> header_map;
    std::map<std::string, char*> header_map_test;
    std::map<std::string, std::string> q_params;
    
    size_t content_start = 0;

    void parse_q_params();

  public:

    Request (receive_struct_t rs) : receiveStruct(rs) {};
    void parse_headers();
    std::string get_method();
    std::map<std::string, std::string> get_headers();
    
    std::string get_route();
    std::string get_header_value(std::string key);
    json::object get_json();

    inline std::map<std::string, std::string> get_args() {return q_params;}
    inline std::vector<std::byte>* get_bytestream() {return receiveStruct.buffer;}
    inline std::vector<std::byte>* get_bytestream_content_start() {return receiveStruct.buffer+content_start;}
    inline size_t get_content_start_index() {return content_start;}
    inline receive_struct_t get_request_buffer() {return receiveStruct;}
};



#endif
