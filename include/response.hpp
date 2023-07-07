#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

#include <string>

#include <boost/json.hpp>

#include "request.hpp"


namespace json = boost::json;

class PotionApp;

typedef struct {
  char* buffer;
  size_t buffer_size;
} route_struct_t;


class Response {

  typedef struct header_vect_struct_t {
    std::string key;
    std::string value;
    
  } header_vect_struct_t;
  private:
    
    std::string STATIC_FOLDER;
    
    Request* request;
    //std::map<std::string, std::string> headers_map;
    std::vector<header_vect_struct_t> headers_vect;

    std::string build_headers(int code, bool content);
    void populate_headers(char* buffer, size_t buffer_size, std::string headers);
    route_struct_t create_route_struct(char* buffer, size_t buffer_size);

  public:
    Response(Request* r);

    route_struct_t send_string(std::string str);
    route_struct_t render(std::string file_path);
    route_struct_t send_status_code(int status_code, json::object obj);
    route_struct_t send_file(std::string file, std::string content_type);
    
    route_struct_t send_js_file(std::string file_path);
    route_struct_t serve_static_file(std::string file_path);

    route_struct_t send_json(json::object obj);
    
    void set_header(std::string key, std::string value);

    std::string code_to_phrase(int code);

    void set_static_folder(std::string sf);

};

void r_test(std::string route);

#endif
