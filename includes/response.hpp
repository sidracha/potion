#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

#include <string>

#include "request.hpp"

class PotionApp;

typedef struct route_struct_t {
  char* buffer;
  size_t buffer_size;
} route_struct_t;


class Response {
  
  private:
    
    Request* request;

    inline char* string_to_char(std::string str, char* buffer);
    inline void error(std::string msg);

  public:
    Response(Request* r);

    route_struct_t send_string(PotionApp* app, std::string str);
    route_struct_t render(PotionApp* app, std::string file_path);
    route_struct_t send_status_code(PotionApp* app, uint16_t status_code);
    route_struct_t send_file(PotionApp* app, std::string file_path, std::string content_type);

    route_struct_t send_js_file(PotionApp* app, std::string file_path);
  
};


#endif
