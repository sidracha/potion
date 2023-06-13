#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

#include <string>


typedef struct route_struct_t {
  char* buffer;
  size_t buffer_size;
} route_struct_t;

route_struct_t send_string(std::string str);
route_struct_t render(std::string file_path);

char* string_to_char(std::string str);

#endif
