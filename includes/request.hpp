#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include <map>

#include "tcpserver_unix.hpp"


class Request {
  private:
    receive_struct_t receiveStruct;

    std::map<std::string, std::string> header_map;
    std::map<std::string, char*> header_map_test;
    std::map<std::string, std::string> q_params;

    void parse_q_params();

  public:

    Request (receive_struct_t rs) : receiveStruct(rs) {};
    void parse_headers();
    std::string get_method();
    std::string get_single_header(std::string key);
    std::map<std::string, std::string> get_headers();
    
    std::string get_route();
    std::string get_header_value(std::string key);

    inline std::map<std::string, std::string> get_args() {return q_params;}

};



#endif
